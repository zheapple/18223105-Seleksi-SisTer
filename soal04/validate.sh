#!/bin/bash
echo "=== Mandelbrot Validation Test ==="
echo "Running quick validation tests to ensure all implementations work correctly..."
echo ""

# Build first if needed
if [ ! -f "bin/mandelbrot_serial" ]; then
    echo "Building executables first..."
    ./build.sh
    echo ""
fi

# Test with small parameters for quick validation
WIDTH=400
HEIGHT=300
MAX_ITER=100

echo "Test parameters: ${WIDTH}x${HEIGHT}, max_iter=${MAX_ITER}"
echo "Output directory: output/"
echo ""

# Create output directory
mkdir -p output

# Test serial
echo "Testing serial implementation..."
if ./bin/mandelbrot_serial $WIDTH $HEIGHT $MAX_ITER -0.75 0.0 3.0 output/test_serial.bmp 2>/dev/null; then
    echo "✓ Serial implementation: OK"
else
    echo "✗ Serial implementation: FAILED"
fi

# Test threading
echo "Testing threading implementation..."
if THREADS=2 ./bin/mandelbrot_threads $WIDTH $HEIGHT $MAX_ITER -0.75 0.0 3.0 output/test_threads.bmp 2>/dev/null; then
    echo "✓ Threading implementation: OK"
else
    echo "✗ Threading implementation: FAILED"
fi

# Test OpenMP
echo "Testing OpenMP implementation..."
if OMP_NUM_THREADS=2 ./bin/mandelbrot_openmp $WIDTH $HEIGHT $MAX_ITER -0.75 0.0 3.0 output/test_openmp.bmp 2>/dev/null; then
    echo "✓ OpenMP implementation: OK"
else
    echo "✗ OpenMP implementation: FAILED"
fi

echo ""
echo "=== VALIDATION COMPLETE ==="

# Check generated files
echo "Generated test files in output/ directory:"
for file in output/test_*.bmp; do
    if [ -f "$file" ]; then
        size=$(ls -lh "$file" | awk '{print $5}')
        echo "  $(basename $file) ($size)"
    fi
done
