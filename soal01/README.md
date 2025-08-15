# Soal 01: Instalasi GNU/Linux Arch Linux dengan archinstall di VirtualBox

Dokumentasi lengkap proses instalasi Arch Linux menggunakan script `archinstall` di VirtualBox untuk keperluan seleksi Lab Sister ITB 2025.

## 📋 Deskripsi

Soal ini mengharuskan instalasi distribusi GNU/Linux Arch Linux menggunakan script instalasi otomatis `archinstall` di dalam mesin virtual VirtualBox. Arch Linux dipilih karena sifatnya yang minimalis dan memberikan kontrol penuh kepada pengguna, cocok untuk pembelajaran sistem operasi tingkat lanjut.

## 🎯 Tujuan Pembelajaran

1. **Pemahaman Virtualisasi** - Menggunakan VirtualBox untuk virtualisasi sistem operasi
2. **Linux Distribution** - Memahami karakteristik Arch Linux sebagai rolling release distribution
3. **Installation Process** - Menguasai proses instalasi Linux menggunakan archinstall script
4. **System Administration** - Dasar-dasar administrasi sistem Linux
5. **Documentation** - Mendokumentasikan proses instalasi dengan screenshot

## 🛠️ Prerequisites

### Hardware Requirements
- **RAM:** Minimal 2GB, direkomendasikan 4GB+
- **Storage:** Minimal 20GB free space
- **CPU:** Mendukung virtualisasi (VT-x/AMD-V)

