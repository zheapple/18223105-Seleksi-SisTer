# Soal 04: Mandelbrot Set Fractal Generator

Implementasi generator fraktal Mandelbrot Set dengan tiga pendekatan parallelisasi berbeda untuk membandingkan performa komputasi serial vs paralel.

## � Struktur Project

```
soal04/
├── src/                    # Source code
│   ├── mandelbrot_serial.cpp
│   ├── mandelbrot_openmp.cpp  
│   ├── mandelbrot_threads.cpp
│   └── mandelbrot_util.hpp
├── bin/                    # Compiled executables (generated)
├── output/                 # Generated BMP files (generated)
├── scripts/
│   ├── build.sh           # Build script
│   ├── benchmark.sh       # Benchmarking script  
│   ├── validate.sh        # Validation script
│   └── explore_regions.sh # Region exploration
├── README.md
└── .gitignore
```

## �📋 Deskripsi Implementasi

### 1. **src/mandelbrot_serial.cpp** - Implementasi Serial
- Menggunakan single thread untuk komputasi
- Baseline untuk perbandingan performa
- Render pixel per pixel secara berurutan
- Waktu eksekusi paling lambat namun paling sederhana

### 2. **src/mandelbrot_openmp.cpp** - Implementasi OpenMP
- Menggunakan OpenMP untuk parallelisasi otomatis
- Parallel for loop dengan `#pragma omp parallel for`
- Mendukung pengaturan jumlah thread via environment variable `OMP_NUM_THREADS`
- Menghasilkan dua output: serial baseline dan hasil paralel dengan speedup comparison
- Load balancing otomatis oleh OpenMP runtime

### 3. **src/mandelbrot_threads.cpp** - Implementasi Manual Threading
- Menggunakan `std::thread` untuk kontrol manual thread
- Membagi kerja berdasarkan chunks baris (row-based decomposition)
- Jumlah thread dapat diatur via environment variable `THREADS`
- Default menggunakan `std::thread::hardware_concurrency()`
- Implementasi join-based synchronization

### 4. **src/mandelbrot_util.hpp** - Utility Functions
- Definisi struct `Viewport` untuk mapping koordinat
- Fungsi `mandelbrot_smooth()` untuk smooth coloring
- Fungsi `color_from_nu()` untuk color mapping
- Fungsi `save_bitmap()` untuk export ke BMP
- Parser command line arguments

## 🛠️ Cara Kompilasi

### Prerequisites
```bash
# macOS - Install OpenMP via Homebrew
brew install libomp

# Linux - Install OpenMP development package
# Ubuntu/Debian:
sudo apt-get install libomp-dev

# CentOS/RHEL:
sudo yum install libomp-devel
```

### Kompilasi Serial Version
```bash
g++ -std=c++17 -O2 src/mandelbrot_serial.cpp -o bin/mandelbrot_serial
```

### Kompilasi Threading Version
```bash
g++ -std=c++17 -O2 -pthread src/mandelbrot_threads.cpp -o bin/mandelbrot_threads
```

### Kompilasi OpenMP Version

**macOS dengan Homebrew libomp:**
```bash
clang++ -std=c++17 -O2 -Xpreprocessor -fopenmp \
        -I/usr/local/opt/libomp/include \
        -L/usr/local/opt/libomp/lib \
        -lomp src/mandelbrot_openmp.cpp -o bin/mandelbrot_openmp
```

**Linux dengan GCC:**
```bash
g++ -std=c++17 -O2 -fopenmp src/mandelbrot_openmp.cpp -o bin/mandelbrot_openmp
```

### Compile Script
Buat script `build.sh` untuk kemudahan:
```bash
#!/bin/bash
echo "Building Mandelbrot implementations..."

# Serial version
echo "Building serial version..."
g++ -std=c++17 -O2 mandelbrot_serial.cpp -o mandelbrot_serial

# Threading version  
echo "Building threading version..."
g++ -std=c++17 -O2 -pthread mandelbrot_threads.cpp -o mandelbrot_threads

# OpenMP version (macOS)
echo "Building OpenMP version..."
if [[ "$OSTYPE" == "darwin"* ]]; then
    clang++ -std=c++17 -O2 -Xpreprocessor -fopenmp \
            -I/usr/local/opt/libomp/include \
            -L/usr/local/opt/libomp/lib \
            -lomp mandelbrot_openmp.cpp -o mandelbrot_openmp
else
    g++ -std=c++17 -O2 -fopenmp mandelbrot_openmp.cpp -o mandelbrot_openmp
fi

echo "Build complete!"
```

