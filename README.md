# 🎓 Seleksi Lab Sister ITB 2025 - 18223105

Repository ini berisi solusi lengkap untuk soal-soal seleksi Laboratorium Sister (Sistem Terdistribusi) Institut Teknologi Bandung tahun 2025. Setiap soal dikerjakan dengan pendekatan yang berbeda untuk mendemonstrasikan kemampuan teknis dan pemahaman konsep yang mendalam.

## 👨‍🎓 Profil Kandidat

**NIM:** 18223105  
**Nama:** [Nama Lengkap]  
**Program Studi:** Teknik Informatika  
**Institusi:** Institut Teknologi Bandung  
**Email:** 18223105@std.stei.itb.ac.id

## 📚 Struktur Repository

```
18223105-Seleksi-SisTer/
├── README.md                   # Dokumentasi utama (file ini)
├── soal01/                     # Instalasi GNU/Linux Arch Linux
│   ├── README.md              # Dokumentasi instalasi lengkap
│   ├── 18223105_B_1_1_GNU.pdf # Laporan instalasi
│   ├── Sister-BCM.png         # Screenshot sistem terinstal
│   └── VBox.log              # Log VirtualBox
├── soal04/                     # Mandelbrot Set Fractal Generator  
│   ├── README.md              # Dokumentasi parallelisasi
│   ├── src/                   # Source code implementations
│   │   ├── mandelbrot_serial.cpp
│   │   ├── mandelbrot_openmp.cpp
│   │   ├── mandelbrot_threads.cpp
│   │   └── mandelbrot_util.hpp
│   ├── bin/                   # Compiled executables
│   ├── output/                # Generated fractal images
│   └── *.sh                   # Build & benchmark scripts
├── soal05/                     # Business Capability Model (BCM)
│   ├── README.md              # Dokumentasi BCM
│   ├── 18223105_B_1_5_BCM*.pdf # Laporan BCM lengkap
│   ├── Sister-BCM.archimate   # Model ArchiMate
│   └── Sister-BCM.png         # Visualisasi BCM
└── soal08/                     # Requiem - Perkalian Bilangan Besar
    ├── README.md              # Dokumentasi algoritma
    ├── requiem.c              # Source code C
    ├── requiem               # Executable
    └── build.sh              # Build script
```

## 🎯 Ringkasan Soal dan Solusi

### 💻 **Soal 01: Instalasi GNU/Linux**
**Objective:** Instalasi Arch Linux dengan archinstall di VirtualBox

**Key Features:**
- ✅ GNOME Desktop Environment dengan GUI lengkap
- ✅ Audio-visual capabilities untuk multimedia
- ✅ NetworkManager untuk koneksi internet stabil  
- ✅ User `lab-assistant` dengan sudo privileges
- ✅ Firefox, VS Code, dan Neofetch terinstal
- ✅ Dokumentasi lengkap dengan screenshots

**Tech Stack:** Arch Linux, VirtualBox, GNOME, archinstall

---

### 🖼️ **Soal 04: Mandelbrot Set Fractal Generator**
**Objective:** Implementasi parallelisasi dengan perbandingan performa

**Key Features:**
- 🚀 **3 Implementasi Paralel**: Serial, OpenMP, Manual Threading
- 📊 **Benchmarking Otomatis** dengan metrics performa lengkap
- 🎨 **Output Visual** dalam format BMP resolution tinggi
- ⚡ **Optimasi Performa** dengan compiler flags dan threading tuning
- 📈 **Speedup Analysis** hingga 2.73x improvement

**Tech Stack:** C++17, OpenMP, std::thread, BMP imaging

**Performance Results:**
| Implementation | Threads | Time (ms) | Speedup | Efficiency |
|----------------|---------|-----------|---------|------------|
| Serial         | 1       | 1298.81   | 1.00x   | 100%       |
| Threading      | 4       | 474.95    | 2.73x   | 68%        |
| OpenMP         | 8       | 487.35    | 2.66x   | 33%        |

---

### 🏢 **Soal 05: Business Capability Model (BCM)**
**Objective:** Pemodelan kemampuan bisnis SIAK-NG UI dengan CMMI framework

**Key Features:**
- 📋 **CMMI Maturity Levels** (1-5) untuk capability assessment
- 🏗️ **ArchiMate Modeling** dengan tool profesional
- 🎯 **4 Core Components**: Academic Lifecycle, Core Services, Supporting Capabilities, Infrastructure
- 📊 **Comprehensive Analysis** dengan capability mapping
- 💡 **"Baka!! Chuunibyou Mode"** creative theming approach

**Tech Stack:** ArchiMate, CMMI Framework, Business Process Modeling

**Core Capabilities:**
- Academic Lifecycle Management
- Course Registration & Records Management  
- Examination & Evaluation Systems
- User Management & Security Compliance
- Infrastructure & Technology Management

---

