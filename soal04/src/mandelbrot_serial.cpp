#include <iostream>
#include <string>
#include <chrono>
#include "mandelbrot_util.hpp"

int main(int argc, char** argv) {
    int width, height, max_iter;
    double x_center, y_center, view_height;
    std::string out_name;

    // Parsing argumen CLI
    parse_cli(argc, argv, width, height, max_iter,
              x_center, y_center, view_height, out_name,
              "mandelbrot_serial.bmp");

    // Setup viewport
    Viewport vp(width, height, x_center, y_center, view_height);

    // Render serial
    auto t0 = std::chrono::high_resolution_clock::now();
    auto image = render_serial_image(width, height, max_iter, vp);
    auto t1 = std::chrono::high_resolution_clock::now();

    // Simpan file BMP
    save_bitmap(out_name, width, height, image);

    // Waktu render
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cout << "[Serial] Resolution: " << width << "x" << height
              << ", max_iter=" << max_iter << "\n";
    std::cout << "Output file: " << out_name << "\n";
    std::cout << "Render time: " << ms << " ms\n";

    return 0;
}
