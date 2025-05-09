#include "menu.h"

void MenuPerpustakaan() {
    addressBuku bukuList = NULL;
    int pilihan;
    char judul[100];
    int stok;
    char nama[100];
    int prioritas;

    do {
        printf("\n=== MENU PERPUSTAKAAN ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tambah Peminjam ke Antrian Buku\n");
        printf("3. Tampilkan Daftar Buku dan Antrian\n");
        printf("4. Layani Peminjam Terdepan\n");
        printf("5. Pengembalian Buku atau Batalkan Antrian\n");
        printf("6. Cari Peminjam\n");
        printf("7. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar(); // Untuk menangani newline

        switch (pilihan) {
            case 1: {
                addressBuku bukuBaru;
                Create_Buku(&bukuBaru);

                printf("Masukkan Judul Buku: ");
                fgets(judul, sizeof(judul), stdin);
                judul[strcspn(judul, "\n")] = '\0'; // Menghapus newline

                printf("Masukkan Stok Buku: ");
                scanf("%d", &stok);
                getchar();

                Isi_Buku(&bukuBaru, judul, stok);
                bukuBaru->next = bukuList;
                if (bukuList != NULL) {
                    bukuList->prev = bukuBaru;
                }
                bukuList = bukuBaru;
                printf("Buku \"%s\" ditambahkan.\n", judul);
                break;
            }
            case 2: {
                printf("Masukkan Judul Buku: ");
                fgets(judul, sizeof(judul), stdin);
                judul[strcspn(judul, "\n")] = '\0';

                addressBuku temp = bukuList;
                while (temp != NULL && strcmp(temp->judul, judul) != 0) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    addressPeminjam pBaru;
                    Create_Peminjam(&pBaru);

                    printf("Masukkan Nama Peminjam: ");
                    fgets(nama, sizeof(nama), stdin);
                    nama[strcspn(nama, "\n")] = '\0';

                    printf("Masukkan Prioritas (1=Dosen, 2=Mahasiswa, 3=Umum): ");
                    scanf("%d", &prioritas);
                    getchar();

                    Isi_Peminjam(&pBaru, nama, prioritas);
                    Ins_Antrian(&temp, pBaru);
                    printf("Peminjam \"%s\" dimasukkan ke antrian.\n", nama);
                } else {
                    printf("Buku \"%s\" tidak ditemukan.\n", judul);
                }
                break;
            }
            case 3:
                Tampil_List(bukuList);
                break;
            case 4: {
                printf("Masukkan Judul Buku untuk Melayani Peminjam: ");
                fgets(judul, sizeof(judul), stdin);
                judul[strcspn(judul, "\n")] = '\0';

                addressBuku temp = bukuList;
                while (temp != NULL && strcmp(temp->judul, judul) != 0) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    char namaTerhapus[100];
                    Del_Peminjam(&temp, namaTerhapus);
                    if (strcmp(namaTerhapus, "-") != 0)
                        printf("Peminjam \"%s\" telah dilayani.\n", namaTerhapus);
                    else
                        printf("Tidak ada antrian pada buku ini.\n");
                } else {
                    printf("Buku tidak ditemukan.\n");
                }
                break;
            }
            case 5: {
                printf("Masukkan Judul Buku: ");
                fgets(judul, sizeof(judul), stdin);
                judul[strcspn(judul, "\n")] = '\0';

                addressBuku temp = bukuList;
                while (temp != NULL && strcmp(temp->judul, judul) != 0) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    printf("Masukkan Nama Peminjam yang Akan Dihapus: ");
                    fgets(nama, sizeof(nama), stdin);
                    nama[strcspn(nama, "\n")] = '\0';

                    char namaTerhapus[100];
                    Del_PeminjamTertentu(&temp, nama, &(temp->antrianDepan));
                    printf("Peminjam \"%s\" telah dihapus dari antrian.\n", nama);
                } else {
                    printf("Buku tidak ditemukan.\n");
                }
                break;
            }
            case 6:
			    printf("Masukkan Judul Buku: ");
			    fgets(judul, sizeof(judul), stdin);
			    judul[strcspn(judul, "\n")] = '\0';
			
			    addressBuku temp = bukuList;
			    while (temp != NULL && strcmp(temp->judul, judul) != 0) {
			        temp = temp->next;
			    }
			
			    if (temp != NULL) {
			        printf("Masukkan Nama Peminjam yang Dicari: ");
			        fgets(nama, sizeof(nama), stdin);
			        nama[strcspn(nama, "\n")] = '\0';
			
			        addressPeminjam ditemukan = Search(temp->antrianDepan, nama);
			        if (ditemukan != NULL) {
			            printf("Peminjam \"%s\" ditemukan dalam antrian ", ditemukan->nama);
			            if (ditemukan->prioritas == 1) {
			                printf("(Dosen).\n");
			            } else if (ditemukan->prioritas == 2) {
			                printf("(Mahasiswa).\n");
			            } else if (ditemukan->prioritas == 3) {
			                printf("(Umum).\n");
			            }
			        } else {
			            printf("Peminjam \"%s\" tidak ditemukan dalam antrian buku \"%s\".\n", nama, judul);
			        }
			    } else {
			        printf("Buku tidak ditemukan.\n");
			    }
			    break;	
            case 7:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 6);
}
