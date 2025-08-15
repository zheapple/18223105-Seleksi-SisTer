# Requiem - BigInteger Multiplication

> **Soal08**: Low-level implementation of arbitrary-precision integer multiplication using bitwise operations and goto-based control flow.

[![Language](https://img.shields.io/badge/language-C17-blue.svg)](https://en.wikipedia.org/wiki/C17_(C_standard_revision))
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-macOS-lightgrey.svg)](https://www.apple.com/macos/)

## 📖 Overview

**Requiem** is a specialized implementation of big integer multiplication that demonstrates:

- ✨ **Bitwise Arithmetic**: All mathematical operations implemented using bitwise operations only
- 🔄 **Goto-based Control Flow**: No traditional loops - all control flow via `goto` statements
- 🚀 **Lookup Table Optimization**: Precomputed tables for fast digit multiplication and splitting
- 🔢 **Manual Memory Management**: Fixed-size arrays with LSB-first digit representation

This project showcases unconventional programming techniques while maintaining optimal performance for educational purposes.

## 🏗️ Architecture

### Algorithm Complexity
- **Time Complexity**: `O(N²)` where N is the number of digits
- **Space Complexity**: `O(N)` with maximum capacity of 1000 digits
- **Optimization**: Precomputed multiplication and digit-split lookup tables

### Key Components

| Component | Description |
|-----------|-------------|
| `u8_add()` | Bitwise addition using carry propagation |
| `u8_sub()` | Bitwise subtraction using borrow propagation |
| `mul10[][]` | 10×10 precomputed multiplication table |
| `split_lo[]` | Lower digit extraction (0-99 → 0-9) |
| `split_hi[]` | Higher digit extraction (0-99 → 0-9) |

## 📁 Project Structure

```
soal08/
├── requiem.c       # Source implementation (170 lines)
├── requiem         # Compiled binary executable
├── build.sh        # Build automation script
└── README.md       # This documentation
```

## 🚀 Quick Start

### Prerequisites
- **Compiler**: Clang (recommended) or GCC with C17 support
- **Platform**: macOS, Linux, or Unix-like systems
- **Memory**: Minimal requirements (< 1MB)

### Installation

1. **Clone and navigate to the project**:
   ```bash
   cd /path/to/18223105-Seleksi-SisTer/soal08
   ```

2. **Build using the provided script**:
   ```bash
   chmod +x build.sh
   ./build.sh
   ```

3. **Or build manually**:
   ```bash
   clang -std=c17 -O2 requiem.c -o requiem
   ```

### Basic Usage

```bash
# Interactive mode
./requiem

# Example session:
# Masukkan angka pertama: 123
# Masukkan angka kedua: 456
# Output: 56088
```

```bash
# Automated input via pipe
echo -e "999\n999" | ./requiem
# Output: 998001
```

## 🧪 Testing

### Test Cases

| Input A | Input B | Expected Output | Test Type |
|---------|---------|-----------------|-----------|
| `12` | `34` | `408` | Basic |
| `123` | `456` | `56088` | Medium |
| `999` | `999` | `998001` | Large |
| `0` | `123` | `0` | Edge Case |
| `9` | `9` | `81` | Single Digit |

### Automated Testing

```bash
# Create and run test suite
cat > run_tests.sh << 'EOF'
#!/bin/bash
echo "🧪 Testing Requiem..."

test_case() {
    local result=$(echo -e "$1" | ./requiem)
    if [ "$result" = "$2" ]; then
        echo "✅ PASS: $1 → $result"
    else
        echo "❌ FAIL: $1 → $result (expected: $2)"
    fi
}

test_case "12\n34" "408"
test_case "123\n456" "56088"  
test_case "999\n999" "998001"
test_case "0\n123" "0"
EOF

chmod +x run_tests.sh && ./run_tests.sh
```

### Performance Benchmarking

```bash
# Measure execution time
time echo -e "123456789\n987654321" | ./requiem

# Memory usage analysis  
/usr/bin/time -l echo -e "999999999\n999999999" | ./requiem
```

## 🔧 Development

### Build Options

```bash
# Debug build with symbols
clang -std=c17 -g -O0 requiem.c -o requiem_debug

# Optimized production build
clang -std=c17 -O3 -march=native requiem.c -o requiem_fast

# With sanitizers for debugging
clang -std=c17 -fsanitize=address -fsanitize=undefined requiem.c -o requiem_safe
```

### Code Analysis

```bash
# Generate assembly output
clang -S -std=c17 -O2 requiem.c -o requiem.s

# Analyze binary
objdump -d requiem | head -50

# Code statistics
echo "Lines of code: $(wc -l < requiem.c)"
echo "Goto statements: $(grep -c goto requiem.c)"
echo "Bitwise operations: $(grep -c 'u8_add\|u8_sub' requiem.c)"
```

### Debugging

```bash
# Interactive debugging with LLDB
lldb ./requiem_debug
# (lldb) run
# (lldb) breakpoint set -f requiem.c -l 100
# (lldb) continue
```

## � Technical Specifications

### Performance Characteristics
- **Algorithm**: Grade-school multiplication with optimizations
- **Time Complexity**: O(N²) where N = number of digits
- **Space Complexity**: O(N) with MAXD = 1000 digit limit
- **Memory Usage**: ~8KB for arrays + minimal stack

### Implementation Details

#### Bitwise Arithmetic Functions
```c
unsigned char u8_add(unsigned char a, unsigned char b);  // Addition via XOR + carry
unsigned char u8_sub(unsigned char a, unsigned char b);  // Subtraction via XOR + borrow  
unsigned char inc(unsigned char x);                      // Increment wrapper
unsigned char dec(unsigned char x);                      // Decrement wrapper
```

#### Optimization Techniques
1. **Precomputed Multiplication Table**: `mul10[10][10]` eliminates runtime multiplication
2. **Digit Split Tables**: `split_lo[100]`, `split_hi[100]` for fast carry handling
3. **LSB-first Representation**: Natural carry propagation direction
4. **Goto-based Control**: Eliminates loop overhead

### Platform Compatibility

| Platform | Compiler | Status |
|----------|----------|--------|
| macOS ARM64 | Clang 15+ | ✅ Tested |
| macOS x86_64 | Clang 15+ | ✅ Tested |
| Linux x86_64 | GCC 9+ | ✅ Compatible |
| Linux ARM64 | GCC 9+ | ✅ Compatible |

## 🎓 Educational Value

This implementation demonstrates several advanced programming concepts:

### Low-Level Programming Techniques
- **Manual Memory Management**: Fixed-size arrays without dynamic allocation
- **Bitwise Operations**: Arithmetic implemented using logical operations only
- **Unconventional Control Flow**: Structured programming via `goto` statements
- **Performance Optimization**: Lookup tables and algorithmic improvements

### Computer Science Concepts
- **Big Integer Arithmetic**: Handling numbers beyond native type limits
- **Algorithm Analysis**: Understanding time/space complexity trade-offs
- **Code Optimization**: Balancing readability vs. performance
- **System Programming**: Low-level C programming without standard library dependencies

## 🔍 Code Examples

### Input Processing
```c
// Convert string to LSB-first digit array
j = 0;
i = dec(la);  // Start from last character
FILL_A:
    A[j] = sa[i] & 0x0F;  // Extract digit
    if (i == 0) goto END_FILL_A;
    i = dec(i);
    j = inc(j);
    goto FILL_A;
```

### Multiplication Core
```c
// O(N²) multiplication with lookup optimization
prod = mul10[A[i]][B[j]];        // Precomputed product
t = u8_add(R[i+j], prod);        // Add to result
t = u8_add(t, carry);            // Include carry
d = split_lo[t];                 // Extract low digit
c = split_hi[t];                 // Extract carry
```

## 🤝 Contributing

This is an educational project for learning purposes. Key areas for exploration:

1. **Algorithm Variants**: Implement Karatsuba or FFT-based multiplication
2. **Platform Porting**: Test on different architectures
3. **Performance Analysis**: Detailed benchmarking and profiling
4. **Code Visualization**: Generate control flow graphs from goto statements

## 📜 License

This project is part of the **18223105-Seleksi-SisTer** academic assignment.

## 📞 Support

- **Student ID**: 18223105
- **Repository**: [18223105-Seleksi-SisTer](https://github.com/zheapple/18223105-Seleksi-SisTer)
- **Assignment**: Soal08 - Requiem

---

> *"In memory of conventional loops - here lies `for`, `while`, and `do-while`. Long live `goto`."*  
> — The Requiem Philosophy