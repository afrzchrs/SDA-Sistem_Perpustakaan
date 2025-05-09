#ifndef BUKU_H
#define BUKU_H

#include "boolean.h"
#include "peminjam.h"

typedef struct buku{
	char judul[100];
	int stok; 
	peminjam* antrianDepan;
}buku;

typedef buku* addressBuku;

void tambahBuku(addressBuku b[], int *jmlhKota);
void inputStok(int *stok);
void hapusBuku(addressBuku b[], int *jmlhKota);
void inputBuku(char *nama);

#endif 
