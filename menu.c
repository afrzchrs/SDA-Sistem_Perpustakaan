#include "menu.h"

void menu() {
    addressBuku daftarBuku[100];
    int jumlahBuku = 0;
    int pilihan;

    do {
        printf("\n=== Menu Perpustakaan ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Hapus Buku\n");
        printf("3. Tampilkan Daftar Buku dan Antrian\n");
        printf("4. Tambah Peminjam ke Antrian\n");
        printf("5. Cari Peminjam dalam Antrian Buku\n");
        printf("6. Layani Peminjam\n");
        printf("7. Hapus Peminjam \n");
        printf("8. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                tambahBuku(daftarBuku, &jumlahBuku);
                break;

            case 2:
                hapusBuku(daftarBuku, &jumlahBuku);
                break;

            case 3:
                Tampil_List(daftarBuku, jumlahBuku);
                break;

            case 4: {
                if (jumlahBuku == 0) {
                    printf("Belum ada buku yang tersedia!\n");
                    break;
                }

                char judul[100];
                printf("Masukkan judul buku: ");
                scanf("%99s", judul);

                addressBuku target = NULL;
                for (int i = 0; i < jumlahBuku; i++) {
                    if (strcmp(daftarBuku[i]->judul, judul) == 0) {
                        target = daftarBuku[i];
                        break;
                    }
                }

                if (target == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    break;
                }

                addressPeminjam p;
                Create_Peminjam(&p);

                char nama[100];
                int prioritas;
                printf("Masukkan nama peminjam: ");
                scanf("%99s", nama);
                printf("Masukkan prioritas (semakin kecil, semakin prioritas): ");
                scanf("%d", &prioritas);

                Isi_Peminjam(&p, nama, prioritas);
                Ins_Antrian(&target, p);
                printf("Peminjam '%s' ditambahkan ke antrian buku '%s'.\n", nama, target->judul);
                break;
            }

            case 5: {
                if (jumlahBuku == 0) {
                    printf("Belum ada buku.\n");
                    break;
                }

                char judul[100], namaCari[100];
                printf("Masukkan judul buku: ");
                scanf("%99s", judul);
                printf("Masukkan nama peminjam yang ingin dicari: ");
                scanf("%99s", namaCari);

                addressBuku target = NULL;
                for (int i = 0; i < jumlahBuku; i++) {
                    if (strcmp(daftarBuku[i]->judul, judul) == 0) {
                        target = daftarBuku[i];
                        break;
                    }
                }

                if (target == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    break;
                }

                addressPeminjam hasil = Search(target->antrianDepan, namaCari);
                if (hasil != NULL) {
                    printf("Peminjam '%s' ditemukan dalam antrian buku '%s'.\n", namaCari, judul);
                } else {
                    printf("Peminjam '%s' tidak ditemukan dalam antrian buku '%s'.\n", namaCari, judul);
                }
                break;
            }

            case 6: {
                char judul[100], namaTerhapus[100];
                printf("Masukkan judul buku: ");
                scanf("%99s", judul);

                addressBuku target = NULL;
                for (int i = 0; i < jumlahBuku; i++) {
                    if (strcmp(daftarBuku[i]->judul, judul) == 0) {
                        target = daftarBuku[i];
                        break;
                    }
                }

                if (target == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    break;
                }

                Del_Peminjam(&target, namaTerhapus);
                printf("Peminjam '%s' telah dihapus dari antrian.\n", namaTerhapus);
                break;
            }

            case 7: {
                char judul[100], namaTarget[100];
                printf("Masukkan judul buku: ");
                scanf("%99s", judul);
                printf("Masukkan nama peminjam yang ingin dihapus: ");
                scanf("%99s", namaTarget);

                addressBuku target = NULL;
                for (int i = 0; i < jumlahBuku; i++) {
                    if (strcmp(daftarBuku[i]->judul, judul) == 0) {
                        target = daftarBuku[i];
                        break;
                    }
                }

                if (target == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    break;
                }

                addressPeminjam p = target->antrianDepan;
                Del_PeminjamTertentu(&target, namaTarget, &p);
                printf("Jika ditemukan, peminjam '%s' telah dihapus dari antrian.\n", namaTarget);
                break;
            }

            case 8:
                printf("Terima kasih telah menggunakan sistem perpustakaan.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 8);
}
