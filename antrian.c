#include "antrian.h"

boolean isEmpty(addressBuku *b, addressPeminjam p) {
	return (*b == NULL || p == NULL);
}


void Tampil_List(addressPeminjam head) {
	if (head == NULL) {
        printf("Tidak ada peminjam.\n");
        return;
    }

    // Simpan daftar unik judul buku
    char daftarJudul[100][100]; // max 100 judul unik
    int jumlahJudul = 0;

    addressPeminjam temp = head;

    // Kumpulkan judul buku unik
    while (temp != NULL) {
        int sudahAda = 0;
        for (int i = 0; i < jumlahJudul; i++) {
            if (strcmp(daftarJudul[i], temp->bukuDipinjam->judul) == 0) {
                sudahAda = 1;
                break;
            }
        }

        if (!sudahAda) {
            strcpy(daftarJudul[jumlahJudul], temp->bukuDipinjam->judul);
            jumlahJudul++;
        }

        temp = temp->next;
    }

    // Tampilkan per judul
    for (int i = 0; i < jumlahJudul; i++) {
        printf("\n%s -> ", daftarJudul[i]);

        // Urutan prioritas 1 ke 3
        for (int prio = 1; prio <= 3; prio++) {
            temp = head;
            while (temp != NULL) {
                if (strcmp(temp->bukuDipinjam->judul, daftarJudul[i]) == 0 && temp->prioritas == prio) {
                    // Cetak nama saja
                    printf("%s", temp->nama);

                    // Cek apakah ada selanjutnya dengan judul dan prioritas sama
                    addressPeminjam t2 = temp->next;
                    int adaLagi = 0;
                    while (t2 != NULL) {
                        if (strcmp(t2->bukuDipinjam->judul, daftarJudul[i]) == 0 && t2->prioritas == prio) {
                            adaLagi = 1;
                            break;
                        }
                        t2 = t2->next;
                    }
                    if (adaLagi) printf(" -> ");
                }
                temp = temp->next;
            }

            // Cek apakah ada prioritas selanjutnya dalam buku yang sama
            temp = head;
            int adaPrioSelanjutnya = 0;
            while (temp != NULL) {
                if (strcmp(temp->bukuDipinjam->judul, daftarJudul[i]) == 0 && temp->prioritas > prio) {
                    adaPrioSelanjutnya = 1;
                    break;
                }
                temp = temp->next;
            }

            if (adaPrioSelanjutnya) printf(" -> ");
        }
        printf("\n");
    }
}


void Ins_Antrian(addressPeminjam *head, addressPeminjam pBaru) {
    if (*head == NULL || pBaru->prioritas < (*head)->prioritas) {
        pBaru->next = *head;
        *head = pBaru;
    } else {
        addressPeminjam temp = *head;
        while (temp->next != NULL && temp->next->prioritas <= pBaru->prioritas) {
            temp = temp->next;
        }
        pBaru->next = temp->next;
        temp->next = pBaru;
    }
}

void Del_Peminjam(addressPeminjam *head, char namaTerhapus[]) {
    if (*head != NULL) {
        addressPeminjam temp = *head;
        strcpy(namaTerhapus, temp->nama);
        *head = temp->next;
        free(temp);
    } else {
        strcpy(namaTerhapus, "-");
    }
}


void Del_PeminjamTertentu(addressPeminjam *head, char namaTerhapus[]) {
    addressPeminjam curr = *head, prev = NULL;
    while (curr != NULL && strcmp(curr->nama, namaTerhapus) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        if (prev == NULL) {
            *head = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
        printf("Peminjam '%s' berhasil dihapus.\n", namaTerhapus);
    } else {
        printf("Peminjam '%s' tidak ditemukan.\n", namaTerhapus);
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

void hapusBuku(addressBuku b[], int *jmlhBuku, addressPeminjam *daftarPeminjam) {
    char hapusJudul[50];
    inputBuku(hapusJudul);

    int i, found = -1;
    for (i = 0; i < *jmlhBuku; i++) {
        if (strcmp(b[i]->judul, hapusJudul) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Buku '%s' tidak ditemukan!\n", hapusJudul);
        return;
    }

    // Hapus semua peminjam yang menunjuk ke buku ini
    addressPeminjam curr = *daftarPeminjam, prev = NULL;
    while (curr != NULL) {
        if (curr->bukuDipinjam == b[found]) {
            addressPeminjam toDelete = curr;
            if (prev == NULL) {
                *daftarPeminjam = curr->next;
                curr = *daftarPeminjam;
            } else {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(toDelete);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    free(b[found]);

    for (i = found; i < (*jmlhBuku) - 1; i++) {
        b[i] = b[i + 1];
    }

    (*jmlhBuku)--;
    printf("Buku '%s' berhasil dihapus beserta peminjamnya.\n", hapusJudul);
}

