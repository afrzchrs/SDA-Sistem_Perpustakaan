#include "boolean.h"

#include "peminjam.h"

#ifndef ANTRIAN_H
#define ANTRIAN_H

boolean isEmpty(addressBuku *b, addressPeminjam p);
void Tampil_List(addressPeminjam p);
void Ins_Antrian(addressPeminjam *head, addressPeminjam pBaru);
void Del_Peminjam(addressPeminjam *head, char namaTerhapus[]);
void Del_PeminjamTertentu(addressPeminjam *head, char namaTerhapus[]);
int NbElmt(addressPeminjam p);
void hapusBuku(addressBuku b[], int *jmlhBuku, addressPeminjam *daftarPeminjam);

#endif
