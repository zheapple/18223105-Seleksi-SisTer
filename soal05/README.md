# Soal 05: Business Capability Model (BCM) - SIAK-NG UI Academic Information System

Dokumen Business Capability Model (BCM) untuk SIAK-NG UI (Sistem Informasi Akademik New Generation Universitas Indonesia) yang menggunakan kerangka kerja CMMI (Capability Maturity Model Integration) dalam konteks "Baka!! Chuunibyou Mode".

## 📊 Deskripsi

Business Capability Model (BCM) ini mendefinisikan kemampuan bisnis yang diperlukan untuk mendukung operasional sistem informasi akademik SIAK-NG UI. Model ini dikembangkan dengan pendekatan CMMI untuk memastikan kematangan proses dan kemampuan organisasi dalam mengelola sistem informasi akademik.

### Komponen Utama BCM SIAK-NG UI

BCM SIAK-NG UI terdiri dari empat komponen utama yang saling terintegrasi. **Academic Lifecycle Management** berfokus pada pengelolaan siklus hidup akademik mahasiswa, memastikan kepatuhan terhadap kebijakan akademik, dan meningkatkan pengalaman pengguna sistem. **Core Academic Services** mencakup layanan inti seperti Course Registration Management (KRS), Academic Records Management, Examination & Evaluation, Scheduling Engine, dan Tuition & Payment Processing yang menjadi tulang punggung operasional akademik. 

**Supporting Capabilities** menyediakan dukungan operasional melalui User Profile & Access Management, Notifications & Alerts, Reporting & Analytics, dan System Integration Management yang memungkinkan sistem berjalan dengan efektif. Sedangkan **Infrastructure & Technology** menangani aspek teknis dengan IT Infrastructure Management, Application Development & Maintenance, Security & Compliance, dan Data Management yang memastikan sistem berjalan dengan stabil dan aman.

## 🏗️ Struktur Dokumen

```
soal05/
├── 18223105_B_1_5_BCM - Baka!! Chuunibyou Mode.pdf  # Dokumen BCM lengkap
├── Sister-BCM.archimate                              # Model ArchiMate
├── Sister-BCM.png                                    # Visualisasi model
└── README.md                                         # Dokumentasi ini
```

## 📋 maturity level CMMI

Model ini menggunakan 5 maturity level CMMI:

1. **Initial** - Proses ad-hoc dan tidak terkontrol
2. **Managed** - Proses dikelola pada level proyek
3. **Defined** - Proses terstandardisasi di organisasi
4. **Quantitatively Managed** - Proses diukur dan dikontrol secara kuantitatif
5. **Optimizing** - Fokus pada peningkatan berkelanjutan

## 🎯 Capability Areas

BCM SIAK-NG UI mencakup berbagai kemampuan bisnis yang saling terintegrasi untuk mendukung operasional sistem informasi akademik secara menyeluruh. Kemampuan-kemampuan ini meliputi Course Registration Management dengan Request & Approval KRS dan Prerequisite Validation, Academic Records Management yang mencakup Grade Entry & Update serta Transcript Generation, Examination & Evaluation dengan Exam Scheduling dan Exam Result Management, Tuition & Payment Processing melalui Billing Management, Virtual Account Payment Integration, dan Payment Status Tracking. Sistem juga didukung oleh Scheduling Engine, User Profile & Access Management dengan Authentication Service dan Role-Based Access Control (RBAC), System Integration Management melalui API Gateway Management dan External Service Integration, IT Infrastructure Management yang mencakup Server & Network Management serta Cloud Resource Management, Application Development & Maintenance dengan Development Pipeline dan Quality Assurance & Testing, Security & Compliance melalui Security Monitoring dan Compliance Management, Data Management dengan Backup & Recovery, serta Reporting & Analytics dengan Admin Dashboard dan Report Generator yang semuanya bekerja secara sinergis untuk memastikan sistem akademik berjalan dengan optimal, aman, dan dapat diandalkan.

## 📄 File Dokumen

### 1. **18223105_B_1_5_BCM - Baka!! Chuunibyou Mode.pdf**
Dokumen utama yang berisi:
- Analisis lengkap Business Capability Model
- Mapping kemampuan dengan maturity level
- Rekomendasi implementasi
- Assessment framework

### 2. **Sister-BCM.archimate**
Model ArchiMate yang berisi:
- Definisi capability dalam format XML
- Relationship antar kemampuan
- Struktur hierarki BCM
- Metadata untuk setiap elemen

### 3. **Sister-BCM.png**
Visualisasi grafis atau hasil export dari archimate.

## 🔍 Analisis BCM

Model ini memberikan panduan untuk:

1. **Assessment Kemampuan Saat Ini**
   - Evaluasi kematangan setiap capability area
   - Identifikasi gap dan area improvement

2. **Roadmap Pengembangan**
   - Prioritas pengembangan berdasarkan business value
   - Tahapan implementasi yang terstruktur

3. **Governance Framework**
   - KPI dan metrik untuk setiap capability
   - Struktur tata kelola yang jelas

## 📚 Referensi

- ArchiMate 3.1 Specification
- Business Capability Modeling Best Practices
- Academic Information System Architecture Patterns

---

**Note**: Dokumen ini merupakan bagian dari Seleksi Sister 2025 - Soal 05, yang fokus pada pemodelan kemampuan bisnis untuk sistem informasi akademik SIAK-NG UI menggunakan kerangka kerja enterprise architecture.
