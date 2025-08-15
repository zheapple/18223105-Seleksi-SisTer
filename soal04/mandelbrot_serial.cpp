#include <iostream>
#include <chrono>
#include "mandelbrot_util.hpp"

int main(int argc, char** argv) {
    int W, H, max_iter; Viewport vp; std::string out;
    parse_cli(argc, argv, W, H, max_iter, vp, out, "serial.bmp");

    auto t0 = std::chrono::steady_clock::now();
    auto rgb = render_serial_rgb(W, H, max_iter, vp);
    auto t1 = std::chrono::steady_clock::now();
    write_bmp24(out, W, H, rgb);
    auto t2 = std::chrono::steady_clock::now();

    auto render_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    auto io_ms     = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "[Serial] " << W << "x" << H << ", max_iter=" << max_iter
              << ": render=" << render_ms << " ms, write=" << io_ms << " ms\n";
    std::cout << "Output → " << out << "\n";
    return 0;
}
