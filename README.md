# 🌱 Growtopia Simulator: Seed Splicing & Farming Cycle

![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=flat-square&logo=c%2B%2B)
![Course](https://img.shields.io/badge/Mata%20Kuliah-Struktur%20Data-2EA44F?style=flat-square)
![Semester](https://img.shields.io/badge/Semester-Ganjil%202026%2F2027-orange?style=flat-square)

Aplikasi simulasi berbasis console (*Command-Line Interface*) yang mereplikasi mekanik inti dari permainan **Growtopia**, khususnya sistem manajemen *Backpack*, kombinasi bibit (*Seed Splicing*), serta siklus penanaman dan pemanenan pohon (*Farming & Harvesting Cycle*). Proyek ini dibangun menggunakan bahasa **C++** dengan implementasi struktur data linier dan nonlinier secara manual (*from scratch* tanpa container STL seperti `std::list`, `std::queue`, atau `std::vector`).

---

## 🎮 Deskripsi Proyek & Mekanik yang Direplikasi

Dalam game **Growtopia**, pemain mengumpulkan berbagai jenis bibit (*Seed*), memadukan dua *Seed* berbeda untuk menemukan spesies pohon baru (*Splicing*), menanamnya di lahan (*World*), lalu memanennya setelah durasi tumbuh (*Grow Time*) selesai untuk memperoleh *Block*, *Seed* baru, dan *Gems*.

Proyek ini menyederhanakan dan mereplikasi siklus mekanik tersebut ke dalam tiga komponen utama:
1. **Dynamic Backpack Management:** Penyimpanan item dengan kapasitas slot terbatas dan sistem *stacking* (maksimal 200 item per slot) serta kursor navigasi dua arah untuk memilih atau membuang (*trash*) item.
2. **Seed Splicing System:** Mekanisme penggabungan dua jenis *Seed* berbeda berdasarkan jaringan resep. Mendukung pencarian resep maju (*forward splicing*), pencarian balik (*reverse lookup* berdasarkan 1 seed), rekomendasi otomatis berdasarkan isi *Backpack*, hingga penambahan resep *custom*.
3. **FIFO Farm Plot & Harvest Cycle:** Lahan tanam yang memproses pertumbuhan bibit berdasarkan urutan waktu tanam. Pohon yang ditanam lebih awal akan dipanen terlebih dahulu saat waktu tumbuhnya habis.

---

## 🧱 Struktur Data yang Digunakan

Program ini mengombinasikan **dua struktur data linier** dan **satu struktur data nonlinier** yang saling terintegrasi:

| Struktur Data | Tipe | Representasi dalam Game | Justifikasi Pemilihan |
| :--- | :---: | :--- | :--- |
| **Doubly Linked List** (`ListBackpack`) | Linier | **Growtopia Backpack** | Memungkinkan penambahan dan penghapusan slot item secara dinamis saat item baru didapat atau habis dipakai, serta mendukung pergeseran *active slot cursor* dua arah (`prev` dan `next`) seperti *hotbar* di Growtopia. |
| **Queue** (`FarmQueue`) | Linier | **Farm Plot / Lahan Tanam** | Menerapkan prinsip *First-In, First-Out* (FIFO), sehingga bibit pohon hasil *splicing* yang ditanam lebih dulu (`enqueue`) akan diproses dan dipanen lebih awal (`dequeue`) ketika waktu tumbuhnya mencapai `0` detik. |
| **Multi-Linked List** (`ListRecipe`) | Nonlinier | **Splicing Recipe Book** | Memodelkan relasi komposisi **Parent–Child**, di mana node *Parent* (`NodeRecipe`) adalah hasil pohon/seed target dan node *Child* (`NodeIngredient`) adalah komponen *seed* bahan penyusunnya. |

---

## ✨ Fitur Utama Program

1. **Lihat Isi Backpack:** Menampilkan seluruh item dalam *Backpack* beserta ID, kategori (`Seed`/`Block`), tingkat kelangkaan (*Rarity*), jumlah *stack* (`x/200`), dan penanda slot aktif (`<-- [ACTIVE SLOT]`).
2. **Navigasi Kursor Backpack (Kiri / Kanan):** Menggeser pointer `cursor` ke node sebelumnya (`prev`) atau berikutnya (`next`).
3. **Trash Item:** Membuang seluruh *stack* item yang sedang ditunjuk oleh `cursor` dari *Backpack* sekaligus membebaskan slot.
4. **Lihat Semua Resep Splicing:** Melakukan *traversal* pada *Multi-Linked List* untuk menampilkan seluruh daftar *Parent* resep beserta *Child* bahan penyusunnya.
5. **Cari Resep Berdasarkan ID Seed:** Mencari semua kemungkinan resep *splicing* yang melibatkan suatu *Seed* tertentu.
6. **Rekomendasi Splicing Otomatis:** Mencocokkan stok *Seed* di dalam *Backpack* (*Doubly Linked List*) dengan daftar resep (*Multi-Linked List*) untuk menampilkan resep apa saja yang siap di-*splice* saat itu juga.
7. **Splice & Tanam ke Farm Plot:** Memvalidasi dan mengurangi 2 *Seed* berbeda dari *Backpack*, lalu memasukkan bibit pohon hasil kombinasi ke dalam antrean lahan (`enqueue`).
8. **Lihat Status Farm Plot:** Menampilkan antrean pohon yang sedang tumbuh di *World* beserta sisa waktu tumbuhnya.
9. **Simulasi Waktu & Panen Otomatis:** Memajukan waktu permainan dalam satuan detik. Pohon di urutan terdepan yang sisa waktunya `<= 0` akan otomatis dipanen (`dequeue`), memberikan *Block*, *Seed* baru ke *Backpack*, serta tambahan *Gems*.
10. **Tambah Resep Splicing Custom:** Menambahkan node *Parent* resep baru beserta relasi *Child* bahan penyusunnya ke dalam *Multi-Linked List* secara dinamis.

---

## 📂 Struktur File Proyek

```text
growtopia-strukdat/
├── main.cpp               # Entry point program & antarmuka menu console interaktif
├── backpack.h             # Header ADT Doubly Linked List (Growtopia Backpack)
├── backpack.cpp           # Implementasi operasi primitif Doubly Linked List
├── farm_queue.h           # Header ADT Queue (Antrean Farm Plot)
├── farm_queue.cpp         # Implementasi operasi primitif Queue
├── splicing_mll.h         # Header ADT Multi-Linked List (Splicing Recipe Book)
├── splicing_mll.cpp       # Implementasi operasi primitif Multi-Linked List
├── game_mechanics.h       # Header subprogram utama & integrasi mekanik Growtopia
├── game_mechanics.cpp     # Implementasi logika splicing, panen, rekomendasi, & pencarian
└── README.md              # Dokumentasi proyek
```

---

## 🚀 Cara Instalasi dan Menjalankan Program

### Prasyarat
* Compiler C++ yang mendukung standar **C++11** atau lebih baru (seperti `g++` dari MinGW/GCC atau Clang).
* Terminal / Command Prompt / IDE (VS Code, Code::Blocks, Dev-C++).

### Langkah-Langkah Menjalankan

1. **Clone repository ini ke komputer lokal Anda:**
   ```bash
   git clone https://github.com/username-anda/growtopia-strukdat.git
   cd growtopia-strukdat
   ```

2. **Kompilasi seluruh file sumber C++:**
   ```bash
   g++ -std=c++17 main.cpp backpack.cpp farm_queue.cpp splicing_mll.cpp game_mechanics.cpp -o growtopia_sim
   ```

3. **Jalankan program:**
   * **Linux / macOS:**
     ```bash
     ./growtopia_sim
     ```
   * **Windows (CMD / PowerShell):**
     ```powershell
     growtopia_sim.exe
     ```

---

## 🕹️ Contoh Alur Penggunaan Singkat

1. Jalankan program, pemain akan memulai dengan 4 jenis *Seed* dasar di *Backpack* (`Dirt Seed`, `Rock Seed`, `Lava Seed`, dan `Cave Background Seed`) serta `150 Gems`.
2. Pilih menu **`7` (Cek Rekomendasi Seed yang Siap Di-Splice)** untuk melihat kombinasi *Seed* yang tersedia.
3. Pilih menu **`8` (Splice & Tanam 2 Seed)**, lalu masukkan ID `101` (`Dirt Seed`) dan `102` (`Rock Seed`). Sistem akan menanam **Grass Seed Tree** ke dalam `Farm Plot #1`.
4. Pilih menu **`10` (Majukan Waktu & Panen Pohon)** dan masukkan `30` detik. **Grass Seed Tree** akan matang, dipanen otomatis, dan memberikan `Grass Block`, `Grass Seed`, serta bonus `Gems`.
5. Gunakan `Grass Seed` hasil panen tersebut untuk melakukan *splicing* tingkat lanjut (misalnya `Grass Seed` + `Rock Seed` -> `Brick Seed`).

---

## 📝 Catatan Pengembangan (Git Commit Convention)

Untuk memenuhi standar dokumentasi tugas besar, riwayat *commit* pada repository ini disusun secara bertahap mengikuti perkembangan modul:
* `init: setup project structure and README`
* `feat(backpack): implement Doubly Linked List ADT for player inventory`
* `feat(farm): implement Queue ADT for world farm plots`
* `feat(splicing): implement Multi-Linked List ADT for splicing recipes`
* `feat(mechanics): integrate splicing, harvest simulation, and recommendation system`
* `feat(ui): build interactive console menu in main.cpp`