#ifndef MANDELBROT_UTIL_HPP
#define MANDELBROT_UTIL_HPP

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <algorithm>

//
// Viewport: memetakan pixel (px, py) -> koordinat kompleks (x, y)
// Diberi width, height, center (xc, yc), dan tinggi tampilan (view_h),
// otomatis menghitung xmin, ymin, dx, dy.
//
struct Viewport {
    int    width  = 1920;
    int    height = 1080;
    double xc     = -0.75;
    double yc     = 0.0;
    double view_h = 3.0;

    // derived
    double xmin = 0.0, ymin = 0.0;
    double xmax = 0.0, ymax = 0.0;
    double dx   = 0.0, dy   = 0.0;

    Viewport() { recalc(); }

    Viewport(int w, int h, double xcenter, double ycenter, double vh)
        : width(w), height(h), xc(xcenter), yc(ycenter), view_h(vh) {
        recalc();
    }

    void recalc() {
        if (width <= 0 || height <= 0 || view_h <= 0.0)
            throw std::invalid_argument("Viewport: width/height/view_h must be positive");
        double aspect = static_cast<double>(width) / static_cast<double>(height);
        double half_h = view_h * 0.5;
        double half_w = half_h * aspect;
        xmin = xc - half_w;
        xmax = xc + half_w;
        ymin = yc - half_h;
        ymax = yc + half_h;
        dx = (xmax - xmin) / std::max(1, width  - 1);
        dy = (ymax - ymin) / std::max(1, height - 1);
    }
};

//
// Iterasi Mandelbrot (integer)
//
// Mengembalikan jumlah iterasi sebelum escape (atau max_iter jika tidak escape).
//
inline int mandelbrot_int(double x0, double y0, int max_iter) {
    double x = 0.0, y = 0.0;
    double x2 = 0.0, y2 = 0.0;
    int i = 0;
    for (; i < max_iter && (x2 + y2) <= 4.0; ++i) {
        y = 2.0 * x * y + y0;
        x = x2 - y2 + x0;
        x2 = x * x;
        y2 = y * y;
    }
    return i;
}

//
// Iterasi Mandelbrot (smooth coloring)
//
// Mengembalikan nilai real 'nu' untuk pewarnaan halus.
// Jika i >= max_iter (dianggap "inside"), kembalikan max_iter.
//
inline double mandelbrot_smooth(double x0, double y0, int max_iter) {
    double x = 0.0, y = 0.0;
    double x2 = 0.0, y2 = 0.0;
    int i = 0;
    for (; i < max_iter && (x2 + y2) <= 4.0; ++i) {
        y = 2.0 * x * y + y0;
        x = x2 - y2 + x0;
        x2 = x * x;
        y2 = y * y;
    }
    if (i >= max_iter) return static_cast<double>(max_iter);
    // Smooth escape-time
    double mag = std::sqrt(x2 + y2);
    double nu = i + 1.0 - std::log2(std::max(1e-16, std::log2(std::max(1.0, mag))));
    return nu;
}

//
// Helper: HSV (0..1) -> RGB (0..255)
//
inline void hsv_to_rgb(double h, double s, double v, uint8_t& r, uint8_t& g, uint8_t& b) {
    h = std::fmod(std::fabs(h), 1.0);
    if (s <= 0.0) {
        uint8_t val = static_cast<uint8_t>(std::clamp(v, 0.0, 1.0) * 255.0 + 0.5);
        r = g = b = val; return;
    }
    double hh = h * 6.0;
    int    i  = static_cast<int>(std::floor(hh));
    double f  = hh - i;
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
    r = static_cast<uint8_t>(std::clamp(R, 0.0, 1.0) * 255.0 + 0.5);
    g = static_cast<uint8_t>(std::clamp(G, 0.0, 1.0) * 255.0 + 0.5);
    b = static_cast<uint8_t>(std::clamp(B, 0.0, 1.0) * 255.0 + 0.5);
}

//
// Pewarnaan dari nilai 'nu' (smooth) -> 32-bit BGRA
//
inline uint32_t color_from_nu(double nu, int max_iter) {
    uint8_t r=0, g=0, b=0, a=255;
    if (nu >= max_iter) {
        // inside set -> hitam
        return (static_cast<uint32_t>(a) << 24)
             | (static_cast<uint32_t>(0) << 16)
             | (static_cast<uint32_t>(0) << 8)
             | (static_cast<uint32_t>(0));
    }
    double t = std::clamp(nu / std::max(1, max_iter), 0.0, 1.0);
    // palet: Hue berputar tajam, saturasi & value konstan
    double h = std::fmod(0.95 + 10.0 * t, 1.0);
    double s = 0.85;
    double v = 1.0;
    hsv_to_rgb(h, s, v, r, g, b);

    // BGRA
    return (static_cast<uint32_t>(a) << 24)
         | (static_cast<uint32_t>(r) << 16) // NOTE: urutan di BMP saat tulis tetap B,G,R,A per byte
         | (static_cast<uint32_t>(g) << 8)
         | (static_cast<uint32_t>(b));
}

