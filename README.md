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
Erlinda Annisa Zahra | 5027241108
... | 5027241xxx
Dimas Satya Andhika | 5027241032

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

Thread atau utas merupakan unit terkecil dalam eksekusi proses dalam sistem operasi modern. Thread memungkinkan sebuah proses untuk terbagi menjadi beberapa jalur eksekusi independen yang dapat berjalan secara paralel, baik dalam satu inti prosesor (single core) maupun beberapa inti prosesor (multi-core). Penggunaan thread sangat penting dalam pengembangan aplikasi yang membutuhkan efisiensi dan responsivitas tinggi, seperti server jaringan, sistem real-time, dan komputasi paralel.
<br>
<br>
Lee dan Hurson (1994) menjelaskan bahwa dalam konteks multithreading, "a thread is a sequence of statically ordered instructions where once the first instruction is executed, the remaining instructions execute without interruption" (p. 34). Artinya, thread adalah aliran instruksi yang dieksekusi secara berurutan dan memiliki jalur logika tersendiri dalam pelaksanaan suatu proses.
<br>
<br>
Salah satu keunggulan thread adalah kemampuannya untuk berbagi memori dan sumber daya dengan thread lain dalam proses yang sama, sehingga komunikasi antarthread menjadi lebih cepat dibandingkan komunikasi antarproses (inter-process communication). Namun, karena thread berjalan secara bersamaan dan berbagi sumber daya yang sama, maka perlu diterapkan teknik sinkronisasi seperti mutex (mutual exclusion) agar tidak terjadi konflik (race condition).
<br>
<br>
Dalam lingkungan komputasi modern, multithreading telah menjadi pendekatan umum dalam pengembangan perangkat lunak, baik dalam sistem operasi, aplikasi desktop, maupun layanan cloud. Selain meningkatkan performa, penggunaan thread juga mempermudah pemrosesan tugas-tugas secara simultan (concurrent), seperti menangani banyak permintaan pengguna pada aplikasi server.

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

Mutual exclusion (eksklusi mutual) adalah salah satu konsep paling mendasar dalam sinkronisasi proses pada sistem komputasi paralel dan terdistribusi. Konsep ini mengatur agar hanya satu proses yang dapat memasuki critical section (bagian kritis dari kode yang mengakses sumber daya bersama) pada satu waktu, sehingga menghindari konflik akses atau kondisi tidak konsisten terhadap sumber daya bersama.
<br>
<br>
Menurut Lamport (1986), masalah mutual exclusion pertama kali dijelaskan dan diselesaikan oleh Dijkstra. Dalam perumusan awalnya, "there is a collection of asynchronous processes, each alternately executing a critical and a noncritical section, that must be synchronized so that no two processes ever execute their critical sections concurrently" (Lamport, 1986, p. 313). Hal ini menunjukkan bahwa eksklusi mutual merupakan fondasi utama dari hampir seluruh mekanisme sinkronisasi proses dalam lingkungan paralel. Bahkan, Lamport menegaskan bahwa hampir semua model formal pemrosesan paralel dan mekanisme komunikasi antarproses secara implisit membutuhkan eksklusi mutual dalam implementasinya.
<br>
<br>
Pada sistem terdistribusi, tantangan eksklusi mutual menjadi lebih kompleks karena tidak adanya memori bersama antar node, dan komunikasi hanya dapat dilakukan melalui pertukaran pesan. Suzuki dan Kasami (1985) menyatakan bahwa, "the problem is to design a distributed algorithm that realizes a mutual exclusion requirement that, at any moment, at most one node may stay in its critical section" (Suzuki & Kasami, 1985, p. 344). Ini menekankan pentingnya rancangan algoritma eksklusi mutual yang dapat menjamin tidak adanya dua node yang berada dalam critical section pada saat bersamaan, meskipun keterbatasan komunikasi dan tidak adanya penyimpanan bersama.
<br>
<br>
Beberapa metode telah dikembangkan untuk mengimplementasikan mutual exclusion, baik menggunakan pendekatan terpusat (centralized), berbasis token (token ring atau privilege transfer seperti pada algoritma Suzuki–Kasami), maupun pendekatan berbasis voting atau quorum. Semua pendekatan ini memiliki satu tujuan yang sama, yaitu menjamin bahwa hanya satu proses yang dapat mengakses sumber daya kritis pada waktu tertentu, serta mencegah kondisi deadlock, starvation, dan race condition.

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

https://github.com/user-attachments/assets/a8c0502e-c86e-46de-9bf1-023989d38516

## Daftar Pustaka

<li>Lee, B. and Hurson, A.R., 1994. Dataflow architectures and multithreading. Computer, 27(8), pp.27–38. Available at: https://doi.org/10.1109/2.303784 [Accessed 23 Jun. 2025].</li>
<li>Lamport, L., 1986. The mutual exclusion problem: Part I – A theory of interprocess communication. Journal of the ACM, 33(2), pp.313–326. Available at: https://doi.org/10.1145/5383.5384 [Accessed 23 Jun. 2025]. </li>
<li>Suzuki, I. and Kasami, T., 1985. A distributed mutual exclusion algorithm. ACM Transactions on Computer Systems, 3(4), pp.344–349. Available at: https://doi.org/10.1145/6110.214406 [Accessed 23 Jun. 2025]. </li>
