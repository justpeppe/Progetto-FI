#ifndef LIBRI_H
#define LIBRI_H
#include "libro.h"

struct Libri {
    libro l;
    struct Libri* successivo;
};

typedef struct Libri* libri;

int crea_lista_Libri(libri* lista);

int inserisci_nuovo_libro(libri* lista, const char titolo[], const char nome_autore[], const char cognome_autore[]);

libro cerca_libro_nella_lista(libri lista, const char titolo_chiave[]);

int modifica_libro_nella_lista(libri lista, const char titolo_attuale[], const char nuovo_titolo[], const char nuovo_nome_autore[], const char nuovo_cognome_autore[]);

int cancella_libro_dalla_lista(libri* lista, const char titolo_chiave[]);

int distruggi_lista_libri(libri* lista);

void stampa_lista_libri(libri lista);

#endif