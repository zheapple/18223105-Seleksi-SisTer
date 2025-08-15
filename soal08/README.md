# Soal 08: Requiem - Perkalian Bilangan Besar

Implementasi perkalian bilangan bulat presisi-arbitrer menggunakan operasi bitwise dan kontrol alur berbasis `goto` untuk pembelajaran teknik pemrograman tingkat rendah.

## 📋 Deskripsi Implementasi

**Requiem** adalah implementasi khusus perkalian bilangan besar yang mendemonstrasikan:

- ✨ **Aritmatika Bitwise**: Semua operasi matematika diimplementasikan menggunakan operasi bitwise saja
- 🔄 **Kontrol Alur Goto**: Tidak menggunakan loop tradisional - semua kontrol alur menggunakan statement `goto`
- 🚀 **Optimasi Lookup Table**: Tabel prekomputasi untuk perkalian digit dan pemisahan yang cepat
- 🔢 **Manajemen Memori Manual**: Array ukuran tetap dengan representasi digit LSB-first

Project ini menampilkan teknik pemrograman non-konvensional sambil mempertahankan performa optimal untuk tujuan edukasi.

## 🏗️ Arsitektur dan Kompleksitas

### Kompleksitas Algoritma
- **Kompleksitas Waktu**: `O(N²)` dimana N adalah jumlah digit
- **Kompleksitas Ruang**: `O(N)` dengan kapasitas maksimum 1000 digit
- **Optimasi**: Tabel lookup prekomputasi untuk perkalian dan pemisahan digit

### Komponen Utama

| Komponen | Deskripsi |
|----------|-----------|
| `u8_add()` | Penjumlahan bitwise menggunakan propagasi carry |
| `u8_sub()` | Pengurangan bitwise menggunakan propagasi borrow |
| `mul10[][]` | Tabel perkalian 10×10 yang sudah diprekomputasi |
| `split_lo[]` | Ekstraksi digit rendah (0-99 → 0-9) |
| `split_hi[]` | Ekstraksi digit tinggi (0-99 → 0-9) |

## 📁 Struktur Project

```
soal08/
├── requiem.c       # Implementasi source code (170 baris)
├── requiem         # Executable binary hasil kompilasi
├── build.sh        # Script automasi build
└── README.md       # Dokumentasi ini
```

## 🛠️ Cara Kompilasi dan Instalasi

### Prerequisites
- **Compiler**: Clang (disarankan) atau GCC dengan dukungan C17
- **Platform**: macOS, Linux, atau sistem Unix-like
- **Memory**: Kebutuhan minimal (< 1MB)

### Instalasi

1. **Clone dan navigasi ke project**:
   ```bash
   cd /path/to/18223105-Seleksi-SisTer/soal08
   ```

2. **Build menggunakan script yang disediakan**:
   ```bash
   chmod +x build.sh
   ./build.sh
   ```

3. **Atau build manual**:
   ```bash
   clang -std=c17 -O2 requiem.c -o requiem
   ```

## 🚀 Cara Menjalankan

```bash
# Menjalankan program
./requiem
```

**Contoh sesi penggunaan:**
```
Masukkan angka pertama: 123
Masukkan angka kedua: 456
56088
```

**Input otomatis via pipe:**
```bash
echo -e "123\n456" | ./requiem
```
Output (prompt muncul namun nilai input tidak ter-echo):
```
Masukkan angka pertama: Masukkan angka kedua: 56088
```

## 🧪 Pengujian dan Validasi

### Test Cases

| Input A | Input B | Output yang Diharapkan | Tipe Test |
|---------|---------|----------------------|-----------|
| `12` | `34` | `408` | Dasar |
| `123` | `456` | `56088` | Menengah |
| `999` | `999` | `998001` | Besar |
| `0` | `123` | `0` | Edge Case |
| `9` | `9` | `81` | Digit Tunggal |

**Catatan**: Ketika menggunakan pipe input, prompt muncul tapi nilai input tidak ter-echo ke terminal.

### Testing Otomatis

```bash
# Membuat dan menjalankan test suite
cat > run_tests.sh << 'EOF'
#!/bin/bash
echo "🧪 Testing Requiem..."

test_case() {
    local result=$(echo -e "$1" | ./requiem | tail -1)
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

### Benchmarking Performa

```bash
# Mengukur waktu eksekusi
time echo -e "123456789\n987654321" | ./requiem

# Analisis penggunaan memori
/usr/bin/time -l echo -e "999999999\n999999999" | ./requiem
```

## 🔧 Development dan Debugging

### Opsi Build

```bash
# Debug build dengan simbol debug
clang -std=c17 -g -O0 requiem.c -o requiem_debug

# Optimized production build
clang -std=c17 -O3 -march=native requiem.c -o requiem_fast

# Dengan sanitizers untuk debugging
clang -std=c17 -fsanitize=address -fsanitize=undefined requiem.c -o requiem_safe
```

### Analisis Kode

```bash
# Generate assembly output
clang -S -std=c17 -O2 requiem.c -o requiem.s

