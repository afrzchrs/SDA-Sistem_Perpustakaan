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

    b[*jmlhBuku] = bukuBaru;
    (*jmlhBuku)++;
    printf("Buku '%s' berhasil ditambahkan!\n", bukuBaru->judul);
}

void tampilDaftarBuku(addressBuku b[], int jmlhBuku) {
    printf("\nDaftar Buku:\n");
    if (jmlhBuku == 0) {
        printf("Tidak ada buku.\n");
        return;
    }
    
    for (int i = 0; i < jmlhBuku; i++) {
        printf("%d. Judul: %s, Stok: %d\n", i+1, b[i]->judul, b[i]->stok);
    }
}

