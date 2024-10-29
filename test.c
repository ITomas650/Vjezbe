#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godinaRodjenja;
    struct Osoba* sljedeca;  
} Osoba;

//kreiranje nove osobe
Osoba* kreirajOsobu(const char* ime, const char* prezime, int godinaRodjenja) {
    Osoba* novaOsoba = (Osoba*)malloc(sizeof(Osoba));
    if (novaOsoba == NULL) {
        printf("Greška pri alokaciji memorije.\n");
        exit(1);
    }
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godinaRodjenja = godinaRodjenja;
    novaOsoba->sljedeca = NULL;
    return novaOsoba;
}

// A. 
void dodajNaPocetak(Osoba** head, const char* ime, const char* prezime, int godinaRodjenja) {
    Osoba* novaOsoba = kreirajOsobu(ime, prezime, godinaRodjenja);
    novaOsoba->sljedeca = *head;
    *head = novaOsoba;
}

// B.
void ispisiListu(Osoba* head) {
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rođenja: %d\n", trenutna->ime, trenutna->prezime, trenutna->godinaRodjenja);
        trenutna = trenutna->sljedeca;
    }
}

// C. 
void dodajNaKraj(Osoba** head, const char* ime, const char* prezime, int godinaRodjenja) {
    Osoba* novaOsoba = kreirajOsobu(ime, prezime, godinaRodjenja);
    if (*head == NULL) {
        *head = novaOsoba;
    } else {
        Osoba* trenutna = *head;
        while (trenutna->sljedeca != NULL) {
            trenutna = trenutna->sljedeca;
        }
        trenutna->sljedeca = novaOsoba;
    }
}

// D.
Osoba* pronadjiPoPrezimenu(Osoba* head, const char* prezime) {
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        if (strcmp(trenutna->prezime, prezime) == 0) {
            return trenutna;
        }
        trenutna = trenutna->sljedeca;
    }
    return NULL;  
}

// E. 
void obrisiOsobu(Osoba** head, const char* prezime) {
    Osoba* trenutna = *head;
    Osoba* prethodna = NULL;

    while (trenutna != NULL && strcmp(trenutna->prezime, prezime) != 0) {
        prethodna = trenutna;
        trenutna = trenutna->sljedeca;
    }

    if (trenutna == NULL) {
        printf("Osoba s prezimenom %s nije pronađena.\n", prezime);
        return;
    }

    if (prethodna == NULL) {  
        *head = trenutna->sljedeca;
    } else {
        prethodna->sljedeca = trenutna->sljedeca;
    }

    free(trenutna);
    printf("Osoba s prezimenom %s je obrisana.\n", prezime);
}


void oslobodiListu(Osoba* head) {
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        Osoba* zaBrisanje = trenutna;
        trenutna = trenutna->sljedeca;
        free(zaBrisanje);
    }
}


int main() {
    Osoba* head = NULL;

    dodajNaPocetak(&head, "Ivan", "Ivić", 1990);
    dodajNaKraj(&head, "Ana", "Anić", 1992);
    dodajNaPocetak(&head, "Marko", "Markić", 1985);

    printf("Lista nakon dodavanja elemenata:\n");
    ispisiListu(head);

    Osoba* trazenaOsoba = pronadjiPoPrezimenu(head, "Anić");
    if (trazenaOsoba != NULL) {
        printf("\nPronađena osoba: Ime: %s, Prezime: %s, Godina rođenja: %d\n", trazenaOsoba->ime, trazenaOsoba->prezime, trazenaOsoba->godinaRodjenja);
    } else {
        printf("\nOsoba s prezimenom Anić nije pronađena.\n");
    }

    obrisiOsobu(&head, "Markić");

    printf("\nLista nakon brisanja elementa:\n");
    ispisiListu(head);

    oslobodiListu(head);
    return 0;
}