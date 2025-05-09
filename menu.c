#include "menu.h"

void menu() {
    addressBuku daftarBuku[100]; 
    int jumlahBuku = 0;
    addressPeminjam daftarPeminjam = NULL;

    int pilihan;
    do {
        printf("\n=== MENU PERPUSTAKAAN ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Lihat Daftar Buku\n");
        printf("3. Tampilkan Daftar Buku dan Antrian\n");
        printf("4. Tambah Peminjam ke Antrian\n");
        printf("5. Cari Peminjam dalam Antrian Buku\n");
        printf("6. Layani Peminjam\n");
        printf("7. Hapus Peminjam\n");
        printf("8. Hapus Buku");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); 
        switch (pilihan) {
            case 1:
                tambahBuku(daftarBuku, &jumlahBuku);
                break;

            case 2:
                tampilDaftarBuku(daftarBuku, jumlahBuku);
                break;
                
            case 3:
                Tampil_List(daftarPeminjam);
                break;

            case 4: {
                if (jumlahBuku == 0) {
                    printf("Belum ada buku. Tambahkan buku terlebih dahulu!\n");
                    break;
                }

                char nama[100];
                int prioritas, idx;

                printf("Masukkan nama peminjam: ");
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;

                printf("Prioritas (1=Dosen, 2=Mahasiswa, 3=Umum): ");
                scanf("%d", &prioritas);

                tampilDaftarBuku(daftarBuku, jumlahBuku);
                printf("Pilih nomor buku yang ingin dipinjam: ");
                scanf("%d", &idx);
                getchar();

                if (idx < 1 || idx > jumlahBuku) {
                    printf("Pilihan buku tidak valid.\n");
                    break;
                }

                addressPeminjam pBaru;
                Create_Peminjam(&pBaru);
                Isi_Peminjam(&pBaru, nama, prioritas, daftarBuku[idx - 1]);
                Ins_Antrian(&daftarPeminjam, pBaru);
                printf("Peminjam '%s' berhasil ditambahkan ke antrian.\n", nama);
                break;
            }
            case 5: {
                char namaCari[100];
                printf("Masukkan nama peminjam yang ingin dicari: ");
                fgets(namaCari, sizeof(namaCari), stdin);
                namaCari[strcspn(namaCari, "\n")] = 0;

                addressPeminjam hasil = Search(daftarPeminjam, namaCari);
                if (hasil != NULL) {
                    printf("Peminjam ditemukan: %s (Prioritas: %d)\n", hasil->nama, hasil->prioritas);
                    if (hasil->bukuDipinjam != NULL)
                        printf("Sedang mengantri untuk buku: %s\n", hasil->bukuDipinjam->judul);
                } else {
                    printf("Peminjam tidak ditemukan dalam antrian.\n");
                }
                break;
            }
            case 6:{
            	char nama[100];
                printf("Masukkan nama peminjam yang ingin dilayani: ");
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;
                Del_Peminjam(&daftarPeminjam, nama);
                break;
				break;
			}
            
            case 7: {
                char nama[100];
                printf("Masukkan nama peminjam yang ingin dihapus: ");
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;
                Del_PeminjamTertentu(&daftarPeminjam, nama);
                break;
            }

            case 8:
                hapusBuku(daftarBuku, &jumlahBuku, &daftarPeminjam);
                break;

            case 0:
                printf("Terima kasih telah menggunakan sistem perpustakaan.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }

    } while (pilihan != 0);
}

