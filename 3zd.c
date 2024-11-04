#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
	char ime[50];
	char prezime[50];
	int godinaRodjenja;
	struct Osoba* next;
} Osoba;

// Funkcija za kreiranje nove osobe
Osoba* kreirajOsobu(char* ime, char* prezime, int godina) {
	Osoba* novaOsoba = (Osoba*)malloc(sizeof(Osoba));
	if (!novaOsoba) return NULL;

	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godinaRodjenja = godina;
	novaOsoba->next = NULL;
	return novaOsoba;
}

// A. Dodavanje elementa na početak liste
void dodajNaPocetak(Osoba** head, Osoba* novaOsoba) {
	novaOsoba->next = *head;
	*head = novaOsoba;
}

// B. Ispis liste
void ispisListe(Osoba* head) {
	Osoba* trenutna = head;
	while (trenutna) {
		printf("Ime: %s, Prezime: %s, Godina rođenja: %d\n", trenutna->ime, trenutna->prezime, trenutna->godinaRodjenja);
		trenutna = trenutna->next;
	}
}

// C. Dodavanje elementa na kraj liste
void dodajNaKraj(Osoba** head, Osoba* novaOsoba) {
	if (*head == NULL) {
		*head = novaOsoba;
	}
	else {
		Osoba* trenutna = *head;
		while (trenutna->next) {
			trenutna = trenutna->next;
		}
		trenutna->next = novaOsoba;
	}
}

// D. Pronalaženje elementa u listi po prezimenu
Osoba* pronadjiPoPrezimenu(Osoba* head, char* prezime) {
	Osoba* trenutna = head;
	while (trenutna) {
		if (strcmp(trenutna->prezime, prezime) == 0) {
			return trenutna;
		}
		trenutna = trenutna->next;
	}
	return NULL;
}

// E. Brisanje određenog elementa iz liste
void brisiElement(Osoba** head, char* prezime) {
	Osoba* trenutna = *head, * prethodna = NULL;

	while (trenutna && strcmp(trenutna->prezime, prezime) != 0) {
		prethodna = trenutna;
		trenutna = trenutna->next;
	}

	if (trenutna) {
		if (prethodna) {
			prethodna->next = trenutna->next;
		}
		else {
			*head = trenutna->next;
		}
		free(trenutna);
	}
}

// 3.A. Dodavanje elementa iza određenog elementa
void dodajIzaElementa(Osoba* head, char* prezime, Osoba* novaOsoba) {
	Osoba* trenutna = pronadjiPoPrezimenu(head, prezime);
	if (trenutna) {
		novaOsoba->next = trenutna->next;
		trenutna->next = novaOsoba;
	}
}

// 3.B. Dodavanje elementa ispred određenog elementa
void dodajIspredElementa(Osoba** head, char* prezime, Osoba* novaOsoba) {
	if (*head == NULL || strcmp((*head)->prezime, prezime) == 0) {
		dodajNaPocetak(head, novaOsoba);
	}
	else {
		Osoba* trenutna = *head;
		while (trenutna->next && strcmp(trenutna->next->prezime, prezime) != 0) {
			trenutna = trenutna->next;
		}
		if (trenutna->next) {
			novaOsoba->next = trenutna->next;
			trenutna->next = novaOsoba;
		}
	}
}

// 3.C. Sortiranje liste po prezimenima osoba
void sortirajListu(Osoba** head) {
	if (*head == NULL) return;

	Osoba* i, * j;
	for (i = *head; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (strcmp(i->prezime, j->prezime) > 0) {
				char tempIme[50], tempPrezime[50];
				int tempGodina;

				strcpy(tempIme, i->ime);
				strcpy(tempPrezime, i->prezime);
				tempGodina = i->godinaRodjenja;

				strcpy(i->ime, j->ime);
				strcpy(i->prezime, j->prezime);
				i->godinaRodjenja = j->godinaRodjenja;

				strcpy(j->ime, tempIme);
				strcpy(j->prezime, tempPrezime);
				j->godinaRodjenja = tempGodina;
			}
		}
	}
}

// 3.D. Upisivanje liste u datoteku
void upisiUFile(Osoba* head, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;

	Osoba* trenutna = head;
	while (trenutna) {
		fprintf(file, "%s %s %d\n", trenutna->ime, trenutna->prezime, trenutna->godinaRodjenja);
		trenutna = trenutna->next;
	}
	fclose(file);
}

// 3.E. Čitanje liste iz datoteke
void citajIzFile(Osoba** head, const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;

	char ime[50], prezime[50];
	int godina;
	while (fscanf(file, "%s %s %d", ime, prezime, &godina) != EOF) {
		Osoba* novaOsoba = kreirajOsobu(ime, prezime, godina);
		dodajNaKraj(head, novaOsoba);
	}
	fclose(file);
}

// Glavni program za testiranje
int main() {
	Osoba* head = NULL;

	dodajNaPocetak(&head, kreirajOsobu("Ana", "Anic", 1990));
	dodajNaKraj(&head, kreirajOsobu("Marko", "Markic", 1985));
	dodajNaKraj(&head, kreirajOsobu("Ivana", "Ivic", 1992));

	printf("Ispis liste:\n");
	ispisListe(head);

	Osoba* pronadjena = pronadjiPoPrezimenu(head, "Markic");
	if (pronadjena) printf("Pronadena osoba: %s %s\n", pronadjena->ime, pronadjena->prezime);

	dodajIzaElementa(head, "Anic", kreirajOsobu("Petar", "Petrovic", 1988));
	dodajIspredElementa(&head, "Ivic", kreirajOsobu("Luka", "Lukic", 1991));

	printf("\nLista nakon dodavanja iza i ispred:\n");
	ispisListe(head);

	sortirajListu(&head);
	printf("\nLista nakon sortiranja:\n");
	ispisListe(head);

	upisiUFile(head, "osobe.txt");

	// Oslobađanje memorije
	while (head) {
		Osoba* temp = head;
		head = head->next;
		free(temp);
	}

	return 0;
}