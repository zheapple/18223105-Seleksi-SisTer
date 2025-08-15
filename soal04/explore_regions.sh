#!/bin/bash
echo "=== Mandelbrot Region Explorer ==="
echo "Generating fractal images for different interesting regions..."
echo ""

# Build first if needed
if [ ! -f "bin/mandelbrot_openmp" ]; then
    echo "Building executables first..."
    ./build.sh
    echo ""
fi

# Create output directory
mkdir -p output/regions

# Classic Mandelbrot view
echo "1. Classic Mandelbrot view..."
./bin/mandelbrot_openmp 1920 1080 1000 -0.75 0.0 3.0 output/regions/classic.bmp

# Zoomed seahorse valley
echo "2. Seahorse Valley (zoomed)..."
./bin/mandelbrot_openmp 1920 1080 2000 -0.74529 0.11307 0.01 output/regions/seahorse.bmp

# Lightning pattern
echo "3. Lightning pattern..."
./bin/mandelbrot_openmp 1920 1080 1500 -1.25066 0.02012 0.005 output/regions/lightning.bmp

# Mini mandelbrot
echo "4. Mini Mandelbrot..."
./bin/mandelbrot_openmp 1920 1080 3000 -0.15652 1.03225 0.02 output/regions/mini.bmp

# Spiral region
echo "5. Spiral region..."
./bin/mandelbrot_openmp 1920 1080 2000 -0.7269 0.1889 0.004 output/regions/spiral.bmp

# Double spiral
echo "6. Double spiral..."
./bin/mandelbrot_openmp 1920 1080 2500 0.001643721971153 0.822467633298876 0.000000001 output/regions/double_spiral.bmp

echo ""
echo "=== EXPLORATION COMPLETE ==="
echo "Generated files in output/regions/ directory:"
ls -la output/regions/
