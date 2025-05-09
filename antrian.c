#include "antrian.h"

boolean isEmpty(addressBuku *b, addressPeminjam p) {
	return (*b == NULL || p == NULL);
}

void Tampil_List(buku* b) {
    while (b != NULL) {
        printf("\"%s\"", b->judul);

        peminjam* p = b->antrianDepan;
        while (p != NULL) {
            if (p->prioritas == 1) {
                printf(" -> \"%s\" (Dosen)", p->nama);  
            } else if (p->prioritas == 2) {
                printf(" -> \"%s\" (Mahasiswa)", p->nama);  
            } else if (p->prioritas == 3) {
                printf(" -> \"%s\" (Umum)", p->nama);  
            }
            p = p->next;
        }

        if (b->antrianDepan == NULL) {
            printf(" -> [Tidak ada antrian]");
        }

        printf("\n");
        b = b->next;
    }
}

void Ins_Antrian(addressBuku *b, addressPeminjam Pnew) {
    if (Pnew == NULL) return;

    addressPeminjam depan = (*b)->antrianDepan;

    if (depan == NULL || Pnew->prioritas < depan->prioritas) {
        // Insert di depan
        Pnew->next = depan;
        Pnew->prev = NULL;
        if (depan != NULL)
            depan->prev = Pnew;
        (*b)->antrianDepan = Pnew;
    } else {
        addressPeminjam temp = depan;
        while (temp->next != NULL && temp->next->prioritas <= Pnew->prioritas) {
            temp = temp->next;
        }
        Pnew->next = temp->next;
        Pnew->prev = temp;
        if (temp->next != NULL)
            temp->next->prev = Pnew;
        temp->next = Pnew;
    }
}

void Del_Peminjam(addressBuku *b, char namaTerhapus[]) {
    if ((*b)->antrianDepan != NULL) {
        addressPeminjam temp = (*b)->antrianDepan;
        strcpy(namaTerhapus, temp->nama);
        (*b)->antrianDepan = temp->next;
        if ((*b)->antrianDepan != NULL)
            (*b)->antrianDepan->prev = NULL;
        free(temp);
    } else {
        strcpy(namaTerhapus, "-");
    }
}

void Del_PeminjamTertentu(addressBuku *b, char namaTerhapus[], addressPeminjam *p) {
    if (p == NULL || *p == NULL) return;

    addressPeminjam target = *p;

    while (target != NULL && strcmp(target->nama, namaTerhapus) != 0) {
        target = target->next;
    }

    if (target != NULL) {
        strcpy(namaTerhapus, target->nama);

        if (target->prev != NULL)
            target->prev->next = target->next;
        else
            (*b)->antrianDepan = target->next;  // target di depan

        if (target->next != NULL)
            target->next->prev = target->prev;

        free(target);
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