Jalankan:
```bash
chmod +x build.sh
./build.sh
```

## 🚀 Cara Menjalankan

### Format Command Line Arguments
```
./program [width] [height] [max_iter] [x_center] [y_center] [view_height] [output_file]
```

**Parameter Default:**
- `width`: 1920
- `height`: 1080  
- `max_iter`: 1000
- `x_center`: -0.75
- `y_center`: 0.0
- `view_height`: 3.0
- `output_file`: sesuai program

### Menjalankan Serial Version
```bash
# Default parameters
./bin/mandelbrot_serial

# Custom parameters  
./bin/mandelbrot_serial 800 600 500

# High resolution
./bin/mandelbrot_serial 3840 2160 2000 -0.5 0.0 2.0 output/mandel_4k.bmp
```

### Menjalankan Threading Version
```bash
# Default (menggunakan hardware_concurrency)
./bin/mandelbrot_threads

# Dengan 8 threads
THREADS=8 ./bin/mandelbrot_threads

# Dengan parameter custom  
THREADS=4 ./bin/mandelbrot_threads 1600 900 1500 -0.75 0.0 3.0 output/threads_test.bmp
```

### Menjalankan OpenMP Version
```bash
# Default threads
./bin/mandelbrot_openmp

# Dengan 8 threads
OMP_NUM_THREADS=8 ./bin/mandelbrot_openmp

# Dengan parameter custom
OMP_NUM_THREADS=16 ./bin/mandelbrot_openmp 2560 1440 3000 -0.75 0.0 3.0 output/openmp_test.bmp
```

## 📊 Benchmarking

### Script Benchmarking Otomatis
Buat script `benchmark.sh`:

```bash
#!/bin/bash
echo "=== Mandelbrot Benchmarking ==="
echo "Date: $(date)"
echo "CPU: $(sysctl -n machdep.cpu.brand_string)"
echo "Cores: $(sysctl -n hw.ncpu)"
echo ""

# Test parameters
WIDTH=1920
HEIGHT=1080
MAX_ITER=1000

echo "Parameters: ${WIDTH}x${HEIGHT}, max_iter=${MAX_ITER}"
echo ""

# Serial baseline
echo "=== SERIAL BASELINE ==="
./mandelbrot_serial $WIDTH $HEIGHT $MAX_ITER
echo ""

# Threading tests
echo "=== THREADING TESTS ==="
for threads in 1 2 4 8 16; do
    echo "--- $threads threads ---"
    THREADS=$threads ./mandelbrot_threads $WIDTH $HEIGHT $MAX_ITER
    echo ""
done

# OpenMP tests  
echo "=== OPENMP TESTS ==="
for threads in 1 2 4 8 16; do
    echo "--- $threads threads ---"
    OMP_NUM_THREADS=$threads ./mandelbrot_openmp $WIDTH $HEIGHT $MAX_ITER
    echo ""
done
```

### Hasil Benchmarking Sampel

**Sistem Test:** MacBook Pro M1, 8 cores
**Parameters:** 1920x1080, max_iter=1000

| Implementation | Threads | Time (ms) | Speedup | Efficiency |
|----------------|---------|-----------|---------|------------|
| Serial         | 1       | 1298.81   | 1.00x   | 100%       |
| Threading      | 1       | 1245.32   | 1.04x   | 104%       |
| Threading      | 2       | 662.44    | 1.96x   | 98%        |
| Threading      | 4       | 474.95    | 2.73x   | 68%        |
| Threading      | 8       | 538.76    | 2.41x   | 30%        |
| OpenMP         | 1       | 986.46    | 1.32x   | 132%       |
| OpenMP         | 2       | 505.23    | 2.57x   | 128%       |
| OpenMP         | 4       | 487.64    | 2.66x   | 67%        |
| OpenMP         | 8       | 487.35    | 2.66x   | 33%        |

