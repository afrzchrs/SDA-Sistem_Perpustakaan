#include "antrian.h"

boolean isEmpty(addressBuku *b, addressPeminjam p) {
	return (*b == NULL || p == NULL);
}

void Tampil_List(addressBuku *b, int jumlahBuku) {
	if (jumlahBuku == 0) {
	        printf("Tidak ada data buku.\n");
	        return;
	    }

    for (int i = 0; i < jumlahBuku; i++) {
        printf("\"%s\"", b[i]->judul);

        addressPeminjam current = b[i]->antrianDepan;
        while (current != NULL) {
            printf(" -> \"%s\"", current->nama);
            current = current->next;
        }

        if (b[i]->antrianDepan == NULL) {
            printf(" -> [Tidak ada antrian]");
        }

        printf("\n");
    }
}

void Ins_Antrian(addressBuku *b, addressPeminjam Pnew) {
    if (Pnew == NULL) return;

    if ((*b)->antrianDepan == NULL || Pnew->prioritas < (*b)->antrianDepan->prioritas) {
        Pnew->next = (*b)->antrianDepan;
        (*b)->antrianDepan = Pnew;
    } else {
        addressPeminjam temp = (*b)->antrianDepan;
        while (temp->next != NULL && temp->next->prioritas <= Pnew->prioritas) {
            temp = temp->next;
        }
        Pnew->next = temp->next;
        temp->next = Pnew;
    }
}

void Del_Peminjam(addressBuku *b, char namaTerhapus[]) {
    if ((*b)->antrianDepan != NULL) {
        addressPeminjam temp = (*b)->antrianDepan;
        strcpy(namaTerhapus, temp->nama);
        (*b)->antrianDepan = temp->next;
        free(temp);
    } else {
        strcpy(namaTerhapus, "-");
    }
}

void Del_PeminjamTertentu(addressBuku *b, char namaTerhapus[], addressPeminjam *p ) {
	if(p == NULL)return;
	
    if (strcmp((*b)->antrianDepan->nama, namaTerhapus) == 0) {
        addressPeminjam temp = (*b)->antrianDepan;
        
        strcpy(namaTerhapus, temp->nama);
        (*b)->antrianDepan = temp->next;
        free(temp);
        
    } else {
    	addressPeminjam temp = *p, prev = NULL;
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
