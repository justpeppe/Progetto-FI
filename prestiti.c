#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prestiti.h"

int crea_lista_prestiti(prestiti* lista) {
    *lista = NULL;
    return 0; // Successo
}


int inserisci_nuovo_prestito(prestiti* lista, char data[], libro l_associato) {
    prestiti nuovo_prestito = (prestiti)malloc(sizeof(struct prestiti));
    if (nuovo_prestito == NULL) {
        return 1; // Errore di allocazione
    }
    
    nuovo_prestito->p = (prestito)malloc(sizeof(struct prestito));
    if (nuovo_prestito->p == NULL) {
        free(nuovo_prestito);
        return 1; // Errore di allocazione
    }

    if (crea_prestito(&nuovo_prestito->p, data, l_associato) != 0) {
        free(nuovo_prestito->p);
        free(nuovo_prestito);
        return 1; // Errore nella creazione del prestito
    }

    nuovo_prestito->successivo = *lista;
    *lista = nuovo_prestito;

    return 0; // Successo
}


prestito cerca_prestito_nella_lista_per_data(prestiti lista, const char data_chiave[]) {
    while (lista != NULL) {
        char data[11];
        get_data_del_prestito(lista->p, data);
        if (strcmp(data, data_chiave) == 0) {
            return lista->p; // Prestito trovato
        }
        lista = lista->successivo;
    }
    return NULL; // Prestito non trovato
}

prestito cerca_prestito_nella_lista_per_libro(prestiti lista, libro l_associato) {
    while (lista != NULL) {
        libro libro_corrente;
        get_libro_del_prestito(lista->p, &libro_corrente);
        if (libro_corrente == NULL) {
            return NULL; // Errore nel recupero del libro associato
        }
        if (libro_corrente == l_associato) {
            return lista->p; // Prestito trovato
        }
        lista = lista->successivo;
    }
    return NULL; // Prestito non trovato
}

int modifica_prestito_nella_lista(prestiti lista, const char data_attuale[], const char nuova_data[], libro nuovo_l_associato) {
    prestito p = cerca_prestito_nella_lista_per_data(lista, data_attuale);
    if (p == NULL) {
        return 1; // Prestito non trovato
    }

    if (set_data_del_prestito(p, nuova_data) != 0) {
        return 1; // Errore nella modifica della data
    }

    if (set_libro_del_prestito(p, nuovo_l_associato) != 0) {
        return 1; // Errore nella modifica del libro associato
    }

    return 0; // Successo
}


int cancella_prestito_dalla_lista(prestiti* lista, const char data_chiave[]) {
    prestiti corrente = *lista;
    prestiti precedente = NULL;

    while (corrente != NULL) {
        char data[11];
        get_data_del_prestito(corrente->p, data);
        if (strcmp(data, data_chiave) == 0) {
            if (precedente == NULL) {
                *lista = corrente->successivo; // Rimuove il primo elemento
            } else {
                precedente->successivo = corrente->successivo; // Rimuove l'elemento corrente
            }
            distruggi_prestito(&corrente->p); // Libera la memoria del prestito
            free(corrente); // Libera la memoria della struttura Prestiti
            return 0; // Successo
        }
        precedente = corrente;
        corrente = corrente->successivo;
    }
    return 1; // Prestito non trovato
}


int distruggi_lista_prestiti(prestiti* lista) {
    prestiti corrente = *lista;
    while (corrente != NULL) {
        prestiti da_cancellare = corrente;
        corrente = corrente->successivo;
        distruggi_prestito(&da_cancellare->p); // Libera la memoria del prestito
        free(da_cancellare); // Libera la memoria della struttura Prestiti
    }
    *lista = NULL; // Imposta la lista a NULL
    return 0; // Successo
}


void stampa_lista_prestiti(prestiti lista) {
    while (lista != NULL) {
        char data[11];
        get_data_del_prestito(lista->p, data);
        
        libro l;
        get_libro_del_prestito(lista->p, &l);
        if (l == NULL) {
            printf("Errore nel recupero del libro associato.\n");
            return;
        }
        
        char titolo[100];
        get_titolo(l, titolo);
        printf("Prestito:\n");
        printf("Data: %s\n", data);
        printf("Libro associato: %s\n", titolo);
        lista = lista->successivo;
    }
    printf("Fine della lista dei prestiti.\n");
}

