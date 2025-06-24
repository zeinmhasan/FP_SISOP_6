# Final Project Sistem Operasi IT

## Peraturan
1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok 6

Nama | NRP
--- | ---
zein muhammad hasan | 5027241035
... | 5027241xxx
... | 5027241xxx
... | 5027241xxx

## Deskripsi Soal : MUTEX/THREAD Dragon Plush™ Sale

Sebuah toko mainan sedang mengadakan diskon besar-besaran untuk boneka Dragon Plush™. Dalam program ini, kamu diminta untuk membuat simulasi penjualan Dragon Plush™ menggunakan konsep Thread dan Mutex (Mutual Exclusion).

### Aturan Simulasi:

<ul>
  <li>Program akan menerima dua input dari user:
    <ul>
      <li>Jumlah pembeli (misal: 3)</li>
      <li>Jumlah Dragon Plush™ yang tersedia (misal: 15)</li>
    </ul>
  </li>
  <li>Setiap pembeli akan membeli 5 Dragon Plush™, dan pembeli dianggap "rakus".</li>
  <li>Setiap pembeli diwakili oleh sebuah thread, dan memiliki ID unik (contoh: Pembeli 1, Pembeli 2, dst).</li>
  <li>Gunakan <strong>mutex</strong> untuk menjamin tidak terjadi race condition.</li>
  <li>Ketika satu pembeli sedang membeli, pembeli lainnya harus menunggu giliran (satu pembeli membeli 5 item sekaligus sebelum pembeli berikutnya).</li>
  <li>Setiap kali terjadi pembelian, tampilkan pesan seperti:</li>

  ```
Pembeli 1 membeli Dragon Plush™ ke-1
Pembeli 1 membeli Dragon Plush™ ke-2
...
Pembeli 1 membeli Dragon Plush™ ke-5
```

<li>Jika ada pembeli yang ingin membeli tetapi stok sudah habis, tampilkan:</li>

```
Pembeli 3: Dragon Plush™ habis
```

</ul>


Struktur Direktori:
```
src/        -> Source code utama
bin/        -> File binary hasil kompilasi
```

## Pengerjaan

**Thread**

Soal yang Terkait Thread : <br>
Setiap pembeli diwakili oleh sebuah thread, dan memiliki ID unik (contoh: Pembeli 1, Pembeli 2, dst).

**Teori**

Thread adalah unit terkecil dalam eksekusi suatu proses yang memungkinkan beberapa instruksi dijalankan secara paralel. Thread digunakan untuk memecah pekerjaan menjadi bagian-bagian kecil yang bisa berjalan secara bersamaan untuk meningkatkan efisiensi.

**Solusi**

```c
pthread_t threads[jumlah_pembeli];

for (int i = 0; i < jumlah_pembeli; i++) {
    int* id_pembeli = malloc(sizeof(int));
    *id_pembeli = i + 1;
    pthread_create(&threads[i], NULL, &proses_pembelian, id_pembeli);
}

for (int i = 0; i < jumlah_pembeli; i++) {
    pthread_join(threads[i], NULL);
}

```

**Mutual Exclusion**

Soal yang Terkait Mutual Exclusion : <br>
Gunakan mutex untuk menjamin tidak terjadi race condition. Artinya, jika Pembeli 1 duluan, maka dia akan membeli 5 kali terlebih dahulu, lalu pembeli berikutnya.



**Teori**

Mutual exclusion (mutex) adalah teknik penguncian yang digunakan untuk mencegah lebih dari satu thread mengakses bagian kritis dari kode (critical section) secara bersamaan, sehingga mencegah kondisi tidak konsisten (race condition).

**Solusi**

```c
pthread_mutex_t mutex_pembelian;
pthread_mutex_init(&mutex_pembelian, NULL);

pthread_mutex_lock(&mutex_pembelian);  // Kunci sebelum akses shared data

// Critical Section: akses dan modifikasi sisa_plush
if (sisa_plush > 0) {
    sisa_plush--;
    // ...
}

pthread_mutex_unlock(&mutex_pembelian);  // Buka kunci

```

**Video Menjalankan Program**
...

## Daftar Pustaka

Sitasi 1
Sitasi 2
Sitasi 3
