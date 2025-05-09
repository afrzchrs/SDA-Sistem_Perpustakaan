#include "buku.h"

void Create_Buku(addressBuku *b) {
    *b = (addressBuku) malloc(sizeof(buku));
}

void Isi_Buku(addressBuku *b, char judul[], int stok) {
    if (*b != NULL) {
        strcpy((*b)->judul, judul);
        (*b)->stok = stok; 
        (*b)->next = NULL;
    }
}

void Ins_Buku(addressBuku *head, char judul[], int stok) {
    addressBuku newNode;
    Create_Buku(&newNode);
    Isi_Buku(&newNode, judul, stok);

    if (*head == NULL) {
        *head = newNode;  
    } else {
        addressBuku temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; 
    }
}

