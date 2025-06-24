#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Untuk usleep (opsional, untuk simulasi)

// === Variabel Global ===
// Variabel yang akan diakses oleh semua thread (critical section)
int sisa_plush; 

// Mutex untuk melindungi akses ke variabel sisa_plush
pthread_mutex_t mutex_pembelian;

// Fungsi yang akan dijalankan oleh setiap thread (pembeli)
void* proses_pembelian(void* arg) {
    // Ambil ID pembeli dari argumen dan bebaskan memori setelahnya
    int id_pembeli = *((int*)arg);
    free(arg);

    // Setiap pembeli akan mencoba membeli sebanyak 5 plush
    int jumlah_ingin_dibeli = 5;

    // --- CRITICAL SECTION START ---
    // Kunci mutex sebelum mengakses/mengubah sisa_plush
    // Jika mutex sedang digunakan thread lain, thread ini akan menunggu.
    pthread_mutex_lock(&mutex_pembelian);

    printf("Pembeli %d masuk untuk membeli...\n", id_pembeli);

    for (int i = 0; i < jumlah_ingin_dibeli; i++) {
        // Cek ketersediaan stok di setiap percobaan pembelian
        if (sisa_plush > 0) {
            sisa_plush--;
            printf("   -> Pembeli %d berhasil membeli 1 Dragon Plush™. (Sisa stok: %d)\n", id_pembeli, sisa_plush);
            // usleep(100000); // Jeda kecil untuk simulasi agar lebih mudah dibaca
        } else {
            // Jika dalam proses membeli ternyata stok habis
            printf("   -> Pembeli %d: Yah, Dragon Plush™ sudah habis!\n", id_pembeli);
            break; // Keluar dari loop pembelian untuk pembeli ini
        }
    }
    
    printf("Pembeli %d selesai.\n\n", id_pembeli);

    // Buka kunci mutex agar thread lain bisa melanjutkan
    pthread_mutex_unlock(&mutex_pembelian);
    // --- CRITICAL SECTION END ---

    return NULL;
}

int main() {
    int jumlah_pembeli;
    int jumlah_plush_awal;

    // --- Input dari User ---
    printf("--- MUTEX/THREAD Dragon Plush™ Sale ---\n");
    printf("Masukkan jumlah pembeli: ");
    scanf("%d", &jumlah_pembeli);

    printf("Masukkan jumlah Dragon Plush™ yang tersedia: ");
    scanf("%d", &jumlah_plush_awal);
    printf("------------------------------------------\n\n");

    sisa_plush = jumlah_plush_awal;

    // --- Inisialisasi Thread dan Mutex ---
    pthread_t threads[jumlah_pembeli];

    // Inisialisasi mutex, return 0 jika sukses
    if (pthread_mutex_init(&mutex_pembelian, NULL) != 0) {
        printf("Inisialisasi mutex gagal.\n");
        return 1;
    }

    // --- Membuat Thread untuk setiap pembeli ---
    for (int i = 0; i < jumlah_pembeli; i++) {
        // Alokasikan memori untuk ID pembeli agar setiap thread punya ID unik
        int* id_pembeli = malloc(sizeof(int));
        if (id_pembeli == NULL) {
            perror("Gagal alokasi memori untuk ID");
            return 1;
        }
        *id_pembeli = i + 1; // ID pembeli dimulai dari 1

        // Buat thread baru yang akan menjalankan fungsi proses_pembelian
        if (pthread_create(&threads[i], NULL, &proses_pembelian, id_pembeli) != 0) {
            printf("Gagal membuat thread untuk pembeli %d.\n", i + 1);
            return 1;
        }
    }

    // --- Menunggu semua thread selesai ---
    for (int i = 0; i < jumlah_pembeli; i++) {
        pthread_join(threads[i], NULL);
    }

    // --- Cleanup ---
    // Hancurkan mutex setelah tidak digunakan lagi
    pthread_mutex_destroy(&mutex_pembelian);

    printf("------------------------------------------\n");
    printf("Semua pembelian telah selesai. Sisa akhir Dragon Plush™: %d\n", sisa_plush);

    return 0;
}
