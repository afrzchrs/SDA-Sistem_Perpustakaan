#ifndef BUKU_H
#define BUKU_H

#include "boolean.h"

typedef struct buku{
	char judul[100];
	int stok; 
}buku;

typedef buku* addressBuku;

void tambahBuku(addressBuku b[], int *jmlhBuku);
void inputStok(int *stok);
void inputBuku(char *nama);
void tampilDaftarBuku(addressBuku b[], int jmlhBuku);

#endif 
