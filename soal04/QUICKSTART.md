# Quick Start Guide - Soal04

## 🚀 Quick Commands

```bash
# 1. Build all implementations
./build.sh

# 2. Validate all implementations  
./validate.sh

# 3. Run comprehensive benchmark
./benchmark.sh

# 4. Explore interesting fractal regions
./explore_regions.sh
```

## 📁 File Organization

- **Source code**: `src/` (commit to git)
- **Executables**: `bin/` (ignored by git)  
- **Generated images**: `output/` (ignored by git)
- **Scripts**: `*.sh` (commit to git)

## 🔧 Manual Usage

```bash
# Serial version
./bin/mandelbrot_serial [width] [height] [max_iter] [x_center] [y_center] [view_height] [output_file]

# Threading version  
THREADS=8 ./bin/mandelbrot_threads [params...]

# OpenMP version
OMP_NUM_THREADS=8 ./bin/mandelbrot_openmp [params...]
```

## 📊 What Gets Committed vs Generated

### ✅ Commit to Git:
- `src/` - Source code files
- `README.md` - Documentation
- `*.sh` - Build and utility scripts  
- `.gitignore` - Git ignore rules

### ❌ Don't Commit (Auto-generated):
- `bin/` - Compiled executables
- `output/` - Generated BMP images
- `*.bmp` - Any BMP files in root
