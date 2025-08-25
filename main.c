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
    printf("1.  Inserisci nuovo libro\n");
    printf("2.  Modifica libro esistente\n");
    printf("3.  Elimina libro esistente\n");
    printf("4.  Visualizza lista libri\n");
    printf("5.  Registra nuovo utente\n");
    printf("6.  Modifica dati utente registrato\n");
    printf("7.  Elimina utente registrato\n");
    printf("8.  Registra nuovo prestito\n");
    printf("9.  Modifica prestito esistente\n");
    printf("10. Elimina prestito\n");
    printf("11. Visualizza lista utenti registrati\n");
    printf("12. Esci\n");
    printf("-----------------------\n");
    printf("Seleziona un'azione: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        scelta = atoi(buffer);
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

// 1. Inserisci nuovo libro
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

// 2. Modifica libro esistente
void gestisci_modifica_libro(libri *lista_libri)
{
    char titolo[100];
    printf("Inserisci il titolo del libro da modificare: ");
    leggi_stringa(titolo, 100);

    libro libro_da_modificare = cerca_libro_nella_lista(*lista_libri, titolo);
    if (libro_da_modificare == NULL)
    {
        printf("Errore: libro non trovato.\n");
        return;
    }

    char nuovo_titolo[100], nuovo_nome_autore[50], nuovo_cognome_autore[50];

    printf("Inserisci il nuovo titolo (lascia vuoto per non modificare): ");
    fgets(nuovo_titolo, 100, stdin);
    nuovo_titolo[strcspn(nuovo_titolo, "\n")] = 0;

    printf("Inserisci il nuovo nome autore (lascia vuoto per non modificare): ");
    fgets(nuovo_nome_autore, 50, stdin);
    nuovo_nome_autore[strcspn(nuovo_nome_autore, "\n")] = 0;

    printf("Inserisci il nuovo cognome autore (lascia vuoto per non modificare): ");
    fgets(nuovo_cognome_autore, 50, stdin);
    nuovo_cognome_autore[strcspn(nuovo_cognome_autore, "\n")] = 0;

    // Aggiorna solo i campi non vuoti
    if (strlen(nuovo_titolo) > 0)
        strncpy(libro_da_modificare->titolo, nuovo_titolo, sizeof(libro_da_modificare->titolo) - 1);
    if (strlen(nuovo_nome_autore) > 0)
        strncpy(libro_da_modificare->nome_autore, nuovo_nome_autore, sizeof(libro_da_modificare->nome_autore) - 1);
    if (strlen(nuovo_cognome_autore) > 0)
        strncpy(libro_da_modificare->cognome_autore, nuovo_cognome_autore, sizeof(libro_da_modificare->cognome_autore) - 1);

    // Assicurati che le stringhe siano terminate correttamente
    libro_da_modificare->titolo[sizeof(libro_da_modificare->titolo) - 1] = '\0';
    libro_da_modificare->nome_autore[sizeof(libro_da_modificare->nome_autore) - 1] = '\0';
    libro_da_modificare->cognome_autore[sizeof(libro_da_modificare->cognome_autore) - 1] = '\0';

    printf("Libro modificato con successo!\n");
}

// 3. Elimina libro esistente
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

// 4. Visualizza lista libri --> stampa_lista_libri

// 5. Registra nuovo utente
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

// 6. Modifica dati utente registrato
void gestisci_modifica_utente(persone *lista_utenti)
{
    char cognome[50];
    printf("Inserisci il cognome dell'utente da modificare: ");
    leggi_stringa(cognome, 50);

    persona utente = cerca_persona_nella_lista(*lista_utenti, cognome);
    if (utente == NULL)
    {
        printf("Errore: utente non trovato.\n");
        return;
    }

    char nuovo_nome[50], nuovo_cognome[50];

    printf("Inserisci il nuovo nome (lascia vuoto per non modificare): ");
    fgets(nuovo_nome, 50, stdin);
    nuovo_nome[strcspn(nuovo_nome, "\n")] = 0;

    printf("Inserisci il nuovo cognome (lascia vuoto per non modificare): ");
    fgets(nuovo_cognome, 50, stdin);
    nuovo_cognome[strcspn(nuovo_cognome, "\n")] = 0;

    if (strlen(nuovo_nome) > 0)
        strncpy(utente->nome, nuovo_nome, sizeof(utente->nome) - 1);
    if (strlen(nuovo_cognome) > 0)
        strncpy(utente->cognome, nuovo_cognome, sizeof(utente->cognome) - 1);

    utente->nome[sizeof(utente->nome) - 1] = '\0';
    utente->cognome[sizeof(utente->cognome) - 1] = '\0';

    printf("Dati utente modificati con successo!\n");
}

// 7. Elimina utente registrato
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

// 8. Registra nuovo prestito
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

// 9. Modifica prestito esistente
void gestisci_modifica_prestito(persone lista_utenti)
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

    prestiti *p_lista_prestiti = get_prestiti_della_persona(utente);
    if (p_lista_prestiti == NULL || *p_lista_prestiti == NULL)
    {
        printf("L'utente non ha prestiti da modificare.\n");
        return;
    }

    printf("Inserisci la data del prestito da modificare (AAAA-MM-GG): ");
    leggi_stringa(data_prestito, 11);

    prestito p = cerca_prestito_nella_lista_per_data(*p_lista_prestiti, data_prestito);
    if (p == NULL)
    {
        printf("Prestito non trovato per la data specificata.\n");
        return;
    }

    char nuova_data[11];
    printf("Inserisci la nuova data del prestito (AAAA-MM-GG, lascia vuoto per non modificare): ");
    fgets(nuova_data, 11, stdin);
    nuova_data[strcspn(nuova_data, "\n")] = 0;

    if (strlen(nuova_data) > 0)
    {
        strncpy(p->data_prestito, nuova_data, sizeof(p->data_prestito) - 1);
        p->data_prestito[sizeof(p->data_prestito) - 1] = '\0';
    }

    printf("Prestito modificato con successo!\n");
}

// 10. Elimina prestito
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

// 11. Visualizza lista utenti registrati --> stampa_lista_persone

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
            gestisci_modifica_libro(&lista_principale_libri);
            break;
        case 3:
            gestisci_elimina_libro(&lista_principale_libri, lista_principale_utenti);
            break;
        case 4:
            stampa_lista_libri(lista_principale_libri);
            break;
        case 5:
            gestisci_registrazione_utente(&lista_principale_utenti);
            break;
        case 6:
            gestisci_modifica_utente(&lista_principale_utenti);
            break;
        case 7:
            gestisci_elimina_utente(&lista_principale_utenti);
            break;
        case 8:
            gestisci_registrazione_prestito(lista_principale_utenti, lista_principale_libri);
            break;
        case 9:
            gestisci_modifica_prestito(lista_principale_utenti);
            break;
        case 10:
            gestisci_elimina_prestito(lista_principale_utenti);
            break;
        case 11:
            stampa_lista_persone(lista_principale_utenti);
            break;
        case 12:
            printf("Uscita in corso...\n");
            break;
        default:
            printf("Scelta non valida. Riprova.\n");
            break;
        }
    } while (scelta != 12);

    distruggi_lista_libri(&lista_principale_libri);
    distruggi_lista_persone(&lista_principale_utenti);

    printf("Programma terminato. Arrivederci!\n");
    return 0;
}
