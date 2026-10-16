#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;
typedef struct _Person {
    char name[20];
    char lastName[30];
    int year;
    Position next;
} Person;

Position insertBegin(Position head, char ime[], char prezime[], int godiste) {
    Position newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("greska pri alokaciji memorije(insertBegin)!\n");
        return head;
    }

    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->year = godiste;
    newPerson->next = head;

    return newPerson;
}

Position insertEnd(Position head, char ime[], char prezime[], int godiste) {
    Position newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("greska pri alokaciji memorije(insertEnd)!\n");
        return head;
    }

    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->year = godiste;
    newPerson->next = NULL;

    if (head == NULL) {
        return newPerson;
    }

    Position pom = head;
    while (pom->next != NULL) {
        pom = pom->next;
    }
    pom->next = newPerson;

    return head;
}

void printList(Position head) {
    if (head == NULL) {
        printf("nema osoba u listi.\n");
        return;
    }

    while (head != NULL) {
        printf(" %s %s %d\n", head->name, head->lastName, head->year);
        head = head->next;
    }
}

Position findLastName(Position head, char prezime[]){

    while(head!=NULL){
            if (strcmp(head->lastName, prezime) == 0) {
                return head;
            }
            head = head->next;
        }
    return NULL;
}

Position deletePerson(Position head, char prezime[]) {
    Position prev = NULL;
    Position curr = head;
    
    while (curr != NULL && strcmp(curr->lastName, prezime) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("osoba nije pronadena.\n");
        return head;
    }
    if (prev == NULL) {
        head = curr->next;
    }
    else {
        prev->next = curr->next;
    }

    free(curr);
    printf("osoba je obrisana s liste.\n");

    return head;
}

void freeList(Position head) {
    while (head != NULL) {
        Position pom = head;
        head = head->next;
        free(pom);
    }
}

int main(void) {
    Position head = NULL;
    Position pronadenaOsoba;

    char ime[20];
    char prezime[30];
    int godiste;
    char odgovor;
    int n;
    int i;

    printf("koliko osoba zelite unijeti u listu? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nunesite ime: ");
        scanf("%s", ime);
        printf("\nunesite prezime: ");
        scanf("%s", prezime);
        printf("\nunesite godiste : ");
        scanf("%d", &godiste);

        head = insertEnd(head, ime, prezime, godiste);
    }

    printf("\nlista osoba:\n");
    printList(head);

    printf("\nzelite li dodati osobu na pocetak liste(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite ime: ");
        scanf("%s", ime);
        printf("\nunesite prezime: ");
        scanf("%s", prezime);
        printf("\nunesite godiste: ");
        scanf("%d", &godiste);

        head = insertBegin(head, ime, prezime, godiste);
        printf("\nlista osoba nakon dodavanja na pocetak: \n");
        printList(head);
    }


    printf("\nzelite li dodati osobu na kraj liste(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite ime: ");
        scanf("%s", ime);
        printf("\nunesite prezime: ");
        scanf("%s", prezime);
        printf("\nunesite godiste: ");
        scanf("%d", &godiste);

        head = insertEnd(head, ime, prezime, godiste);
        printf("\nlista osoba nakon dodavanja na kraj: \n");
        printList(head);
    }


    printf("\nzelite li pronaci osobu po prezimenu(odgovorite s d/n)?");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite prezime: ");
        scanf("%s", prezime);

        pronadenaOsoba = findLastName(head, prezime);

        if (pronadenaOsoba != NULL) {
            printf("%s %s %d\n",pronadenaOsoba->name, pronadenaOsoba->lastName, pronadenaOsoba->year);
        }
        else {
            printf("osoba nije pronadena.\n");
        }
    }


    printf("\nzelite li obrisati osobu s liste(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite prezime osobe koju zelite obrisati: ");
        scanf("%s", prezime);
        head = deletePerson(head, prezime);

        printf("\nlista osoba nakon brisanja:\n");
        printList(head);
    }

    freeList(head);

    return 0;
}