//
// Renderer serial siap pakai -> vector<uint32_t> BGRA
//
inline std::vector<uint32_t> render_serial_image(int width, int height, int max_iter, const Viewport& vp) {
    std::vector<uint32_t> img(static_cast<size_t>(width) * height);
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

//
// Tulis BMP 32-bit (BGRA) bottom-up
//
inline void save_bitmap(const std::string& filename, int width, int height, const std::vector<uint32_t>& bgra) {
    if (bgra.size() != static_cast<size_t>(width) * height) {
        throw std::runtime_error("save_bitmap: pixel buffer size mismatch");
    }

    std::ofstream f(filename, std::ios::binary);
    if (!f) throw std::runtime_error("save_bitmap: cannot open output file: " + filename);

    const uint32_t file_header_size = 14;
    const uint32_t dib_header_size  = 40; // BITMAPINFOHEADER
    const uint32_t bpp = 32;
    const uint32_t compression = 0; // BI_RGB
    const uint32_t row_stride = static_cast<uint32_t>(width) * 4u; // 4 bytes per pixel
    const uint32_t image_size = row_stride * static_cast<uint32_t>(height);
    const uint32_t pixel_data_offset = file_header_size + dib_header_size;
    const uint32_t file_size = pixel_data_offset + image_size;

    auto put16 = [&](uint16_t v){ f.put(static_cast<char>(v & 0xFF)); f.put(static_cast<char>((v >> 8) & 0xFF)); };
    auto put32 = [&](uint32_t v){
        f.put(static_cast<char>(v & 0xFF));
        f.put(static_cast<char>((v >> 8) & 0xFF));
        f.put(static_cast<char>((v >> 16) & 0xFF));
        f.put(static_cast<char>((v >> 24) & 0xFF));
    };

    // BITMAP FILE HEADER
    f.put('B'); f.put('M');                 // Signature
    put32(file_size);                       // File size
    put16(0); put16(0);                     // Reserved
    put32(pixel_data_offset);               // Pixel data offset

    // DIB HEADER (BITMAPINFOHEADER)
    put32(dib_header_size);
    put32(static_cast<uint32_t>(width));
    put32(static_cast<uint32_t>(height));   // positive height = bottom-up
    put16(1);                               // planes
    put16(static_cast<uint16_t>(bpp));      // bits-per-pixel
    put32(compression);                     // compression BI_RGB
    put32(image_size);                      // image size
    put32(2835); put32(2835);               // X/Y pixels-per-meter (~72 DPI)
    put32(0); put32(0);                     // color used/important

    // Pixel data (bottom-up): tiap baris dari bawah ke atas
    for (int y = height - 1; y >= 0; --y) {
        const uint32_t* row = &bgra[static_cast<size_t>(y) * width];
        // tulis per-pixel dalam urutan B, G, R, A
        for (int x = 0; x < width; ++x) {
            uint32_t px = row[x];
            uint8_t r = static_cast<uint8_t>((px >> 16) & 0xFF);
            uint8_t g = static_cast<uint8_t>((px >> 8) & 0xFF);
            uint8_t b = static_cast<uint8_t>((px) & 0xFF);
            uint8_t a = static_cast<uint8_t>((px >> 24) & 0xFF);
            f.put(static_cast<char>(b));
            f.put(static_cast<char>(g));
            f.put(static_cast<char>(r));
            f.put(static_cast<char>(a));
        }
    }
}

//
// Parser argumen CLI umum
// Format: [width height max_iter x_center y_center view_height output.bmp]
//
inline void parse_cli(int argc, char** argv,
                      int& width, int& height, int& max_iter,
                      double& x_center, double& y_center, double& view_height,
                      std::string& out_name,
                      const std::string& default_out = "output.bmp") {
    width = 1920;
    height = 1080;
    max_iter = 1000;
    x_center = -0.75;
    y_center = 0.0;
    view_height = 3.0;
    out_name = default_out;

    if (argc > 1) width  = std::stoi(argv[1]);
    if (argc > 2) height = std::stoi(argv[2]);
    if (argc > 3) max_iter = std::stoi(argv[3]);
    if (argc > 4) x_center = std::stod(argv[4]);
    if (argc > 5) y_center = std::stod(argv[5]);
    if (argc > 6) view_height = std::stod(argv[6]);
    if (argc > 7) out_name = argv[7];
}

#endif // MANDELBROT_UTIL_HPP
