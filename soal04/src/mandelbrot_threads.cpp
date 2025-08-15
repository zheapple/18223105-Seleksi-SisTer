#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <cstdlib> // getenv
#include "mandelbrot_util.hpp"

static void render_chunk(std::vector<uint32_t>& img,
                          int width, int height, int max_iter,
                          const Viewport& vp, int y_start, int y_end) {
    for (int py = y_start; py < y_end; ++py) {
        double y0 = vp.ymin + py * vp.dy;
        for (int px = 0; px < width; ++px) {
            double x0 = vp.xmin + px * vp.dx;
            double nu = mandelbrot_smooth(x0, y0, max_iter);
            img[static_cast<size_t>(py) * width + px] = color_from_nu(nu, max_iter);
        }
    }
}

int main(int argc, char** argv) {
    int width, height, max_iter;
    double x_center, y_center, view_height;
    std::string out_name;

    parse_cli(argc, argv, width, height, max_iter,
              x_center, y_center, view_height, out_name,
              "mandelbrot_threads.bmp");

    Viewport vp(width, height, x_center, y_center, view_height);

    // Tentukan jumlah thread
    int num_threads = std::thread::hardware_concurrency();
    if (const char* env_p = std::getenv("THREADS")) {
        num_threads = std::max(1, std::atoi(env_p));
    }
    if (num_threads <= 0) num_threads = 1;

    std::vector<uint32_t> image(static_cast<size_t>(width) * height);

    auto t0 = std::chrono::high_resolution_clock::now();

    // Bagi pekerjaan
    std::vector<std::thread> workers;
    int chunk = height / num_threads;
    int y_start = 0;
    for (int i = 0; i < num_threads; ++i) {
        int y_end = (i == num_threads - 1) ? height : y_start + chunk;
        workers.emplace_back(render_chunk, std::ref(image),
                             width, height, max_iter, std::cref(vp),
                             y_start, y_end);
        y_start = y_end;
    }

    // Tunggu semua thread selesai
    for (auto& th : workers) th.join();

    auto t1 = std::chrono::high_resolution_clock::now();

    save_bitmap(out_name, width, height, image);

    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cout << "[Threads] Resolution: " << width << "x" << height
              << ", max_iter=" << max_iter << "\n";
    std::cout << "Threads used: " << num_threads << "\n";
    std::cout << "Output file: " << out_name << "\n";
    std::cout << "Render time: " << ms << " ms\n";

    return 0;
}
