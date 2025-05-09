#include "peminjam.h"
	
void Create_Peminjam(addressPeminjam *p) {
	    *p = (addressPeminjam) malloc(sizeof(peminjam));
	}
	
void Isi_Peminjam(addressPeminjam *p, char nama[], int prioritas) {
	    if (*p != NULL) {
	        strcpy((*p)->nama, nama);
	        (*p)->prioritas = prioritas;
	        (*p)->next = NULL;
	    }
	}
	
addressPeminjam Search(addressPeminjam p, char nama[]) {
	    while (p != NULL) {
	        if (strcmp(p->nama, nama) == 0)
	            return p;
	        p = p->next;
	    }
	    return NULL;
	}
