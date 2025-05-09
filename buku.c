#include "buku.h"

void Create_Buku(addressBuku *b) {
    *b = (addressBuku) malloc(sizeof(buku));
}

void Isi_Buku(addressBuku *b, char judul[], int stok) {
    if (*b != NULL) {
        strcpy((*b)->judul, judul);
        (*b)->stok = stok; 
        (*b)->antrianDepan = NULL;
        (*b)->next = NULL;
    }
}

