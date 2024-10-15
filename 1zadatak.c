#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct 
{
    char ime[MAX];
    char prezime[MAX];
    int bodovi;
}Student;

int brojredaka(char *);
void ucitavanjestudenta(char *, Student *, int);
void ispis(Student *, int);

int main(){
    char nazivdatoteke[] = "studenti.txt";
    int brstudenata= brojredaka(nazivdatoteke);
    Student *studenti = (Student *)malloc(brstudenata * sizeof(Student));
    if (!studenti) {
        printf("Greška pri alokaciji memorije!\n");
        return -1;
    }
    ucitavanjestudenta(nazivdatoteke,studenti,brstudenata);
    ispis(studenti,brstudenata);
    return 0;
}
int brojredaka(char *datoteka){
FILE *txt = fopen(datoteka,"r");
if(!txt){
    printf("GRESKA\n");
    return -1;
}
int redovi=0;
char red[1024];
while(fgets( red,1024,txt)){
    redovi++;
}
fclose(txt);
return redovi;
}
void ucitavanjestudenta(char *datoteka, Student *studenti, int brojstd){
FILE *txt = fopen(datoteka,"r");
if(!txt){
    printf("GRESKA\n");
    return -1;
}

for(int i =0; i<brojstd; i++){
    fscanf(txt,"%s %s %d", studenti[i].ime,studenti[i].prezime,studenti[i].bodovi);

}
fclose(txt);
}
void ispis(Student *studenti, int brojstd){
    for (int i = 0; i < brojstd; i++) {
    float relativniBodovi = (float)studenti[i].bodovi / MAX_BODOVI * 100;
    printf("%s\t%s\t%d\t\t%.2f%%\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativniBodovi);
    }


}