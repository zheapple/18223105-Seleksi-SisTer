#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include "mandelbrot_util.hpp"

// Render Mandelbrot secara serial
std::vector<uint32_t> render_serial(int width, int height, int max_iter, const Viewport &view) {
    std::vector<uint32_t> image(width * height);
    for (int py = 0; py < height; ++py) {
        for (int px = 0; px < width; ++px) {
            double x0 = view.xmin + px * view.dx;
            double y0 = view.ymin + py * view.dy;
            int iter = mandelbrot(x0, y0, max_iter);
            image[py * width + px] = get_color(iter, max_iter);
        }
    }
    return image;
}

// Render Mandelbrot secara parallel dengan OpenMP
std::vector<uint32_t> render_openmp(int width, int height, int max_iter, const Viewport &view) {
    std::vector<uint32_t> image(width * height);
    #pragma omp parallel for schedule(dynamic)
    for (int py = 0; py < height; ++py) {
        for (int px = 0; px < width; ++px) {
            double x0 = view.xmin + px * view.dx;
            double y0 = view.ymin + py * view.dy;
            int iter = mandelbrot(x0, y0, max_iter);
            image[py * width + px] = get_color(iter, max_iter);
        }
    }
    return image;
}

int main(int argc, char** argv) {
    // Parsing argumen
    int width      = (argc > 1) ? std::stoi(argv[1]) : 1920;
    int height     = (argc > 2) ? std::stoi(argv[2]) : 1080;
    int max_iter   = (argc > 3) ? std::stoi(argv[3]) : 1000;
    double x_center = (argc > 4) ? std::stod(argv[4]) : -0.75;
    double y_center = (argc > 5) ? std::stod(argv[5]) : 0.0;
    double view_height = (argc > 6) ? std::stod(argv[6]) : 3.0;
    std::string filename = (argc > 7) ? argv[7] : "openmp.bmp";

    Viewport view(width, height, x_center, y_center, view_height);

    // Serial benchmark
    auto t0 = std::chrono::high_resolution_clock::now();
    auto img_serial = render_serial(width, height, max_iter, view);
    auto t1 = std::chrono::high_resolution_clock::now();
    save_bitmap("serial_openmp_baseline.bmp", width, height, img_serial);
    double time_serial = std::chrono::duration<double, std::milli>(t1 - t0).count();

    // Parallel benchmark
    auto p0 = std::chrono::high_resolution_clock::now();
    auto img_parallel = render_openmp(width, height, max_iter, view);
    auto p1 = std::chrono::high_resolution_clock::now();
    save_bitmap(filename, width, height, img_parallel);
    double time_parallel = std::chrono::duration<double, std::milli>(p1 - p0).count();

    // Output info
    int threads_used = omp_get_max_threads();
    std::cout << "[OpenMP] Resolution: " << width << "x" << height
              << ", max_iter=" << max_iter
              << ", threads=" << threads_used << "\n";
    std::cout << "Serial render:   " << time_serial   << " ms (serial_openmp_baseline.bmp)\n";
    std::cout << "Parallel render: " << time_parallel << " ms (" << filename << ")\n";
    if (time_parallel > 0) {
        std::cout << "Speedup:         " << time_serial / time_parallel << "x\n";
    }

    return 0;
}
