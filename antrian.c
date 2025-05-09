#include "antrian.h"

boolean isEmpty(addressBuku b, addressPeminjam p) {
    return (b == NULL || p == NULL);
}

void Tampil_List(addressPeminjam p, addressBuku b) {
    while (b != NULL) {
        printf("\"%s\"", b->judul);
        int ada = 0;

        addressPeminjam temp = p;
        while (temp != NULL) {
            if (temp->antrianDepan == b) {
                ada = 1;
                if (temp->prioritas == 1)
                    printf(" -> \"%s\" (Dosen)", temp->nama);
                else if (temp->prioritas == 2)
                    printf(" -> \"%s\" (Mahasiswa)", temp->nama);
                else
                    printf(" -> \"%s\" (Umum)", temp->nama);
            }
            temp = temp->next;
        }

        if (!ada) {
            printf(" -> [Tidak ada antrian]");
        }

        printf("\n");
        b = b->next;
    }
}

void Ins_Antrian(addressPeminjam *p, addressPeminjam Pnew, addressBuku b) {
    if (Pnew == NULL) return;

    Pnew->antrianDepan = b; // set buku yang sedang diantri

    if (*p == NULL || Pnew->prioritas < (*p)->prioritas) {
        Pnew->next = *p;
        *p = Pnew;
    } else {
        addressPeminjam temp = *p;
        while (temp->next != NULL && temp->next->prioritas <= Pnew->prioritas) {
            temp = temp->next;
        }
        Pnew->next = temp->next;
        temp->next = Pnew;
    }
}

void Del_PeminjamTertentu(addressPeminjam *p, char namaTerhapus[]) {
    if (*p == NULL) return;

    addressPeminjam temp = *p;

    if (strcmp(temp->nama, namaTerhapus) == 0) {
        *p = temp->next;
        free(temp);
    } else {
        addressPeminjam prev = temp;
        temp = temp->next;
        while (temp != NULL && strcmp(temp->nama, namaTerhapus) != 0) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL) {
            prev->next = temp->next;
            free(temp);
        }
    }
}

int NbElmt(addressPeminjam p) {
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}