**Analisis:**
- **Threading** optimal di 4 threads (2.73x speedup)
- **OpenMP** konsisten di 4-8 threads (~2.66x speedup)  
- Diminishing returns setelah 4 threads karena memory bandwidth limitation
- OpenMP lebih konsisten dalam load balancing

## 🖼️ Output Files

Program menghasilkan file BMP dengan visualisasi fraktal Mandelbrot di directory `output/`:

- `output/serial_*.bmp` - Output serial version
- `output/threads_*.bmp` - Output threading version  
- `output/openmp_*.bmp` - Output OpenMP version
- `output/regions/` - Koleksi region menarik dari explore_regions.sh

### Viewing Images
**macOS:**
```bash
open output/*.bmp
```

**Linux:**
```bash
eog output/*.bmp      # GNOME
feh output/*.bmp      # feh
```

## 🔧 Parameter Tuning

### Untuk Benchmarking Cepat
```bash
# Low resolution untuk testing cepat
./bin/mandelbrot_serial 800 600 500 -0.75 0.0 3.0 output/test_low.bmp

# Medium resolution 
./bin/mandelbrot_serial 1600 900 1000 -0.75 0.0 3.0 output/test_med.bmp

# High resolution untuk stress test
./bin/mandelbrot_serial 3840 2160 2000 -0.75 0.0 3.0 output/test_high.bmp
```

### Exploring Different Regions
```bash
# Classic Mandelbrot view
./bin/mandelbrot_serial 1920 1080 1000 -0.75 0.0 3.0 output/classic.bmp

# Zoomed seahorse valley
./bin/mandelbrot_serial 1920 1080 2000 -0.74529 0.11307 0.01 output/seahorse.bmp

# Lightning pattern
./bin/mandelbrot_serial 1920 1080 1500 -1.25066 0.02012 0.005 output/lightning.bmp

# Mini mandelbrot
./bin/mandelbrot_serial 1920 1080 3000 -0.15652 1.03225 0.02 output/mini.bmp
```

## 🐛 Troubleshooting

### OpenMP Compilation Issues

**Error: `omp.h` not found**
```bash
# Install OpenMP library
brew install libomp  # macOS
sudo apt install libomp-dev  # Ubuntu
```

**Error: `unsupported option '-fopenmp'` pada macOS**
```bash
# Gunakan clang dengan explicit paths
clang++ -Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include -L/usr/local/opt/libomp/lib -lomp
```

### Runtime Issues

**Error: `std::clamp not found`**
- Pastikan menggunakan `-std=c++17` atau yang lebih baru

**Program crash dengan `--help`**
- Parser tidak mendukung `--help`, gunakan tanpa arguments untuk default

### Performance Issues

**Threading slower than serial:**
- Coba dengan resolusi yang lebih besar
- Thread overhead bisa dominan pada workload kecil

**No speedup dengan banyak threads:**
- Memory bandwidth bottleneck
- Optimal thread count biasanya = jumlah physical cores

## 📈 Tips Optimasi

1. **Compiler optimization:** Selalu gunakan `-O2` atau `-O3`
2. **Thread count:** Mulai dengan physical core count
3. **Resolution scaling:** Gunakan resolusi besar untuk parallelization yang efektif
4. **Memory access:** Row-major processing untuk cache efficiency
5. **Load balancing:** OpenMP `schedule(dynamic)` untuk irregular workloads

## 🔍 Advanced Usage

### Environment Variables
```bash
# Threading version
export THREADS=8

# OpenMP version  
export OMP_NUM_THREADS=8
export OMP_SCHEDULE="dynamic,1"
export OMP_PROC_BIND="close"
```

### Batch Processing
```bash
#!/bin/bash
# Generate multiple zoom levels
for zoom in 3.0 1.0 0.5 0.1 0.05; do
    ./bin/mandelbrot_openmp 1920 1080 2000 -0.75 0.0 $zoom "output/zoom_$zoom.bmp"
done
```

---
**Author:** 18223105  
**Course:** Sister (Sistem Terdistribusi)  
**Institution:** Institut Teknologi Bandung
