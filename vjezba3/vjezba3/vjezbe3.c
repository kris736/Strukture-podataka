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

/*PRVI DIO ZADATKA, ZADATAK 2*/

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

/*DRUGI DIO ZADATKA, ZADATAK 3*/

int insertAfter(Position head, char* trazenoPrezime, char* ime, char* prezime, int godiste) {
    Position trazenaOsoba = findLastName(head, trazenoPrezime);
    if (trazenaOsoba == NULL) {
        printf("ne postoji osoba s unesenim prezimenom!\n");
        return -1;
    }

    Position novaOsoba = (Position)malloc(sizeof(Person));
    if (novaOsoba == NULL) {
        printf("greska kod alokacije memorije (insertAfter)!\n");
        return -1;
    }

    strcpy(novaOsoba->name, ime);
    strcpy(novaOsoba->lastName, prezime);
    novaOsoba->year = godiste;

    novaOsoba->next = trazenaOsoba->next;
    trazenaOsoba->next = novaOsoba;

    return 0;
}

int insertBefore(Position head, char* trazenoPrezime, char* ime, char* prezime, int godiste) {
    Position prev = head;
    Position curr = head->next;

    while (curr != NULL && strcmp(curr->lastName, trazenoPrezime) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) { 
        printf("ne postoji osoba s unesenim prezimenom!\n");
        return -1;
    }

    Position novaOsoba = (Position)malloc(sizeof(Person));
    if (novaOsoba == NULL) {
        printf("greska kod alokacije memorije (insertBefore)!\n");
        return -1;
    }

    strcpy(novaOsoba->name, ime);
    strcpy(novaOsoba->lastName, prezime);
    novaOsoba->year = godiste;

    novaOsoba->next = curr;
    prev->next = novaOsoba;


    return 0;
}

int sortFunkciju(Position head) {
    Position p = head->next;
    Position q = head;
    Position temp = NULL;
    while (p->next != NULL) {
        if (strcmp(p->lastName, p->next->lastName) > 0) {
            temp = p->next;
            q->next = temp;
            p->next = temp->next;
            temp->next = p;
            q = head;
            p = q->next;
        }
        else {
            q = p;
            p = p->next;
        }
    }

    return 0;
}

int upisujeListuUDatoteku(Position head) {
    FILE* fp = fopen("popis3.txt", "w");
    if (fp == NULL) {
        printf("greska pri otvaranju datoteke!");
        return -1;
    }
    Position curr = head->next;
    while (curr != NULL) {
        fprintf(fp, "%s %s %d\n", curr->name, curr->lastName, curr->year);
        curr = curr->next;
    }

    fclose(fp);

    return 0;
}

int citaListuIzDatoteke(Position head) {
    FILE* fp = fopen("popis3.txt", "r");
    if (fp == NULL) {
        printf("greska pri otvaranju datoteke!");
        return -1;
    }

    char ime[20];
    char prezime[30];
    int godiste;

    while (fscanf(fp, "%19s %29s %d", ime, prezime, &godiste) == 3) {
        if (insertEnd(head, ime, prezime, godiste) != 0) {
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);
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
    char trazenoPrezime[30];

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

    printf("\nzelite li pronaci osobu po prezimenu(odgovorite s d/n)? ");
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

    printf("\nzelite li dodati osobu iza odredene osobe(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite iza kojeg prezimena zelite dodati novu osobu: ");
        scanf("%29s", trazenoPrezime);
        printf("\nunesite ime nove osobe: ");
        scanf("%19s", ime);
        printf("\nunesite prezime nove osobe: ");
        scanf("%29s", prezime);
        printf("\nunesite godinu rodenja nove osobe: ");
        scanf("%d", &godiste);

        insertAfter(&Head, trazenoPrezime, ime, prezime, godiste);
        printf("\nlista nakon dodavanja iza osobe:\n");
        printList(Head.next);
    }

    printf("\nzelite li dodati osobu ispred odredene osobe(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        printf("\nunesite ispred kojeg prezimena zelite dodati novu osobu? ");
        scanf("%29s", trazenoPrezime);
        printf("\nunesite ime nove osobe: ");
        scanf("%19s", ime);
        printf("\nunesite prezime nove osobe: ");
        scanf("%29s", prezime);
        printf("\nunesite godinu rodenja nove osobe: ");
        scanf("%d", &godiste);

        insertBefore(&Head, trazenoPrezime, ime, prezime, godiste);
        printf("\nlista nakon dodavanja ispred osobe:\n");
        printList(Head.next);
    }


    printf("\nzelite li sortirati funkciju(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        sortFunkciju(&Head);
        printf("\nlista nakon sortiranja:\n");
        printList(Head.next);
    }

    printf("\nzelite li zapisati listu u datoteku(odgovorite s d/n)? ");
    scanf(" %c", &odgovor);
    if (odgovor == 'd') {
        if (upisujeListuUDatoteku(&Head) == 0) {
            printf("\nlista je zapisana u popis3.txt.\n");
        }
    }

    printf("\nzelite li da program procita listu iz datoteke (d/n)? ");
    scanf(" %c", &odgovor);

    if (odgovor == 'd') {
        Person novaHead = {
            .name = {0},
            .lastName = " ",
            .year = 0,
            .next = NULL
        };

        if (citaListuIzDatoteke(&novaHead) == 0) {
            printf("\nosobe procitane iz datoteke:\n");
            printList(novaHead.next);
        }
    }

    return 0;

}