### 🔢 **Soal 08: Requiem - Perkalian Bilangan Besar**
**Objective:** Implementasi algoritma non-konvensional dengan constraints khusus

**Key Features:**
- 🔧 **Pure Bitwise Operations** tanpa operator aritmatika standar
- 🔄 **Goto-based Control Flow** menggantikan loop tradisional
- ⚡ **Lookup Table Optimization** untuk perkalian dan digit splitting
- 🚀 **O(N²) Complexity** dengan optimasi prekomputasi
- 💾 **Fixed-size Arrays** dengan manajemen memori manual

**Tech Stack:** C17, Clang/GCC, Bitwise arithmetic

**Algorithm Highlights:**
- Custom `u8_add()` dan `u8_sub()` dengan carry/borrow propagation
- Precomputed `mul10[][]` multiplication table
- `split_lo[]` dan `split_hi[]` untuk digit extraction
- LSB-first digit representation untuk efisiensi

## 🛠️ Quick Start Guide

### Prerequisites
```bash
# macOS/Linux Development Environment
- Git untuk version control
- Clang/GCC untuk kompilasi C/C++
- VirtualBox untuk virtualisasi
- ArchiMate tool untuk modeling (optional)
```

### Clone Repository
```bash
git clone https://github.com/zheapple/18223105-Seleksi-SisTer.git
cd 18223105-Seleksi-SisTer
```

### Build All Projects
```bash
# Soal 04: Mandelbrot Generator
cd soal04
chmod +x build.sh && ./build.sh
./benchmark.sh

# Soal 08: Requiem
cd ../soal08  
chmod +x build.sh && ./build.sh
./requiem 123456789 987654321
```

## 📊 Technical Highlights

### **Programming Languages Used**
- **C++17** - Advanced parallelization dengan modern C++ features
- **C17** - Low-level bitwise programming dengan optimization
- **Bash** - Automation scripts dan system administration
- **ArchiMate** - Business capability modeling

### **Key Technologies & Frameworks**
- **OpenMP** - Parallel computing framework
- **std::thread** - Manual thread management
- **VirtualBox** - Hardware virtualization
- **GNOME** - Linux desktop environment
- **CMMI** - Capability maturity model integration

### **Development Best Practices**
- ✅ **Comprehensive Documentation** dengan README per soal
- ✅ **Version Control** dengan Git workflow yang proper
- ✅ **Code Quality** dengan compiler optimizations (-O2, -O3)
- ✅ **Performance Benchmarking** dengan automated testing
- ✅ **Cross-platform Compatibility** (macOS, Linux)

## 🎓 Learning Outcomes

### **System Administration Skills**
- Linux installation dan configuration
- VirtualBox virtualization management
- Network dan user management
- System troubleshooting dan optimization

### **High-Performance Computing**
- Parallel programming dengan OpenMP dan threading
- Performance analysis dan benchmarking  
- Memory optimization dan cache efficiency
- Scalability analysis dengan multiple cores

### **Software Architecture**
- Business capability modeling dengan CMMI
- Enterprise architecture dengan ArchiMate
- System integration planning
- Maturity assessment frameworks

### **Algorithm Design**
- Non-conventional programming approaches
- Bitwise operation optimization
- Memory management dalam constraints
- Complexity analysis dan optimization

## 🏆 Achievement Summary

| Kategori | Pencapaian |
|----------|------------|
| **Soal Dikerjakan** | 4/8 soal (50% completion rate) |
| **Dokumentasi** | Komprehensif dengan README per soal |
| **Code Quality** | Production-ready dengan optimizations |
| **Performance** | Benchmarking dengan measurable improvements |
| **Innovation** | Creative approaches dalam constraints |

## 🌐 Online Documentation

### **Blog & Social Media**
- 📝 **Medium Blog**: Technical deep-dive articles
- 📱 **Instagram**: Visual documentation dan progress updates  
- 💻 **GitHub**: Complete source code dengan commit history
- 🔗 **LinkedIn**: Professional portfolio showcase

### **Additional Resources**
- 📹 **Demo Videos** menunjukkan aplikasi running
- 📊 **Performance Charts** dari benchmarking results
- 🖼️ **Screenshots Gallery** dari setiap tahap implementasi
- 📋 **Technical Reports** dalam format PDF

## 📞 Contact Information

**Email:** 18223105@std.stei.itb.ac.id  
**GitHub:** [@zheapple](https://github.com/zheapple)  
**LinkedIn:** [zheannettaapple](linkedin.com/in/zheannettaapple)
**Medium:** [@18223105](https://medium.com/@18223105)

## 📄 License

This project is created for educational purposes as part of ITB Sister Lab selection process 2025. All code is available under MIT License for learning and reference.

---

**© 2025 - 18223105 | Institut Teknologi Bandung | Lab Sister Seleksi**

> *"Exploring distributed systems through hands-on implementation and creative problem solving."*
