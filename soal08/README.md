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

## 🛠️ Cara Kompilasi dan Menjalankan

### Prerequisites
- **Compiler**: Clang (disarankan) atau GCC dengan dukungan C17
- **Platform**: macOS, Linux, atau sistem Unix-like

### Kompilasi

```bash
# Build menggunakan script yang disediakan
chmod +x build.sh
./build.sh

# Atau build manual
clang -std=c17 -O2 requiem.c -o requiem
```

### Menjalankan

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

## 🧪 Pengujian dan Validasi

### Test Cases

| Input A | Input B | Output yang Diharapkan | Tipe Test |
|---------|---------|----------------------|-----------|
| `12` | `34` | `408` | Dasar |
| `123` | `456` | `56088` | Menengah |
| `999` | `999` | `998001` | Besar |
| `0` | `123` | `0` | Edge Case |

### Testing Otomatis

```bash
# Membuat dan menjalankan test suite
cat > run_tests.sh << 'TESTEOF'
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
TESTEOF

chmod +x run_tests.sh && ./run_tests.sh
```

## 📊 Spesifikasi Teknis

### Karakteristik Performa
- **Algoritma**: Perkalian grade-school dengan optimasi
- **Kompleksitas Waktu**: O(N²) dimana N = jumlah digit
- **Kompleksitas Ruang**: O(N) dengan batas MAXD = 1000 digit
- **Penggunaan Memori**: ~8KB untuk array + minimal stack

### Teknik Optimasi
1. **Tabel Perkalian Prekomputasi**: `mul10[10][10]` menghilangkan perkalian runtime
2. **Tabel Split Digit**: `split_lo[100]`, `split_hi[100]` untuk handling carry yang cepat
3. **Representasi LSB-first**: Arah propagasi carry yang natural
4. **Kontrol Berbasis Goto**: Menghilangkan overhead loop

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

## 🐛 Troubleshooting

### Masalah Kompilasi
**Error: `clang: command not found`**
```bash
# Install Xcode Command Line Tools (macOS)
xcode-select --install

# Install GCC (Linux)
sudo apt install gcc  # Ubuntu
```

### Masalah Runtime
**Program crash dengan input besar**
- Periksa batas MAXD = 1000 digit
- Input yang terlalu panjang akan menyebabkan overflow

## 📈 Tips Optimasi

1. **Compiler optimization**: Gunakan `-O2` atau `-O3` untuk performa optimal
2. **Input validation**: Tambahkan validasi input untuk robustness
3. **Memory alignment**: Pertimbangkan alignment untuk performa cache yang lebih baik

---
**Author:** 18223105  
**Course:** Sister (Sistem Terdistribusi)  
**Institution:** Institut Teknologi Bandung

---

> *"Dalam kenangan loop konvensional - di sinilah terbaring `for`, `while`, dan `do-while`. Hiduplah `goto`."*  
> — Filosofi Requiem
