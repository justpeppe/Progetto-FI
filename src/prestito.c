#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prestito.h"

int crea_prestito(prestito* nuovo_prestito, const char data[], libro l_associato) {
    *nuovo_prestito = (prestito)malloc(sizeof(struct prestito));
    if (*nuovo_prestito == NULL) {
        return 1;
    }
    strcpy((*nuovo_prestito)->data_prestito, data);
    (*nuovo_prestito)->libro_associato = l_associato;
    return 0;
}

int get_data_del_prestito(prestito p, char data[]) {
    if (p == NULL || data == NULL) {
        return 1; // Errore
    }
    
    strcpy(data, p->data_prestito);
    return 0; // Successo
}

libro get_libro_del_prestito(prestito p, libro* l_cerca) {
    if (p == NULL || l_cerca == NULL) {
        return NULL; // Errore
    }
    
    *l_cerca = p->libro_associato;
    return *l_cerca; // Successo
}

int set_data_del_prestito(prestito p, const char nuova_data[]) {
    if (p == NULL || nuova_data == NULL) {
        return 1;
    }
    
    strcpy(p->data_prestito, nuova_data);
    return 0;
}

int set_libro_del_prestito(prestito p, libro nuovo_l_associato) {
    if (p == NULL || nuovo_l_associato == NULL) {
        return 1;
    }
    
    p->libro_associato = nuovo_l_associato;
    return 0;
}

int aggiorna_puntatore_libro_prestito(prestito p, libro vecchio_libro, libro nuovo_libro) {
    if (p == NULL || vecchio_libro == NULL || nuovo_libro == NULL) {
        return 1;
    }
    
    if (p->libro_associato == vecchio_libro) {
        p->libro_associato = nuovo_libro;
        return 0;
    }
    
    return 1;
}

int distruggi_prestito(prestito* p) {
    if (p == NULL || *p == NULL) {
        return 1;
    }
    
    free(*p);
    *p = NULL;
    return 0;
}

int stampa_prestito(prestito p) {
    if (p == NULL) {
        return 1;
    }

    char data[11];
    get_data_del_prestito(p, data);
    
    libro l;
    get_libro_del_prestito(p, &l);
    if (l == NULL) {
        return 1; // Errore nel recupero del libro associato
    }
    
    char titolo[100];
    get_titolo(l, titolo);
    
    printf("Prestito:\n");
    printf("Data: %s\n", data);
    printf("Libro associato: %s\n", titolo);
    
    return 0;
}