### Software Requirements
- **VirtualBox 7.0+** 
- **Arch Linux ISO** (terbaru dari https://archlinux.org/download/)
- **Koneksi Internet** stabil untuk download packages

### Download Links
```bash
# VirtualBox
https://www.virtualbox.org/wiki/Downloads

# Arch Linux ISO
https://archlinux.org/download/
# Mirror Indonesia: https://mirror.gi.co.id/archlinux/iso/latest/
```

## ⚙️ Setup VirtualBox

### 1. Membuat Virtual Machine Baru

1. **Buka VirtualBox Manager**
2. **Klik "New"** untuk membuat VM baru
3. **Konfigurasi dasar:**
   - **Name:** `ArchLinux-Sister`
   - **Type:** Linux
   - **Version:** Arch Linux (64-bit)
   - **Memory:** 2048 MB (minimum), 4096 MB (recommended)

### 2. Konfigurasi Storage

1. **Create Virtual Hard Disk**
   - **Size:** 20 GB (minimum), 30 GB (recommended)
   - **Type:** VDI (VirtualBox Disk Image)
   - **Storage:** Dynamically allocated

2. **Mount Arch Linux ISO**
   - Settings → Storage
   - Controller IDE → Empty
   - Klik disk icon → Choose a disk file
   - Select Arch Linux ISO file

### 3. Network Settings

```
Settings → Network
├── Adapter 1: NAT (default)
└── Advanced → Port Forwarding (optional untuk SSH)
```

### 4. System Settings

```
Settings → System
├── Processor: 2 cores (recommended)
├── Acceleration: VT-x/AMD-V enabled
└── Boot Order: Hard Disk, Optical
```

### 5. Display Settings

```
Settings → Display
├── Video Memory: 128 MB
└── Graphics Controller: VMSVGA
```

## 🚀 Proses Instalasi Arch Linux

### 1. Boot dari ISO

1. **Start VM** dari VirtualBox Manager
2. **Boot Menu** akan muncul, pilih:
   ```
   Arch Linux install medium (x86_64, BIOS)
   ```
3. **Tunggu loading** hingga muncul prompt root

### 2. Verifikasi Koneksi Internet

```bash
# Test koneksi internet
ping -c 3 archlinux.org

# Jika tidak ada koneksi, check network interface
ip link show

# Enable interface jika perlu
ip link set enp0s3 up
dhcpcd enp0s3
```

### 3. Update System Clock

```bash
# Sinkronisasi waktu sistem
timedatectl set-ntp true

# Verifikasi status
timedatectl status
```

### 4. Menjalankan archinstall

```bash
# Jalankan script instalasi interaktif
archinstall
```

### 5. Konfigurasi archinstall

Script `archinstall` akan menanyakan beberapa konfigurasi:

#### **Mirror Selection**
```
Select mirror region: Indonesia
```

#### **Disk Configuration**
```
Drive: /dev/sda (20 GB VirtualBox disk)
Disk layout: 
├── Boot partition: 512 MB (FAT32)
├── Root partition: 18+ GB (ext4)
└── Swap: 2 GB (optional)

Partitioning: Use entire disk
Filesystem: ext4 (recommended)
```

#### **Disk Encryption (Optional)**
```
Encrypt drive: No (untuk kemudahan)
# Atau "Yes" jika ingin pembelajaran encryption
```

#### **Hostname**
```
Hostname: archlinux-sister
```

#### **Root Password**
```
Root password: [set strong password]
Confirm password: [repeat password]
```

#### **User Account**
```
Create user: yes
Username: sister
Password: [set password]
Admin privileges: yes (sudo access)
```

#### **Profile Selection**
```
Profile: Desktop
Desktop: GNOME (recommended untuk pemula)
# Alternatif: KDE Plasma, XFCE, i3
```

#### **Audio Driver**
```
Audio: PulseAudio (default)
```

#### **Kernel**
```
Kernel: linux (stable kernel)
```

#### **Additional Packages**
```
Additional packages (space-separated):
firefox git vim nano htop neofetch base-devel
```

#### **Network Configuration**
```
Network: NetworkManager (recommended)
```

#### **Timezone**
```
Timezone: Asia/Jakarta
```

#### **Optional Repositories**
```
Enable multilib: yes
```

### 6. Konfirmasi dan Mulai Instalasi

1. **Review konfigurasi** yang telah dipilih
2. **Confirm installation** dengan mengetik `yes`
3. **Tunggu proses instalasi** (15-30 menit tergantung koneksi)

### 7. Post Installation

```bash
# Setelah instalasi selesai
# Remove ISO dari VM settings
# Restart VM

# Login dengan user yang dibuat
# Username: sister
# Password: [password yang dibuat]
```

## 📸 Screenshots Dokumentasi

Berdasarkan file yang ada di folder soal01:

1. **`Screen Shot 2025-08-15 at 00.16.10.png`** - Screenshot tahap awal instalasi
2. **`Screen Shot 2025-08-15 at 00.37.13.png`** - Screenshot proses konfigurasi archinstall
3. **`Screen Shot 2025-08-15 at 01.16.56.png`** - Screenshot sistem yang sudah terinstall

## 🔧 Post-Installation Setup

### 1. First Boot

```bash
# Login sebagai user biasa (bukan root)
# Update sistem
sudo pacman -Syu

# Install additional packages
sudo pacman -S wget curl git vim
```

### 2. Install VirtualBox Guest Additions

```bash
# Install guest additions untuk integrasi VirtualBox
sudo pacman -S virtualbox-guest-utils

# Enable guest services
sudo systemctl enable vboxservice.service

# Reboot untuk aktivasi
sudo reboot
```

### 3. Network Configuration

```bash
# Check network status
systemctl status NetworkManager

# Connect to network jika belum
nmcli device wifi list
nmcli device wifi connect "SSID" password "password"
```

### 4. Desktop Environment Setup

```bash
# Jika menggunakan GNOME
# Install additional GNOME applications
sudo pacman -S gnome-tweaks gnome-extensions-app

# Enable GNOME Display Manager
sudo systemctl enable gdm.service
```

## 📊 Verifikasi Instalasi

### System Information

```bash
# Check OS info
cat /etc/os-release
uname -a

# Check hardware
lscpu
free -h
lsblk

# Check services
systemctl list-unit-files --state=enabled
```

### Performance Test

```bash
# Install benchmarking tools
sudo pacman -S htop iotop

# Check system performance
htop

# Disk usage
df -h
du -sh /*
```

## 🐛 Troubleshooting

### Common Issues

#### **Boot Issues**
```bash
# Jika gagal boot setelah instalasi
# Boot dari ISO lagi, mount root partition
mount /dev/sda2 /mnt
arch-chroot /mnt

# Reinstall bootloader
grub-install /dev/sda
grub-mkconfig -o /boot/grub/grub.cfg
```

#### **Network Issues**
```bash
# Jika tidak ada internet di VM
systemctl start NetworkManager
systemctl enable NetworkManager

# Manual IP configuration
ip link set enp0s3 up
dhcpcd enp0s3
```

#### **Graphics Issues**
```bash
# Jika display resolution tidak sesuai
# Install VirtualBox guest additions
sudo pacman -S virtualbox-guest-utils
sudo reboot
```

### VirtualBox Specific Issues

#### **VM Won't Start**
- Check virtualization enabled in BIOS
- Increase RAM allocation
- Check available disk space

#### **Slow Performance**
- Enable VT-x/AMD-V in VM settings
- Increase video memory to 128MB
- Install guest additions

## 📝 Laporan Instalasi Sistem GNU/Linux

### **Distribusi:** Arch Linux  
### **Metode Instalasi:** archinstall  
### **Platform:** VirtualBox pada macOS

---

## I. Pendahuluan

Dokumen ini disusun sebagai laporan hasil instalasi sistem operasi GNU/Linux, yang merupakan bagian dari persyaratan tugas yang diberikan. Instalasi ini menggunakan Arch Linux dengan skrip pembantu `archinstall` untuk mempermudah proses. Proses instalasi dilakukan pada sebuah mesin virtual yang dikelola oleh VirtualBox di sistem operasi macOS. Pemilihan metode ini bertujuan untuk mencapai kriteria penilaian 2 poin sambil mendokumentasikan setiap tahapan secara komprehensif.

## II. Spesifikasi dan Pemenuhan

Tabel berikut merangkum status pemenuhan seluruh spesifikasi wajib dan bonus yang dikerjakan, dilengkapi dengan deskripsi spesifik dari implementasi yang dilakukan.

| Spesifikasi | Status | Deskripsi Implementasi |
|-------------|--------|------------------------|
| **Graphical User Interface (GUI)** | ✅ Terpenuhi | Lingkungan desktop GNOME berhasil diinstal, menyediakan antarmuka grafis yang lengkap dan fungsional. |
| **Kapabilitas Audio-visual** | ✅ Terpenuhi | Sistem dikonfigurasi dengan driver grafis dan audio yang mendukung pemutaran video secara lancar di peramban web. |
| **Koneksi Internet** | ✅ Terpenuhi | Konfigurasi jaringan dikelola oleh NetworkManager, memastikan konektivitas internet stabil tanpa intervensi manual pasca-instalasi. |
| **Manajemen Paket** | ✅ Terpenuhi | Sistem menggunakan manajer paket `pacman`, yang diverifikasi melalui instalasi aplikasi seperti Firefox dan Visual Studio Code. |
| **Pengguna Biasa (unprivileged)** | ✅ Terpenuhi | Sebuah akun pengguna non-root, `lab-assistant`, dibuat untuk seluruh aktivitas operasional sehari-hari. |
| **Graphical Text Editor** | ✅ Terpenuhi | Aplikasi Visual Studio Code diinstal sebagai editor teks grafis utama. |
| **Graphical Web Browser** | ✅ Terpenuhi | Aplikasi Firefox berhasil diinstal untuk keperluan penjelajahan web. |
| **Wallpaper** | ✅ Terpenuhi | Tampilan wallpaper desktop telah disesuaikan dengan kriteria tugas. |
| **Skrip Bash Neofetch** | ✅ Terpenuhi | Skrip bash untuk menginstal dan menjalankan Neofetch berhasil dibuat dan dieksekusi oleh pengguna biasa. |
| **Poin Bonus** | 🔄 (Jika dikerjakan) | *(Catatan: Dokumentasi untuk spesifikasi bonus akan dilampirkan secara terpisah.)* |

### Verifikasi Komponen Sistem

```bash
# Informasi sistem final
OS: Arch Linux x86_64
Kernel: Linux 6.x.x-arch1-1
DE: GNOME 45+
WM: Mutter
Shell: bash 5.2.x
Terminal: gnome-terminal
Package Manager: pacman 6.x
User Account: lab-assistant (with sudo privileges)
```

## III. Prosedur Instalasi

### 1. **Persiapan Lingkungan**

Proses dimulai dengan mengunduh berkas `.iso` Arch Linux dari mirror resmi. Sebuah mesin virtual baru dibuat pada VirtualBox dengan spesifikasi berikut:

- **RAM:** 2 GB (2048 MB)
- **Storage:** 20 GB (VDI, dynamically allocated)
- **Network:** NAT dengan NetworkManager
- **Graphics:** VMSVGA controller

### 2. **Eksekusi archinstall**

Setelah booting dari media instalasi, skrip `archinstall` dijalankan dengan konfigurasi sebagai berikut:

#### **Konfigurasi Sistem:**
- **Mirrors:** Mirror dari Indonesia untuk optimalisasi kecepatan download
- **Disk:** Partisi otomatis (default partition layout) dengan filesystem ext4
- **Bootloader:** GRUB sebagai bootloader utama
- **Hostname:** `archlinux-sister`

#### **Konfigurasi Pengguna:**
- **Root password:** Dikonfigurasi untuk keamanan sistem
- **User account:** `lab-assistant` dengan hak sudo penuh
- **User password:** Dikonfigurasi sesuai standar keamanan

#### **Konfigurasi Desktop:**
- **Profile:** Desktop environment
- **DE Selection:** GNOME (lengkap dengan aplikasi default)
- **Display Manager:** GDM (GNOME Display Manager)

#### **Konfigurasi Jaringan & Waktu:**
- **Network Manager:** NetworkManager untuk manajemen koneksi otomatis
- **Timezone:** Asia/Jakarta
- **NTP Sync:** Aktif untuk sinkronisasi waktu otomatis

### 3. **Pasca-Instalasi dan Perbaikan**

Setelah instalasi selesai, sistem di-reboot tanpa media instalasi. Untuk mengatasi kendala performa video, pengaturan grafis VirtualBox disesuaikan dengan:

- **Graphics Controller:** Diubah menjadi VMSVGA
- **3D Acceleration:** Dinonaktifkan untuk stabilitas
- **Video Memory:** Dialokasikan 128 MB

#### **Instalasi Aplikasi Tambahan:**
```bash
# Update sistem dan install aplikasi wajib
sudo pacman -Syu
sudo pacman -S firefox code neofetch git base-devel

# Install VirtualBox Guest Additions
sudo pacman -S virtualbox-guest-utils
sudo systemctl enable vboxservice.service
```

#### **Konfigurasi Neofetch Script:**
```bash
#!/bin/bash
# Script: install_neofetch.sh
# Install dan jalankan neofetch sebagai user biasa

if ! command -v neofetch &> /dev/null; then
    echo "Installing neofetch..."
    sudo pacman -S neofetch
fi

echo "Running neofetch..."
neofetch
```

## IV. Dokumentasi Visual

### Screenshots Tahapan Instalasi:

1. **`Screen Shot 2025-08-15 at 00.16.10.png`** - Tahap awal boot dan akses archinstall
2. **`Screen Shot 2025-08-15 at 00.37.13.png`** - Proses konfigurasi archinstall dengan menu interaktif
3. **`Screen Shot 2025-08-15 at 01.16.56.png`** - Sistem GNOME yang telah berhasil diinstal dan dikonfigurasi

### VirtualBox Logs:
- **`VBox.log`** - Log lengkap proses virtualisasi dan troubleshooting

## V. Troubleshooting yang Dilakukan

### **Masalah Grafis:**
- **Issue:** Resolusi display tidak optimal dan performa 3D lambat
- **Solution:** Mengubah Graphics Controller ke VMSVGA dan menonaktifkan 3D acceleration

### **Network Configuration:**
- **Issue:** Koneksi internet tidak stabil pada boot pertama
- **Solution:** Restart NetworkManager service dan konfigurasi DHCP otomatis

### **User Permissions:**
- **Verification:** Memastikan user `lab-assistant` memiliki akses sudo yang tepat
- **Testing:** Menjalankan `sudo pacman -S` untuk verifikasi hak akses

## VI. Verifikasi Fungsionalitas

### **GUI Testing:**
```bash
# Test desktop environment
echo $XDG_CURRENT_DESKTOP  # Output: GNOME
loginctl show-session $(loginctl | grep $(whoami) | awk '{print $1}') -p Type
```

### **Audio-Visual Testing:**
- **Browser Video:** YouTube playback test di Firefox
- **Audio Output:** PulseAudio functionality test
- **Graphics:** Desktop effects dan window management

### **Network Connectivity:**
```bash
# Test koneksi internet
ping -c 3 google.com
curl -I https://archlinux.org
```

### **Package Management:**
```bash
# Test pacman functionality
pacman -Q | wc -l  # Jumlah package terinstal
sudo pacman -S htop  # Test instalasi package baru
```

## VII. Kesimpulan

Proyek instalasi Arch Linux ini telah berhasil memenuhi seluruh spesifikasi wajib yang ditetapkan dalam kriteria tugas. Penggunaan `archinstall` terbukti efektif dalam menyederhanakan proses instalasi sambil tetap memberikan kontrol konfigurasi yang diperlukan.

### **Pencapaian:**
- ✅ **Sistem operasi fungsional** dengan GUI lengkap
- ✅ **Semua spesifikasi wajib** terpenuhi dan terverifikasi
- ✅ **Dokumentasi komprehensif** dengan screenshot dan logs
- ✅ **User experience** yang optimal untuk penggunaan sehari-hari

### **Pembelajaran:**
1. **Virtualization best practices** dalam VirtualBox
2. **Arch Linux ecosystem** dan philosophy
3. **Modern installation methods** dengan archinstall
4. **System administration** fundamentals
5. **Documentation standards** untuk proyek teknis

Laporan ini, bersama dengan dokumentasi video dan bukti tangkapan layar, berfungsi sebagai deliverable yang lengkap untuk pemenuhan tugas instalasi sistem GNU/Linux.

## � Dokumentasi Online

### 📝 **Blog Medium**
**Artikel:** "Installing Arch Linux with archinstall on VirtualBox: A Complete Guide"  
**Link:** [Medium Blog Post](https://medium.com/@zheannettaapha/i-use-arch-btw-installing-arch-linux-in-virtualbox-the-smart-way-2cdd9b9bdf90)

**Konten Blog:**
- Detailed step-by-step installation process
- Troubleshooting common VirtualBox issues
- Performance optimization tips
- Comparison: archinstall vs manual installation
- Screenshots with explanations

### 📱 **Instagram Post**
**Post:** Arch Linux Installation Journey  
**Link:** [Instagram Post](https://www.instagram.com/p/DNYU9AsSmyN/?igsh=bWJkdXc1NHplcG0z)

**Konten Instagram:**
- 📸 Story highlights of installation process
- 🎥 Short video demo of GNOME desktop
- 💡 Quick tips in carousel format
- 🏷️ Hashtags: #ArchLinux #Linux #VirtualBox #TechStudent #ITB #SisterLab
- 📝 Caption with key learning points

### 📊 **Engagement Metrics**
```
Blog Medium:
├── Target audience: Linux enthusiasts, students
├── Expected reach: 500+ readers
└── Topics covered: Installation, troubleshooting, tips

Instagram Post:
├── Format: Carousel + Story highlights
├── Target audience: Tech community, fellow students  
├── Hashtags: #ArchLinux #Linux #VirtualBox #ITB
└── Engagement: Comments, shares, saves
```

### 🎯 **Content Strategy**
- **Educational focus:** Help other students with similar tasks
- **Visual documentation:** Screenshots with annotations
- **Problem-solving:** Common issues and solutions
- **Community engagement:** Encourage questions and discussions

## �🎓 Kesimpulan Pembelajaran

### Skill yang Dipelajari

1. **Virtualization:** Setup dan konfigurasi VirtualBox
2. **Linux Installation:** Proses instalasi Arch Linux dengan archinstall
3. **System Administration:** User management, package management
4. **Troubleshooting:** Mengatasi masalah instalasi dan konfigurasi
5. **Documentation:** Membuat dokumentasi teknis dengan screenshot

### Keunggulan archinstall

- **User-friendly:** Lebih mudah dibanding instalasi manual Arch
- **Flexible:** Banyak pilihan konfigurasi
- **Educational:** Tetap memberikan pemahaman tentang komponen sistem
- **Time-efficient:** Instalasi lebih cepat dan reliable

## 📚 Referensi

- [Arch Linux Installation Guide](https://wiki.archlinux.org/title/Installation_guide)
- [archinstall Documentation](https://wiki.archlinux.org/title/Archinstall)
- [VirtualBox User Manual](https://www.virtualbox.org/manual/)
- [Arch Linux Beginner's Guide](https://wiki.archlinux.org/title/General_recommendations)

## 📋 File Terkait

```
soal01/
├── 18223105_B_1_1_GNU.pdf           # Dokumentasi instalasi
├── Screen Shot 2025-08-15 at 00.16.10.png  
├── Screen Shot 2025-08-15 at 00.37.13.png  
├── Screen Shot 2025-08-15 at 01.16.56.png  
├── VBox.log                         # Log VirtualBox
└── README.md                        # Dokumentasi ini
```

---

**Author:** 18223105  
**Course:** Sister (Sistem Terdistribusi)  
**Institution:** Institut Teknologi Bandung  
**Date:** August 15, 2025
