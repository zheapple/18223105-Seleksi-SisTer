#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <stdexcept>

struct Viewport {
    double xc = -0.75;   // center x
    double yc = 0.0;     // center y
    double h  = 3.0;     // complex-plane height covered (y-range)
};

inline void parse_cli(int argc, char** argv, int& W, int& H, int& max_iter,
                      Viewport& vp, std::string& out_name,
                      const std::string& default_out) {
    W = 1920; H = 1080; max_iter = 1000; vp = Viewport{}; out_name = default_out;
    if (argc >= 3) {
        W = std::stoi(argv[1]);
        H = std::stoi(argv[2]);
    }
    if (argc >= 4) max_iter = std::stoi(argv[3]);
    if (argc >= 6) { vp.xc = std::stod(argv[4]); vp.yc = std::stod(argv[5]); }
    if (argc >= 7) vp.h  = std::stod(argv[6]);
    if (argc >= 8) out_name = argv[7];
}

inline void viewport_bounds(int W, int H, const Viewport& vp,
                            double& xmin, double& xmax, double& ymin, double& ymax) {
    double aspect = static_cast<double>(W) / H;
    double half_h = vp.h * 0.5;
    double half_w = half_h * aspect;
    xmin = vp.xc - half_w; xmax = vp.xc + half_w;
    ymin = vp.yc - half_h; ymax = vp.yc + half_h;
}

// Smooth iteration count (for coloring)
inline double mandelbrot_smooth(double cr, double ci, int max_iter) {
    double zr = 0.0, zi = 0.0;
    int i = 0; double zr2 = 0.0, zi2 = 0.0;
    for (; i < max_iter && (zr2 + zi2) <= 4.0; ++i) {
        zi = 2.0 * zr * zi + ci;
        zr = zr2 - zi2 + cr;
        zr2 = zr * zr; zi2 = zi * zi;
    }
    if (i >= max_iter) return static_cast<double>(max_iter);
    // continuous/smooth coloring
    double mag = std::sqrt(zr2 + zi2);
    double nu = i + 1.0 - std::log2(std::log2(mag));
    return nu;
}

// HSV (h in [0,1), s,v in [0,1]) to RGB 0..255
inline void hsv_to_rgb(double h, double s, double v, uint8_t& r, uint8_t& g, uint8_t& b) {
    if (s <= 0.0) { r = g = b = static_cast<uint8_t>(v * 255.0 + 0.5); return; }
    h = std::fmod(std::fabs(h), 1.0) * 6.0; // 0..6
    int i = static_cast<int>(std::floor(h));
    double f = h - i;
    double p = v * (1.0 - s);
    double q = v * (1.0 - s * f);
    double t = v * (1.0 - s * (1.0 - f));
    double R, G, B;
    switch (i % 6) {
        case 0: R=v; G=t; B=p; break;
        case 1: R=q; G=v; B=p; break;
        case 2: R=p; G=v; B=t; break;
        case 3: R=p; G=q; B=v; break;
        case 4: R=t; G=p; B=v; break;
        case 5: R=v; G=p; B=q; break;
        default: R=G=B=0; break;
    }
    r = static_cast<uint8_t>(R * 255.0 + 0.5);
    g = static_cast<uint8_t>(G * 255.0 + 0.5);
    b = static_cast<uint8_t>(B * 255.0 + 0.5);
}

inline void color_from_iter(double nu, int max_iter,
                            uint8_t& r, uint8_t& g, uint8_t& b) {
    if (nu >= max_iter) { r = g = b = 0; return; } // inside set → black
    double t = nu / max_iter;              // 0..1
    double h = 0.95 + 10.0 * t;            // wrap around hues for variety
    h = std::fmod(h, 1.0);
    double s = 0.8, v = 1.0;
    hsv_to_rgb(h, s, v, r, g, b);
}

inline std::vector<uint8_t> render_serial_rgb(int W, int H, int max_iter, const Viewport& vp) {
    double xmin, xmax, ymin, ymax; viewport_bounds(W, H, vp, xmin, xmax, ymin, ymax);
    std::vector<uint8_t> rgb(W * H * 3);
    for (int y = 0; y < H; ++y) {
        double ci = ymax + (y * (ymin - ymax) / (H - 1.0)); // top→bottom
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

inline void write_bmp24(const std::string& filename, int W, int H, const std::vector<uint8_t>& rgb) {
    if (rgb.size() != static_cast<size_t>(W) * H * 3) {
        throw std::runtime_error("RGB buffer size mismatch");
    }
    std::ofstream f(filename, std::ios::binary);
    if (!f) throw std::runtime_error("Failed to open output file: " + filename);

    int row_stride = W * 3;
    int padding = (4 - (row_stride % 4)) % 4;
    int image_size = (row_stride + padding) * H;
    int file_size  = 14 + 40 + image_size;

    // BITMAPFILEHEADER
    f.put('B'); f.put('M');
    auto put32 = [&](uint32_t v){ f.put(v & 0xFF); f.put((v>>8)&0xFF); f.put((v>>16)&0xFF); f.put((v>>24)&0xFF); };
    auto put16 = [&](uint16_t v){ f.put(v & 0xFF); f.put((v>>8)&0xFF); };
    put32(file_size);
    put16(0); put16(0);              // reserved
    put32(54);                       // pixel data offset

    // BITMAPINFOHEADER
    put32(40);                       // header size
    put32(static_cast<uint32_t>(W));
    put32(static_cast<uint32_t>(H)); // positive → bottom-up
    put16(1);                        // planes
    put16(24);                       // bpp
    put32(0);                        // compression BI_RGB
    put32(image_size);
    put32(2835); put32(2835);        // 72 DPI
    put32(0); put32(0);              // colors used/important

    std::vector<char> pad(padding, 0);
    // Write rows bottom-up
    for (int y = H - 1; y >= 0; --y) {
        for (int x = 0; x < W; ++x) {
            size_t idx = (y * W + x) * 3;
            uint8_t r = rgb[idx], g = rgb[idx+1], b = rgb[idx+2];
            f.put(static_cast<char>(b));
            f.put(static_cast<char>(g));
            f.put(static_cast<char>(r));
        }
        if (padding) f.write(pad.data(), padding);
    }
}
