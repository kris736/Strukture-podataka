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

int insertBegin(Position head, char* ime, char* prezime, int godiste) {
    Position newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("greska kod alokacije memorije u insertBeginu!\n");
        return -1;
    }

    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->year = godiste;

    newPerson->next = head->next;
    head->next = newPerson;

    return 0;
}

int insertEnd(Position head, char* ime, char* prezime, int godiste) {
    Position newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("greska kod alokacije memorije u insertEndu!\n");
        return -1;
    }

    strcpy(newPerson->name, ime);
    strcpy(newPerson->lastName, prezime);
    newPerson->year = godiste;
    newPerson->next = NULL;

    while (head->next != NULL) {
        head = head->next;
    }
    head->next = newPerson;

    return 0;
}

int printList(Position head) {
    if (head == NULL) {
        printf("nema osoba u listi.\n");
        return -1;
    }
    while (head != NULL) {
        printf("%s %s %d\n", head->name, head->lastName, head->year);
        head = head->next;
    }

    return 0;
}

Position findLastName(Position head, char* prezime) {
    Position curr = head->next;

    while (curr != NULL) {
        if (strcmp(curr->lastName, prezime) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int deletePerson(Position head, char* prezime) {
    Position prev = head;
    Position curr = head->next;

    while (curr != NULL && strcmp(curr->lastName, prezime) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("ne postoji osoba s unesenim prezimenom!\n");
        return -1;
    }

    prev->next = curr->next;
    free(curr);

    return 0;
}


int main() {
    Person Head = {
        .name = {0},
        .lastName = " ",
        .year = 0,
        .next = NULL
    };

    int i;
    int n;
    char odgovor;
    char ime[20];
    char prezime[30];
    int godiste;

    printf("koliko osoba zelite unijeti u listu? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nunesite ime: ");
        scanf("%19s", ime);
        printf("\nunesite prezime: ");
        scanf("%29s", prezime);
        printf("\nunesite godinu rodenja: ");
        scanf("%d", &godiste);

        insertEnd(&Head, ime, prezime, godiste);
    }

    printf("\nUnesene osobe:\n");
    printList(Head.next);

    printf("\nzelite li dodati osobu na pocetak liste(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite ime: ");
        scanf("%19s", ime);
        printf("\nunesite prezime: ");
        scanf("%29s", prezime);
        printf("\nunesite godiste: ");
        scanf("%d", &godiste);

        insertBegin(&Head, ime, prezime, godiste);
        printf("\nlista osoba nakon dodavanja na pocetak: \n");
        printList(Head.next);
    }

    printf("\nzelite li dodati osobu na kraj liste(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite ime: ");
        scanf("%19s", ime);
        printf("\nunesite prezime: ");
        scanf("%29s", prezime);
        printf("\nunesite godiste: ");
        scanf("%d", &godiste);

        insertEnd(&Head, ime, prezime, godiste);
        printf("\nlista osoba nakon dodavanja na kraj: \n");
        printList(Head.next);
    }

    printf("\nzelite li pronaci osobu po prezimenu(odgovorite s d/n)?");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite prezime: ");
        scanf("%29s", prezime);

        Position trazenaOsoba = findLastName(&Head, prezime);
        if (trazenaOsoba != NULL) {
            printf("pronadena osoba: %s %s %d\n", trazenaOsoba->name, trazenaOsoba->lastName, trazenaOsoba->year);
        }
        else {
            printf("ne postoji osoba s unesenim prezimenom!\n");
        }
    }

    printf("\nzelite li obrisati osobu s liste(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite prezime osobe koju zelite obrisati: ");
        scanf("%29s", prezime);
        deletePerson(&Head, prezime);

        printf("\nlista osoba nakon brisanja:\n");
        printList(Head.next);
    }

    return 0;
}