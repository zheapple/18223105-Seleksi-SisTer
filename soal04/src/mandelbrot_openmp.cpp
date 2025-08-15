#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "mandelbrot_util.hpp"

#ifdef _OPENMP
#include <omp.h>
#endif

static std::vector<uint32_t> render_openmp(int width, int height, int max_iter, const Viewport& vp) {
    std::vector<uint32_t> img(static_cast<size_t>(width) * height);

    #pragma omp parallel for schedule(static)
    for (int py = 0; py < height; ++py) {
        double y0 = vp.ymin + py * vp.dy;
        for (int px = 0; px < width; ++px) {
            double x0 = vp.xmin + px * vp.dx;
            double nu = mandelbrot_smooth(x0, y0, max_iter);
            img[static_cast<size_t>(py) * width + px] = color_from_nu(nu, max_iter);
        }
    }

    return img;
}

int main(int argc, char** argv) {
    int width, height, max_iter;
    double x_center, y_center, view_height;
    std::string out_name;

    parse_cli(argc, argv, width, height, max_iter,
              x_center, y_center, view_height, out_name,
              "openmp.bmp");

    Viewport vp(width, height, x_center, y_center, view_height);

    // --- Render Serial ---
    auto t0 = std::chrono::high_resolution_clock::now();
    auto img_serial = render_serial_image(width, height, max_iter, vp);
    auto t1 = std::chrono::high_resolution_clock::now();

    save_bitmap("serial_openmp_baseline.bmp", width, height, img_serial);

    double serial_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

#ifdef _OPENMP
    // --- Render OpenMP ---
    auto p0 = std::chrono::high_resolution_clock::now();
    auto img_openmp = render_openmp(width, height, max_iter, vp);
    auto p1 = std::chrono::high_resolution_clock::now();

    save_bitmap(out_name, width, height, img_openmp);

    double parallel_ms = std::chrono::duration<double, std::milli>(p1 - p0).count();

    std::cout << "[OpenMP] Resolution: " << width << "x" << height
              << ", max_iter=" << max_iter << "\n";
    std::cout << "Serial time:   " << serial_ms << " ms (serial_openmp_baseline.bmp)\n";
    std::cout << "Parallel time: " << parallel_ms << " ms (" << out_name << ")\n";
    std::cout << "Speedup:       " << (serial_ms / parallel_ms) << "x\n";
#else
    std::cout << "[OpenMP disabled] Serial time: " << serial_ms
              << " ms (serial_openmp_baseline.bmp)\n";
    std::cout << "Recompile with OpenMP support to enable parallelism.\n";
#endif

    return 0;
}