# Statistik kode
echo "Baris kode: $(wc -l < requiem.c)"
echo "Statement goto: $(grep -c goto requiem.c)"
echo "Operasi bitwise: $(grep -c 'u8_add\|u8_sub' requiem.c)"
```

### Debugging

```bash
# Interactive debugging dengan LLDB
lldb ./requiem_debug
# (lldb) run
# (lldb) breakpoint set -f requiem.c -l 100
# (lldb) continue
```

## 📊 Spesifikasi Teknis

### Karakteristik Performa
- **Algoritma**: Perkalian grade-school dengan optimasi
- **Kompleksitas Waktu**: O(N²) dimana N = jumlah digit
- **Kompleksitas Ruang**: O(N) dengan batas MAXD = 1000 digit
- **Penggunaan Memori**: ~8KB untuk array + minimal stack

### Detail Implementasi

#### Fungsi Aritmatika Bitwise
```c
unsigned char u8_add(unsigned char a, unsigned char b);  // Penjumlahan via XOR + carry
unsigned char u8_sub(unsigned char a, unsigned char b);  // Pengurangan via XOR + borrow  
unsigned char inc(unsigned char x);                      // Wrapper increment
unsigned char dec(unsigned char x);                      // Wrapper decrement
```

#### Teknik Optimasi
1. **Tabel Perkalian Prekomputasi**: `mul10[10][10]` menghilangkan perkalian runtime
2. **Tabel Split Digit**: `split_lo[100]`, `split_hi[100]` untuk handling carry yang cepat
3. **Representasi LSB-first**: Arah propagasi carry yang natural
4. **Kontrol Berbasis Goto**: Menghilangkan overhead loop

### Kompatibilitas Platform

| Platform | Compiler | Status |
|----------|----------|--------|
| macOS ARM64 | Clang 15+ | ✅ Teruji |
| macOS x86_64 | Clang 15+ | ✅ Teruji |
| Linux x86_64 | GCC 9+ | ✅ Kompatibel |
| Linux ARM64 | GCC 9+ | ✅ Kompatibel |

## 🎓 Nilai Edukasi

Implementasi ini mendemonstrasikan beberapa konsep pemrograman tingkat lanjut:

### Teknik Pemrograman Tingkat Rendah
- **Manajemen Memori Manual**: Array ukuran tetap tanpa alokasi dinamis
- **Operasi Bitwise**: Aritmatika diimplementasikan hanya menggunakan operasi logis
- **Kontrol Alur Non-konvensional**: Pemrograman terstruktur via statement `goto`
- **Optimasi Performa**: Lookup table dan perbaikan algoritma

### Konsep Computer Science
- **Aritmatika Bilangan Besar**: Menangani bilangan di luar batas tipe native
- **Analisis Algoritma**: Memahami trade-off kompleksitas waktu/ruang
- **Optimasi Kode**: Menyeimbangkan readability vs. performa
- **System Programming**: Pemrograman C tingkat rendah tanpa dependency library standar

## 🔍 Contoh Kode

### Pemrosesan Input
```c
// Membaca string input dengan prompt
printf("Masukkan angka pertama: ");
scanf("%s", sa);
printf("Masukkan angka kedua: ");
scanf("%s", sb);

// Konversi string ke array digit LSB-first
j = 0;
i = dec(la);  // Mulai dari karakter terakhir
FILL_A:
    A[j] = sa[i] & 0x0F;  // Ekstrak digit
    if (i == 0) goto END_FILL_A;
    i = dec(i);
    j = inc(j);
    goto FILL_A;
```

### Core Perkalian
```c
// Perkalian O(N²) dengan optimasi lookup
prod = mul10[A[i]][B[j]];        // Produk prekomputasi
t = u8_add(R[i+j], prod);        // Tambah ke hasil
t = u8_add(t, carry);            // Sertakan carry
d = split_lo[t];                 // Ekstrak digit rendah
c = split_hi[t];                 // Ekstrak carry
```

## 🔄 Pengembangan Lanjutan

Project ini adalah project edukasi untuk pembelajaran. Area eksplorasi lebih lanjut:

1. **Varian Algoritma**: Implementasi perkalian Karatsuba atau berbasis FFT
2. **Porting Platform**: Testing pada arsitektur yang berbeda
3. **Analisis Performa**: Benchmarking dan profiling yang detail
4. **Visualisasi Kode**: Generate control flow graph dari statement goto

## 🐛 Troubleshooting

### Masalah Kompilasi
**Error: `clang: command not found`**
```bash
# Install Xcode Command Line Tools (macOS)
xcode-select --install

# Install GCC (Linux)
sudo apt install gcc  # Ubuntu
sudo yum install gcc  # CentOS
```

**Error: `requiem.c:xx: warning: implicit declaration`**
- Pastikan menggunakan `-std=c17` atau yang lebih baru

### Masalah Runtime
**Program crash dengan input besar**
- Periksa batas MAXD = 1000 digit
- Input yang terlalu panjang akan menyebabkan overflow

**Hasil salah pada edge case**
- Validasi dengan test case yang disediakan
- Debug dengan versi debug build

## 📈 Tips Optimasi

1. **Compiler optimization**: Gunakan `-O2` atau `-O3` untuk performa optimal
2. **Input validation**: Tambahkan validasi input untuk robustness
3. **Memory alignment**: Pertimbangkan alignment untuk performa cache yang lebih baik
4. **Lookup table**: Tabel prekomputasi sudah optimal untuk operasi yang sering digunakan

---
**Author:** 18223105  
**Course:** Sister (Sistem Terdistribusi)  
**Institution:** Institut Teknologi Bandung

---

> *"Dalam kenangan loop konvensional - di sinilah terbaring `for`, `while`, dan `do-while`. Hiduplah `goto`."*  
> — Filosofi Requiem