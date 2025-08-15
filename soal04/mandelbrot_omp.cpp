#include <iostream>
#include <chrono>
#include <cstdlib>
#include "mandelbrot_utils.hpp"
#ifdef _OPENMP
  #include <omp.h>
#endif

static std::vector<uint8_t> render_omp_rgb(int W, int H, int max_iter, const Viewport& vp) {
    double xmin, xmax, ymin, ymax; viewport_bounds(W, H, vp, xmin, xmax, ymin, ymax);
    std::vector<uint8_t> rgb(W * H * 3);

    #pragma omp parallel for schedule(static)
    for (int y = 0; y < H; ++y) {
        double ci = ymax + (y * (ymin - ymax) / (H - 1.0));
        for (int x = 0; x < W; ++x) {
            double cr = xmin + (x * (xmax - xmin) / (W - 1.0));
            double nu = mandelbrot_smooth(cr, ci, max_iter);
            uint8_t r, g, b; color_from_iter(nu, max_iter, r, g, b);
            size_t idx = (y * W + x) * 3;
            rgb[idx+0] = r; rgb[idx+1] = g; rgb[idx+2] = b;
        }
    }
    return rgb;
}

int main(int argc, char** argv) {
    int W, H, max_iter; Viewport vp; std::string out;
    parse_cli(argc, argv, W, H, max_iter, vp, out, "mandelbrot_omp.bmp");

    // Serial baseline
    auto t0 = std::chrono::steady_clock::now();
    auto rgb_serial = render_serial_rgb(W, H, max_iter, vp);
    auto t1 = std::chrono::steady_clock::now();
    write_bmp24("serial_omp_baseline.bmp", W, H, rgb_serial);

    long long serial_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

#ifdef _OPENMP
    // Parallel
    auto p0 = std::chrono::steady_clock::now();
    auto rgb_parallel = render_omp_rgb(W, H, max_iter, vp);
    auto p1 = std::chrono::steady_clock::now();
    write_bmp24(out, W, H, rgb_parallel);

    long long parallel_ms = std::chrono::duration_cast<std::chrono::milliseconds>(p1 - p0).count();

    std::cout << "Resolution " << W << "x" << H << ", max_iter=" << max_iter << "\n";
    std::cout << "Serial render:   " << serial_ms   << " ms (serial_omp_baseline.bmp)\n";
    std::cout << "Parallel render: " << parallel_ms << " ms (" << out << ")\n";
    if (parallel_ms > 0) {
        double speedup = static_cast<double>(serial_ms) / parallel_ms;
        std::cout << "Speedup:         " << speedup << "x\n";
    }
#else
    std::cout << "Serial render:   " << serial_ms << " ms (serial_omp_baseline.bmp)\n";
    std::cout << "Recompile with OpenMP flags to enable parallel speedup.\n";
#endif

    return 0;
}
