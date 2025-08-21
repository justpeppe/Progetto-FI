#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persone.h"
#include "libri.h"

int stampa_menu()
{
    int scelta = -1;
    char buffer[16];

    printf("\n--- MENU BIBLIOTECA ---\n");
    printf("1.  Aggiungi nuovo libro\n");
    printf("2.  Visualizza lista libri\n");
    printf("3.  Registra nuovo utente\n");
    printf("4.  Visualizza lista utenti e prestiti\n");
    printf("5.  Registra nuovo prestito\n");
    printf("6.  Elimina libro\n");
    printf("7.  Elimina utente\n");
    printf("8.  Elimina prestito\n");
    printf("0.  Esci\n");
    printf("-----------------------\n");
    printf("Seleziona un'azione: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        scelta = atoi(buffer); // atoi -> converte stringa in intero (fatto con scanf rimaneva /n alla fine e veniva dato come input al sottomenù)
    }

    return scelta;
}

void leggi_stringa(char *buffer, int dimensione)
{
    do
    {
        fgets(buffer, dimensione, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0)
        {
            printf("La stringa non può essere vuota. Riprova: ");
        }
    } while (strlen(buffer) == 0);
}

int is_libro_in_prestito(persone lista_utenti, libro libro_da_controllare)
{
    while (lista_utenti != NULL)
    {
        prestiti *p_lista_prestiti = get_prestiti_della_persona(lista_utenti->p);
        if (cerca_prestito_nella_lista_per_libro(*p_lista_prestiti, libro_da_controllare) != NULL)
        {
            return 1;
        }
        lista_utenti = lista_utenti->successivo;
    }
    return 0;
}

// Primo menù
void gestisci_inserimento_libro(libri *lista_libri)
{
    char titolo[100], nome_autore[50], cognome_autore[50];

    printf("Inserisci titolo del libro: ");
    leggi_stringa(titolo, 100);
    printf("Inserisci nome dell'autore: ");
    leggi_stringa(nome_autore, 50);
    printf("Inserisci cognome dell'autore: ");
    leggi_stringa(cognome_autore, 50);

    if (inserisci_nuovo_libro(lista_libri, titolo, nome_autore, cognome_autore) == 0)
    {
        printf("Libro inserito con successo!\n");
    }
    else
    {
        printf("Errore: impossibile inserire il libro.\n");
    }
}

// Secondo menù --> presente in libri.h

// Terzo menù
void gestisci_registrazione_utente(persone *lista_utenti)
{
    char nome[50], cognome[50];

    printf("Inserisci nome utente: ");
    leggi_stringa(nome, 50);
    printf("Inserisci cognome utente: ");
    leggi_stringa(cognome, 50);

    if (inserisci_nuova_persona(lista_utenti, nome, cognome) == 0)
    {
        printf("Utente registrato con successo!\n");
    }
    else
    {
        printf("Errore: impossibile registrare l'utente.\n");
    }
}

// Quarto menù --> presente in persone.h

// Quinto menù
void gestisci_registrazione_prestito(persone lista_utenti, libri lista_libri)
{
    char cognome_utente[50], titolo_libro[100], data_prestito[11];
    persona utente = NULL;
    libro libro_da_prestare = NULL;

    do {
        printf("Inserisci cognome dell'utente per il prestito: ");
        leggi_stringa(cognome_utente, 50);
        utente = cerca_persona_nella_lista(lista_utenti, cognome_utente);
        if (utente == NULL)
            printf("Errore: utente non trovato. Riprova.\n");
    } while (utente == NULL);

    do {
        printf("Inserisci titolo del libro da prestare: ");
        leggi_stringa(titolo_libro, 100);
        libro_da_prestare = cerca_libro_nella_lista(lista_libri, titolo_libro);
        if (libro_da_prestare == NULL) {
            printf("Errore: libro non trovato. Riprova.\n");
            continue;
        }
        if (is_libro_in_prestito(lista_utenti, libro_da_prestare)) {
            printf("Errore: il libro '%s' è già in prestito. Scegli un altro libro.\n", titolo_libro);
            libro_da_prestare = NULL;
        }
    } while (libro_da_prestare == NULL);

    printf("Inserisci data prestito (AAAA-MM-GG): ");
    leggi_stringa(data_prestito, 11);

    prestiti *p_lista_prestiti_utente = get_prestiti_della_persona(utente);
    if (p_lista_prestiti_utente == NULL)
    {
        printf("Errore interno nel recuperare la lista prestiti.\n");
        return;
    }

    if (inserisci_nuovo_prestito(p_lista_prestiti_utente, data_prestito, libro_da_prestare) == 0)
    {
        printf("Prestito registrato con successo!\n");
    }
    else
    {
        printf("Errore: impossibile registrare il prestito.\n");
    }
}

