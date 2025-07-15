#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persona.h"

int crea_persona(persona* nuova_persona, const char nome[], const char cognome[]) {
    if (nuova_persona == NULL || nome == NULL || cognome == NULL) {
        return 1; // Errore: puntatore nullo
    }
    
    *nuova_persona = (persona)malloc(sizeof(struct persona));
    if (*nuova_persona == NULL) {
        return 1; // Errore di allocazione memoria
    }
    
    strcpy((*nuova_persona)->nome, nome);
    strcpy((*nuova_persona)->cognome, cognome);
    (*nuova_persona)->lista_propri_prestiti = NULL; 
    
    return 0; // Successo
}


int get_nome_persona(persona pers, char nome[]) {
    if (pers == NULL || nome == NULL) {
        return 1; // Errore: puntatore nullo
    }
    
    strcpy(nome, pers->nome);
    return 0; // Successo
}


int get_cognome_persona(persona pers, char cognome[]) {
    if (pers == NULL || cognome == NULL) {
        return 1; // Errore: puntatore nullo
    }
    
    strcpy(cognome, pers->cognome);
    return 0; // Successo
}


prestiti* get_prestiti_della_persona(persona pers) {
    if (pers == NULL) {
        return NULL;
    }
    // Restituisce l'indirizzo del puntatore alla lista, non una sua copia.
    return &(pers->lista_propri_prestiti);
}


int set_nome_persona(persona pers, const char nuovo_nome[]) {
    if (pers == NULL || nuovo_nome == NULL) {
        return 1; // Errore: puntatore nullo
    }
    
    strcpy(pers->nome, nuovo_nome);
    return 0; // Successo
}


int set_cognome_persona(persona pers, const char nuovo_cognome[]) {
    if (pers == NULL || nuovo_cognome == NULL) {
        return 1; // Errore: puntatore nullo
    }
    
    strcpy(pers->cognome, nuovo_cognome);
    return 0; // Successo
}


int distruggi_persona(persona* pers) {
    if (pers == NULL || *pers == NULL) {
        return 1; // Errore: puntatore nullo
    }
    
    distruggi_lista_prestiti(&((*pers)->lista_propri_prestiti));

    free(*pers);
    *pers = NULL; 
    return 0; // Successo
}


int stampa_persona(persona pers) {
    if (pers == NULL) {
        return 1;
    }
    
    printf("Utente: %s %s\n", pers->nome, pers->cognome);
    printf("Prestiti in corso:\n");
    stampa_lista_prestiti(pers->lista_propri_prestiti); // Aggiunta
    printf("--------------------------------\n");
    return 0; 
}