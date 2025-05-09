#ifndef BUKU_H
#define BUKU_H

#include "boolean.h"
#include "peminjam.h"

typedef struct buku{
	char judul[100];
	int stok;
	struct buku* next;
}buku;

typedef buku* addressBuku;

void Create_Buku(addressBuku *b);
void Isi_Buku(addressBuku *b, char judul[], int stok);
void Ins_Buku(addressBuku *head, char judul[], int stok) ;

#endif
