#ifndef PEMINJAM_H
#define PEMINJAM_H

#include "boolean.h"

typedef struct peminjam{
	char nama[100];
    int prioritas; 
    struct peminjam* next;
    struct peminjam* prev;
}peminjam;

typedef peminjam* addressPeminjam; 

void Create_Peminjam(addressPeminjam *p);
void Isi_Peminjam(addressPeminjam *p, char nama[], int prioritas);
addressPeminjam Search(addressPeminjam p, char nama[]);

#endif

