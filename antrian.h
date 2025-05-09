#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "boolean.h"
#include "buku.h"
#include "peminjam.h"

boolean isEmpty(addressBuku *b, addressPeminjam p);
void Tampil_List(buku* b);
void Ins_Antrian(addressBuku *b, addressPeminjam Pnew);
void Del_Peminjam(addressBuku *b, char namaTerhapus[]);
void Del_PeminjamTertentu(addressBuku *b, char namaTerhapus[], addressPeminjam *p);
int NbElmt(addressPeminjam p);

#endif
