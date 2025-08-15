#!/bin/bash
echo "Building Mandelbrot implementations..."

# Create bin directory if it doesn't exist
mkdir -p bin output

# Serial version
echo "Building serial version..."
g++ -std=c++17 -O2 src/mandelbrot_serial.cpp -o bin/mandelbrot_serial

# Threading version  
echo "Building threading version..."
g++ -std=c++17 -O2 -pthread src/mandelbrot_threads.cpp -o bin/mandelbrot_threads

# OpenMP version (macOS)
echo "Building OpenMP version..."
if [[ "$OSTYPE" == "darwin"* ]]; then
    clang++ -std=c++17 -O2 -Xpreprocessor -fopenmp \
            -I/usr/local/opt/libomp/include \
            -L/usr/local/opt/libomp/lib \
            -lomp src/mandelbrot_openmp.cpp -o bin/mandelbrot_openmp
else
    g++ -std=c++17 -O2 -fopenmp src/mandelbrot_openmp.cpp -o bin/mandelbrot_openmp
fi

echo "Build complete!"
echo ""
echo "Available executables:"
ls -la bin/
