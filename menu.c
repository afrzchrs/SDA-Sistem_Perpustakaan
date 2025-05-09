#include "menu.h"
void Menu() {
	addressBuku daftarBuku = NULL;
    addressPeminjam daftarPeminjam = NULL;
    int pilihan;
    char buffer[100];
    do {
        printf("\n===== MENU PERPUSTAKAAN =====\n");
	    printf("1. Tambah Buku\n");
	    printf("2. Tambah Peminjam\n");
	    printf("3. Tampilkan Antrian Buku\n");
	    printf("4. Cari Peminjam\n");
	    printf("5. Kembalikan Buku atau batal antri(Hapus Peminjam)\n");
	    printf("6. Tampilkan Jumlah Peminjam\n");
	    printf("0. Keluar\n");
	    printf("Pilih menu:  ");
        scanf("%d", &pilihan);
        getchar(); // menangkap newline agar tidak mengganggu input berikutnya

        switch (pilihan) {
            case 1: {
                char judul[100];
                int stok;
                printf("Masukkan judul buku: ");
                fgets(judul, sizeof(judul), stdin);
                judul[strcspn(judul, "\n")] = '\0'; // hapus newline

                printf("Masukkan jumlah stok: ");
                scanf("%d", &stok);
                getchar();

                Ins_Buku(&daftarBuku, judul, stok);
                printf("Buku berhasil ditambahkan.\n");
                break;
            }
            case 2: {
                if (daftarBuku == NULL) {
                    printf("Belum ada buku. Tambahkan buku terlebih dahulu.\n");
                    break;
                }

                char nama[100];
                int prioritas, indeksBuku = 0;
                addressBuku temp = daftarBuku;

                printf("Masukkan nama peminjam: ");
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = '\0';

                printf("Prioritas (1=Dosen, 2=Mahasiswa, 3=Umum): ");
                scanf("%d", &prioritas);
                getchar();

                printf("Pilih buku yang ingin dipinjam:\n");
                int i = 1;
                while (temp != NULL) {
                    printf("%d. %s (Stok: %d)\n", i++, temp->judul, temp->stok);
                    temp = temp->next;
                }

                printf("Pilihan buku (nomor): ");
                scanf("%d", &indeksBuku);
                getchar();

                temp = daftarBuku;
                for (i = 1; temp != NULL && i < indeksBuku; i++) {
                    temp = temp->next;
                }

                if (temp == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    break;
                }

                addressPeminjam p;
                Create_Peminjam(&p);
                Isi_Peminjam(&p, nama, prioritas);
                Ins_Antrian(&daftarPeminjam, p, temp);

                printf("Peminjam berhasil ditambahkan ke antrian.\n");
                break;
            }
            case 3:
                if (daftarBuku == NULL) {
                    printf("Belum ada buku.\n");
                } else {
                    Tampil_List(daftarPeminjam, daftarBuku);
                }
                break;
            case 4: {
                char cari[100];
                printf("Masukkan nama peminjam yang dicari: ");
                fgets(cari, sizeof(cari), stdin);
                cari[strcspn(cari, "\n")] = '\0';

                addressPeminjam hasil = Search(daftarPeminjam, cari);
                if (hasil != NULL) {
                    printf("Peminjam ditemukan: %s (Prioritas %d)\n", hasil->nama, hasil->prioritas);
                } else {
                    printf("Peminjam tidak ditemukan.\n");
                }
                break;
            }
            case 5: {
                char hapus[100];
                printf("Masukkan nama peminjam yang mengembalikan buku: ");
                fgets(hapus, sizeof(hapus), stdin);
                hapus[strcspn(hapus, "\n")] = '\0';

                Del_PeminjamTertentu(&daftarPeminjam, hapus);
                printf("Peminjam \"%s\" telah dihapus dari antrian.\n", hapus);
                break;
            }
            case 6: {
                int total = NbElmt(daftarPeminjam);
                printf("Jumlah peminjam saat ini: %d\n", total);
                break;
            }
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 0);

    return 0;
}
