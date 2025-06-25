#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

int sisa_plush; 

pthread_mutex_t mutex_pembelian;

void* proses_pembelian(void* arg) {
    int id_pembeli = *((int*)arg);
    free(arg);
    int jumlah_ingin_dibeli = 5;
    pthread_mutex_lock(&mutex_pembelian);
    printf("Pembeli %d masuk untuk membeli...\n", id_pembeli);

    for (int i = 0; i < jumlah_ingin_dibeli; i++) {
        
        if (sisa_plush > 0) {
            sisa_plush--;
            printf("   -> Pembeli %d berhasil membeli 1 Dragon Plush™. (Sisa stok: %d)\n", id_pembeli, sisa_plush);
        } else {
            printf("   -> Pembeli %d: Yah, Dragon Plush™ sudah habis!\n", id_pembeli);
        }
    }
    printf("Pembeli %d selesai.\n\n", id_pembeli);
    pthread_mutex_unlock(&mutex_pembelian);
    return NULL;
}

int main() {
    int jumlah_pembeli;
    int jumlah_plush_awal;

    printf("--- MUTEX/THREAD Dragon Plush™ Sale ---\n");
    printf("Masukkan jumlah pembeli: ");
    scanf("%d", &jumlah_pembeli);

    printf("Masukkan jumlah Dragon Plush™ yang tersedia: ");
    scanf("%d", &jumlah_plush_awal);
    printf("------------------------------------------\n\n");

    sisa_plush = jumlah_plush_awal;

    pthread_t threads[jumlah_pembeli];

    if (pthread_mutex_init(&mutex_pembelian, NULL) != 0) {
        printf("Inisialisasi mutex gagal.\n");
        return 1;
    }
    for (int i = 0; i < jumlah_pembeli; i++) {
        int* id_pembeli = malloc(sizeof(int));
        if (id_pembeli == NULL) {
            perror("Gagal alokasi memori untuk ID");
            return 1;
        }
        *id_pembeli = i + 1; 

        if (pthread_create(&threads[i], NULL, &proses_pembelian, id_pembeli) != 0) {
            printf("Gagal membuat thread untuk pembeli %d.\n", i + 1);
            return 1;
        }
    }
    for (int i = 0; i < jumlah_pembeli; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex_pembelian);

    printf("------------------------------------------\n");
    printf("Semua pembelian telah selesai. Sisa akhir Dragon Plush™: %d\n", sisa_plush);

    return 0;
}
