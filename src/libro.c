#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libro.h"

int crea_libro(libro* nuovo_libro, const char titolo[], const char nome_autore[], const char cognome_autore[]) {  
    *nuovo_libro = (libro)malloc(sizeof(struct libro));
    if (*nuovo_libro == NULL) {
        return 1; // Errore di allocazione
    } 
    set_titolo(*nuovo_libro, titolo);
    set_nome_autore(*nuovo_libro, nome_autore);
    set_cognome_autore(*nuovo_libro, cognome_autore);
    return 0; // Successo
}


int get_titolo(libro l, char titolo[]) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    strcpy(titolo, l->titolo);
    return 0; // Successo
}


int get_nome_autore(libro l, char nome_autore[]) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    strcpy(nome_autore, l->nome_autore);
    return 0; // Successo
}


int get_cognome_autore(libro l, char cognome_autore[]) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    strcpy(cognome_autore, l->cognome_autore);
    return 0; // Successo
}


int set_titolo(libro l, const char nuovo_titolo[]) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    strcpy(l->titolo, nuovo_titolo);
    return 0; // Successo
}


int set_nome_autore(libro l, const char nuovo_nome_autore[]) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    strcpy(l->nome_autore, nuovo_nome_autore);
    return 0; // Successo
}


int set_cognome_autore(libro l, const char nuovo_cognome_autore[]) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    strcpy(l->cognome_autore, nuovo_cognome_autore);
    return 0; // Successo
}


int distruggi_libro(libro* l) {
    if (*l == NULL) {
        return 1; // Libro non valido
    }
    free(*l);
    *l = NULL;
    return 0; // Successo
}


int stampa_libro(libro l) {
    if (l == NULL) {
        return 1; // Libro non valido
    }
    printf("Titolo: %s\n", l->titolo);
    printf("Autore: %s %s\n", l->nome_autore, l->cognome_autore);
    return 0; // Successo
}

