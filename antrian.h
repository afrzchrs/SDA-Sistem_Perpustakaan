#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "boolean.h"
#include "buku.h"
#include "peminjam.h"

boolean isEmpty(addressBuku b, addressPeminjam p);
void Tampil_List(addressPeminjam p, addressBuku b);
void Ins_Antrian(addressPeminjam *p, addressPeminjam Pnew, addressBuku b);
void Del_PeminjamTertentu(addressPeminjam *p, char namaTerhapus[]);
int NbElmt(addressPeminjam p);

#endif
