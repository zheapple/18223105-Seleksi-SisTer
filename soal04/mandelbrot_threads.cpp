#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "mandelbrot_util.hpp"

static void render_rows(int y0, int y1, int W, int H, int max_iter,
                        double xmin, double xmax, double ymin, double ymax,
                        std::vector<uint8_t>& rgb) {
    for (int y = y0; y < y1; ++y) {
        double ci = ymax + (y * (ymin - ymax) / (H - 1.0));
        for (int x = 0; x < W; ++x) {
            double cr = xmin + (x * (xmax - xmin) / (W - 1.0));
            double nu = mandelbrot_smooth(cr, ci, max_iter);
            uint8_t r, g, b; color_from_iter(nu, max_iter, r, g, b);
            size_t idx = (y * W + x) * 3;
            rgb[idx+0] = r; rgb[idx+1] = g; rgb[idx+2] = b;
        }
    }
}

static std::vector<uint8_t> render_threaded_rgb(int W, int H, int max_iter, const Viewport& vp, int nthreads) {
    double xmin, xmax, ymin, ymax; viewport_bounds(W, H, vp, xmin, xmax, ymin, ymax);
    std::vector<uint8_t> rgb(W * H * 3);

    if (nthreads <= 0) nthreads = std::thread::hardware_concurrency();
    if (nthreads <= 0) nthreads = 4;

    std::vector<std::thread> workers;
    workers.reserve(nthreads);

    int block = (H + nthreads - 1) / nthreads;
    for (int t = 0; t < nthreads; ++t) {
        int y0 = t * block;
        int y1 = std::min(H, y0 + block);
        if (y0 >= y1) break;
        workers.emplace_back(render_rows, y0, y1, W, H, max_iter, xmin, xmax, ymin, ymax, std::ref(rgb));
    }
    for (auto& th : workers) th.join();
    return rgb;
}

int main(int argc, char** argv) {
    int W, H, max_iter; Viewport vp; std::string out;
    parse_cli(argc, argv, W, H, max_iter, vp, out, "mandelbrot_threads.bmp");

    int nthreads = std::thread::hardware_concurrency();
    const char* env = std::getenv("THREADS");
    if (env) { try { nthreads = std::stoi(env); } catch (...) {} }

    // Serial baseline
    auto t0 = std::chrono::steady_clock::now();
    auto rgb_serial = render_serial_rgb(W, H, max_iter, vp);
    auto t1 = std::chrono::steady_clock::now();
    write_bmp24("serial_threads_baseline.bmp", W, H, rgb_serial);

    // Parallel threaded
    auto p0 = std::chrono::steady_clock::now();
    auto rgb_parallel = render_threaded_rgb(W, H, max_iter, vp, nthreads);
    auto p1 = std::chrono::steady_clock::now();
    write_bmp24(out, W, H, rgb_parallel);

    long long serial_ms   = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    long long parallel_ms = std::chrono::duration_cast<std::chrono::milliseconds>(p1 - p0).count();

    std::cout << "Resolution " << W << "x" << H << ", max_iter=" << max_iter << "\n";
    std::cout << "Threads: " << nthreads << "\n";
    std::cout << "Serial render:   " << serial_ms   << " ms  (serial_threads_baseline.bmp)\n";
    std::cout << "Parallel render: " << parallel_ms << " ms  (" << out << ")\n";
    if (parallel_ms > 0) {
        double speedup = static_cast<double>(serial_ms) / parallel_ms;
        std::cout << "Speedup:        " << speedup << "x\n";
    }
    return 0;
}
