#ifndef LIBRO_H
#define LIBRO_H

struct libro {
    char titolo[100];
    char nome_autore[50];
    char cognome_autore[50];
};

typedef struct libro* libro;

int crea_libro(libro* nuovo_libro, const char titolo[], const char nome_autore[], const char cognome_autore[]);

int get_titolo(libro l, char titolo[]);
int get_nome_autore(libro l, char nome_autore[]);
int get_cognome_autore(libro l, char cognome_autore[]);

int set_titolo(libro l, const char nuovo_titolo[]);
int set_nome_autore(libro l, const char nuovo_nome_autore[]);
int set_cognome_autore(libro l, const char nuovo_cognome_autore[]);

int distruggi_libro(libro* l);

int stampa_libro(libro l);

#endif