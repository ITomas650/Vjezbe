#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50


typedef struct Directory {
    char name[MAX_NAME];
    struct Directory* parent; 
    struct Directory* subdirectories; 
    struct Directory* next; 
} Directory;


Directory* createDirectory(char* name, Directory* parent) {
    Directory* newDir = (Directory*)malloc(sizeof(Directory));
    if (!newDir) {
        printf("Greska: Nedovoljno memorije!\n");
        exit(1);
    }
    strcpy(newDir->name, name);
    newDir->parent = parent;
    newDir->subdirectories = NULL;
    newDir->next = NULL;
    return newDir;
}


void addSubdirectory(Directory* current, char* name) {
    Directory* newDir = createDirectory(name, current);
    if (current->subdirectories == NULL) {
        current->subdirectories = newDir;
    } else {
        Directory* temp = current->subdirectories;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newDir;
    }
    printf("Direktorij '%s' je uspjesno kreiran.\n", name);
}


Directory* findSubdirectory(Directory* current, char* name) {
    Directory* temp = current->subdirectories;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}


void listContents(Directory* current) {
    Directory* temp = current->subdirectories;
    if (temp == NULL) {
        printf("Ovaj direktorij je prazan.\n");
    } else {
        printf("Sadrzaj direktorija '%s':\n", current->name);
        while (temp != NULL) {
            printf("  %s\n", temp->name);
            temp = temp->next;
        }
    }
}


int main() {
    char command[10], dirName[MAX_NAME];
    Directory* root = createDirectory("root", NULL); 
    Directory* current = root; 

    printf("Simulacija DOS naredbi za direktorije.\n");

    while (1) {
        printf("\n[%s]> ", current->name);
        scanf("%s", command);

        if (strcmp(command, "md") == 0) { 
            scanf("%s", dirName);
            if (findSubdirectory(current, dirName)) {
                printf("Greska: Direktorij '%s' vec postoji.\n", dirName);
            } else {
                addSubdirectory(current, dirName);
            }
        } 
        else if (strcmp(command, "cd") == 0) { 
            scanf("%s", dirName);
            Directory* nextDir = findSubdirectory(current, dirName);
            if (nextDir) {
                current = nextDir;
            } else {
                printf("Greska: Direktorij '%s' ne postoji.\n", dirName);
            }
        } 
        else if (strcmp(command, "cd..") == 0) { 
            if (current->parent != NULL) {
                current = current->parent;
            } else {
                printf("Greska: Trenutno ste u root direktoriju.\n");
            }
        } 
        else if (strcmp(command, "dir") == 0) { 
            listContents(current);
        } 
        else if (strcmp(command, "izlaz") == 0) { 
            printf("Izlazak iz programa.\n");
            break;
        } 
        else {
            printf("Nepoznata naredba.\n");
        }
    }

    return 0;
}