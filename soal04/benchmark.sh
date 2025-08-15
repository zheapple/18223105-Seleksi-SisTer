#!/bin/bash
echo "=== Mandelbrot Benchmarking ==="
echo "Date: $(date)"
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "CPU: $(sysctl -n machdep.cpu.brand_string)"
    echo "Cores: $(sysctl -n hw.ncpu)"
else
    echo "CPU: $(cat /proc/cpuinfo | grep 'model name' | head -1 | cut -d':' -f2)"
    echo "Cores: $(nproc)"
fi
echo ""

# Build first if needed
if [ ! -f "bin/mandelbrot_serial" ]; then
    echo "Building executables first..."
    ./build.sh
    echo ""
fi

# Test parameters
WIDTH=1920
HEIGHT=1080
MAX_ITER=1000

echo "Parameters: ${WIDTH}x${HEIGHT}, max_iter=${MAX_ITER}"
echo "Output directory: output/"
echo ""

# Create output directory
mkdir -p output

# Serial baseline
echo "=== SERIAL BASELINE ==="
./bin/mandelbrot_serial $WIDTH $HEIGHT $MAX_ITER -0.75 0.0 3.0 output/serial_baseline.bmp
echo ""

# Threading tests
echo "=== THREADING TESTS ==="
for threads in 1 2 4 8 16; do
    echo "--- $threads threads ---"
    THREADS=$threads ./bin/mandelbrot_threads $WIDTH $HEIGHT $MAX_ITER -0.75 0.0 3.0 output/threads_${threads}.bmp
    echo ""
done

# OpenMP tests  
echo "=== OPENMP TESTS ==="
for threads in 1 2 4 8 16; do
    echo "--- $threads threads ---"
    OMP_NUM_THREADS=$threads ./bin/mandelbrot_openmp $WIDTH $HEIGHT $MAX_ITER -0.75 0.0 3.0 output/openmp_${threads}.bmp
    echo ""
done

echo "=== BENCHMARKING COMPLETE ==="
echo "Generated files in output/ directory:"
ls -la output/