// Sesto menù
void gestisci_elimina_libro(libri *lista_libri, persone lista_utenti)
{
    char titolo[100];
    printf("Inserisci titolo del libro da eliminare: ");
    leggi_stringa(titolo, 100);

    libro libro_da_eliminare = cerca_libro_nella_lista(*lista_libri, titolo);
    if (libro_da_eliminare == NULL)
    {
        printf("Errore: libro non trovato.\n");
        return;
    }

    // Se il libro è in prestito NON effettuare la cancellazione
    if (is_libro_in_prestito(lista_utenti, libro_da_eliminare))
    {
        printf("ERRORE: Impossibile eliminare il libro '%s' perche' attualmente in prestito.\n", titolo);
        return;
    }

    if (cancella_libro_dalla_lista(lista_libri, titolo) == 0)
    {
        printf("Libro eliminato con successo!\n");
    }
}

// Settimo menù
void gestisci_elimina_utente(persone *lista_utenti)
{
    char cognome[50];
    printf("Inserisci cognome dell'utente da eliminare: ");
    leggi_stringa(cognome, 50);

    persona utente = cerca_persona_nella_lista(*lista_utenti, cognome);
    if (utente == NULL)
    {
        printf("Errore: utente non trovato.\n");
        return;
    }

    prestiti *p_lista_prestiti = get_prestiti_della_persona(utente);
    if (p_lista_prestiti != NULL && *p_lista_prestiti != NULL)
    {
        printf("ERRORE: impossibile eliminare l'utente '%s' perché ha prestiti in corso.\n", cognome);
        return;
    }

    if (cancella_persona_dalla_lista(lista_utenti, cognome) == 0)
    {
        printf("Utente eliminato con successo!\n");
    }
    else
    {
        printf("Errore: utente non trovato.\n");
    }
}

// Ottavo menù
void gestisci_elimina_prestito(persone lista_utenti)
{
    char cognome_utente[50], data_prestito[11];
    printf("Inserisci cognome dell'utente: ");
    leggi_stringa(cognome_utente, 50);

    persona utente = cerca_persona_nella_lista(lista_utenti, cognome_utente);
    if (utente == NULL)
    {
        printf("Errore: utente non trovato.\n");
        return;
    }

    printf("Inserisci data del prestito da eliminare (AAAA-MM-GG): ");
    leggi_stringa(data_prestito, 11);

    prestiti *p_lista_prestiti_utente = get_prestiti_della_persona(utente);
    if (p_lista_prestiti_utente == NULL)
    {
        printf("Errore interno nel recuperare la lista prestiti.\n");
        return;
    }

    if (cancella_prestito_dalla_lista(p_lista_prestiti_utente, data_prestito) == 0)
    {
        printf("Prestito eliminato con successo!\n");
    }
    else
    {
        printf("Errore: prestito non trovato per la data specificata.\n");
    }
}

int main()
{
    libri lista_principale_libri;
    persone lista_principale_utenti;

    crea_lista_Libri(&lista_principale_libri);
    crea_lista_persone(&lista_principale_utenti);

    int scelta = -1;
    do
    {
        scelta = stampa_menu();
        switch (scelta)
        {
        case 1:
            gestisci_inserimento_libro(&lista_principale_libri);
            break;
        case 2:
            stampa_lista_libri(lista_principale_libri);
            break;
        case 3:
            gestisci_registrazione_utente(&lista_principale_utenti);
            break;
        case 4:
            stampa_lista_persone(lista_principale_utenti);
            break;
        case 5:
            gestisci_registrazione_prestito(lista_principale_utenti, lista_principale_libri);
            break;
        case 6:
            gestisci_elimina_libro(&lista_principale_libri, lista_principale_utenti);
            break;
        case 7:
            gestisci_elimina_utente(&lista_principale_utenti);
            break;
        case 8:
            gestisci_elimina_prestito(lista_principale_utenti);
            break;
        case 0:
            printf("Uscita in corso...\n");
            break;
        default:
            printf("Scelta non valida. Riprova.\n");
            break;
        }
    } while (scelta != 0);

    distruggi_lista_libri(&lista_principale_libri);
    distruggi_lista_persone(&lista_principale_utenti);

    printf("Programma terminato. Arrivederci!\n");
    return 0;
}
