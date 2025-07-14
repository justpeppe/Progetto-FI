#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libri.h"


int crea_lista_Libri(libri* lista) {
    *lista = NULL;
    return 0; // Successo
}

int inserisci_nuovo_libro(libri* lista, char titolo[], char nome_autore[], char cognome_autore[]) {
    libri nuovo_libro = (libri)malloc(sizeof(struct Libri));
    if (nuovo_libro == NULL) {
        return 1; // Errore di allocazione
    }
    nuovo_libro->l = (libro)malloc(sizeof(struct libro));
    set_titolo(nuovo_libro->l, titolo);
    set_nome_autore(nuovo_libro->l, nome_autore);
    set_cognome_autore(nuovo_libro->l, cognome_autore);

    char titolo_nuovo[100];
    get_titolo(nuovo_libro->l, titolo_nuovo);

    libri corrente = *lista;
    libri precedente = NULL;

    // Scorre la lista per trovare la posizione corretta
    while (corrente != NULL) {
        char titolo_corrente[100];
        get_titolo(corrente->l, titolo_corrente);
        if (strcmp(titolo_nuovo, titolo_corrente) < 0) {
            break; // Trovato il punto di inserimento
        }
        precedente = corrente;
        corrente = corrente->successivo;
    }

    // Inserisce il nodo
    if (precedente == NULL) { // Inserimento in testa
        nuovo_libro->successivo = *lista;
        *lista = nuovo_libro;
    } else { // Inserimento in mezzo o in coda
        precedente->successivo = nuovo_libro;
        nuovo_libro->successivo = corrente;
    }

    return 0; // Successo
}


libro cerca_libro_nella_lista(libri lista, char titolo_chiave[]) {
    while (lista != NULL) {
        char titolo[100];
        get_titolo(lista->l, titolo);
        if (strcmp(titolo, titolo_chiave) == 0) {
            return lista->l; // Libro trovato
        }
        lista = lista->successivo;
    }
    return NULL; // Libro non trovato
}

//Se passo parametri vuoti vuol dire che non voglio effettuare modifiche
int modifica_libro_nella_lista(libri lista, char titolo_attuale[], char nuovo_titolo[], char nuovo_nome_autore[], char nuovo_cognome_autore[]) {
    libro l = cerca_libro_nella_lista(lista, titolo_attuale);
    if (l == NULL) {
        return 1; // Libro non trovato
    }

    if (nuovo_titolo[0] != '\0') {
        set_titolo(l, nuovo_titolo);
    }

    if (nuovo_nome_autore[0] != '\0') {
        set_nome_autore(l, nuovo_nome_autore);
    }

    if (nuovo_cognome_autore[0] != '\0') {
        set_cognome_autore(l, nuovo_cognome_autore);
    }

    return 0; // Successo
}


int cancella_libro_dalla_lista(libri* lista, char titolo_chiave[]) {
    libri corrente = *lista;
    libri precedente = NULL;

    while (corrente != NULL) {
        char titolo[100];
        get_titolo(corrente->l, titolo);
        if (strcmp(titolo, titolo_chiave) == 0) {
            if (precedente == NULL) {
                *lista = corrente->successivo; // Rimuove il primo elemento
            } else {
                precedente->successivo = corrente->successivo; // Rimuove l'elemento corrente
            }
            distruggi_libro(&corrente->l); // Libera la memoria del libro
            free(corrente); // Libera la memoria della struttura Libri
            return 0; // Successo
        }
        precedente = corrente;
        corrente = corrente->successivo;
    }
    return 1; // Libro non trovato
}


int distruggi_lista_libri(libri* lista) {
    libri corrente = *lista;
    while (corrente != NULL) {
        libri da_cancellare = corrente;
        corrente = corrente->successivo;
        distruggi_libro(&da_cancellare->l); // Libera la memoria del libro
        free(da_cancellare); // Libera la memoria della struttura Libri
    }
    *lista = NULL; // Imposta la lista a NULL
    return 0; // Successo
}


void stampa__lista_libri(libri lista) {
    while (lista != NULL) {
        char titolo[100];
        char nome_autore[50];
        char cognome_autore[50];

        get_titolo(lista->l, titolo);
        get_nome_autore(lista->l, nome_autore);
        get_cognome_autore(lista->l, cognome_autore);

        printf("Titolo: %s, Autore: %s %s\n", titolo, nome_autore, cognome_autore);
        lista = lista->successivo;
    }
}