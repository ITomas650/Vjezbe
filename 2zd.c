#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Osoba
{
    char ime[100];
    char prezime[100];
    int god;
    struct Osoba* next;
    
}Osoba;
Osoba* Kreiraj(char* ime,char* prezime,int god){
    Osoba* NovaOsoba= (Osoba*)malloc(sizeof(Osoba));
    if(!NovaOsoba){
        printf("Greska alokacija");
        return NULL;   
        }
    strcpy(NovaOsoba->ime,ime);
    strcpy(NovaOsoba->prezime,prezime);
    NovaOsoba->god=god;
    NovaOsoba->next=NULL;

}
void DodajOsobuNaPocetak(Osoba** head,char* ime,char* prezime,int god){
    	Osoba* NovaO=Kreiraj(ime,prezime,god);
        NovaO->next=*head;
        *head=NovaO;

}
void DodajNaKraj(Osoba** head,char* ime,char* prezime,int god){
    Osoba* NovaO=Kreiraj(ime,prezime,god);
    if(*head==NULL){
        *head=NovaO;
        return;
    }
    Osoba* trenutna = *head;
    while(trenutna->next !=NULL){
        trenutna=trenutna->next;
    }
trenutna->next=NovaO;

}
void Ispis(Osoba* head){
    Osoba* trenutna =head;
    while(trenutna!=NULL){
        printf("%s %s %d\n",trenutna->ime,trenutna->prezime,trenutna->god);
        trenutna=trenutna->next;
    }
}
void IspisJedna(Osoba* head){
    printf("%s %s %d\n",head->ime,head->prezime,head->god);

}
void PronadiPrezime(Osoba* head, char* prezime){
    Osoba* trenutna =head;
    while(trenutna!=NULL){
       
        if(strcmp(trenutna->prezime,prezime)==0){
            printf("pronaden: ");
            IspisJedna(trenutna);
        }
        trenutna=trenutna->next;
    }


}




void ObrisiElement(Osoba** head, char* prezime) {
	Osoba* trenutna = *head;
	Osoba* prethodna = NULL;
	if (trenutna == NULL) {
		printf("lista je prazna\n");
		return;
	}
    if(strcmp(trenutna->prezime,prezime) == 0){
		*head = trenutna->next;
		printf("obrisan prvi");
		return;
            
            
            
        }
    while(trenutna!=NULL && strcmp(trenutna->prezime, prezime)!=0){
		prethodna = trenutna;
		trenutna = trenutna->next;
         
    }
	if (trenutna == NULL) {
		printf("nije pronaden\n");
		return;
	
	}
	prethodna->next = trenutna->next;
	free(trenutna);
}


int main(){
    Osoba* head=NULL;
    	DodajOsobuNaPocetak(&head,"I","T2",2005);
        DodajNaKraj(&head,"I2","T",2005);
        Ispis(head);
    	PronadiPrezime(head,"T");
        PronadiPrezime(head,"T2");
        ObrisiElement(&head, "T");
		Ispis(head);
}           