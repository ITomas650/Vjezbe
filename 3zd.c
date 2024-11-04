#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
	char ime[100];
	char prezime[100];
	int god;
	struct Osoba* next;
} Osoba;

Osoba* Kreiraj(char* ime, char* prezime, int god) {
	Osoba* NovaOsoba = (Osoba*)malloc(sizeof(Osoba));
	if (!NovaOsoba) {
		printf("Greska pri alokaciji memorije\n");
		return NULL;
	}
	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->god = god;
	NovaOsoba->next = NULL;
	return NovaOsoba;
}

void DodajNaPocetak(Osoba** head, char* ime, char* prezime, int god) {
	Osoba* NovaO = Kreiraj(ime, prezime, god);
	NovaO->next = *head;
	*head = NovaO;
}

void DodajNaKraj(Osoba** head, char* ime, char* prezime, int god) {
	Osoba* NovaO = Kreiraj(ime, prezime, god);
	if (*head == NULL) {
		*head = NovaO;
		return;
	}
	Osoba* trenutna = *head;
	while (trenutna->next != NULL) {
		trenutna = trenutna->next;
	}
	trenutna->next = NovaO;
}

void Ispis(Osoba* head) {
	Osoba* trenutna = head;
	while (trenutna != NULL) {
		printf("%s %s %d\n", trenutna->ime, trenutna->prezime, trenutna->god);
		trenutna = trenutna->next;
	}
}

// A. Funkcija za dodavanje elementa iza određene osobe
void DodajIza(Osoba* head, char* prezimeTrazeno, char* ime, char* prezime, int god) {
	Osoba* trenutna = head;
	while (trenutna != NULL && strcmp(trenutna->prezime, prezimeTrazeno) != 0) {
		trenutna = trenutna->next;
	}
	if (trenutna == NULL) {
		printf("Osoba s prezimenom %s nije pronadena.\n", prezimeTrazeno);
		return;
	}
	Osoba* NovaO = Kreiraj(ime, prezime, god);
	NovaO->next = trenutna->next;
	trenutna->next = NovaO;
}

// B. Funkcija za dodavanje elementa ispred određene osobe
void DodajIspred(Osoba** head, char* prezimeTrazeno, char* ime, char* prezime, int god) {
	Osoba* trenutna = *head;
	Osoba* prethodna = NULL;

	while (trenutna != NULL && strcmp(trenutna->prezime, prezimeTrazeno) != 0) {
		prethodna = trenutna;
		trenutna = trenutna->next;
	}

	if (trenutna == NULL) {
		printf("Osoba s prezimenom %s nije pronadena.\n", prezimeTrazeno);
		return;
	}

	Osoba* NovaO = Kreiraj(ime, prezime, god);
	if (prethodna == NULL) { // Ako je tražena osoba prvi element
		NovaO->next = *head;
		*head = NovaO;
	}
	else {
		NovaO->next = trenutna;
		prethodna->next = NovaO;
	}
}

int main() {
	Osoba* head = NULL;

	DodajNaPocetak(&head, "Ivo", "Ivic", 1990);
	DodajNaKraj(&head, "Ana", "Anic", 1985);
	printf("Pocetna lista:\n");
	Ispis(head);

	printf("\nDodavanje iza odredene osobe:\n");
	DodajIza(head, "Ivic", "Marko", "Maric", 1995);
	Ispis(head);

	printf("\nDodavanje ispred odredene osobe:\n");
	DodajIspred(&head, "Anic", "Petar", "Petrovic", 1975);
	Ispis(head);

	return 0;
}