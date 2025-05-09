#include "buku.h"

void inputBuku(char *nama) {
    printf("Masukkan nama Buku: ");
    scanf("%49s", nama); 
}

void inputStok(int *stok){
    printf("Masukkan jumlah stok Buku: ");
    scanf("%d", stok); 
}

void tambahBuku(addressBuku b[], int *jmlhBuku) {
    addressBuku bukuBaru = (addressBuku) malloc(sizeof(buku));
    if (bukuBaru == NULL) {
        return;
    }

    inputBuku(bukuBaru->judul); 
    inputStok(&(bukuBaru->stok)); 
    bukuBaru->antrianDepan = NULL; 

    b[*jmlhBuku] = bukuBaru;
    (*jmlhBuku)++;
    printf("Buku '%s' berhasil ditambahkan!\n", bukuBaru->judul);
}

void hapusBuku(addressBuku b[], int *jmlhBuku) {	
    char hapusJudul[50];
    inputBuku(hapusJudul); 

    int i, found = -1;
    for (i = 0; i < *jmlhBuku; i++) {
        if (strcmp(b[i]->judul, hapusJudul) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Buku '%s' tidak ditemukan!\n", hapusJudul);
        return;
    }

    // Hapus semua peminjam di antrian
    while (b[found]->antrianDepan != NULL) {
        char namaDummy[100];
        Del_Peminjam(&(b[found]), namaDummy);
    }

    free(b[found]); // free memori buku

    // Geser array
    for (i = found; i < (*jmlhBuku) - 1; i++) {
        b[i] = b[i + 1];
    }

    (*jmlhBuku)--;  
    printf("Buku '%s' berhasil dihapus beserta daftar peminjam yang terkait.\n", hapusJudul);
}

