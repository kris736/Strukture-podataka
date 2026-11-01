#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;
typedef struct Poly {
    int koeficijent;
    int potencija;
    Position next;
} polynom;


Position newPoly(int koef, int pot)
{
    Position new = (Position)malloc(sizeof(struct Poly));
    if (new == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    new->koeficijent = koef;
    new->potencija = pot;
    new->next = NULL;

    return new;
}


int insertSorted(Position head, Position newPoly)
{
    Position q = head;

    while (q->next != NULL && q->next->potencija > newPoly->potencija) {
        q = q->next;
    }

    if (q->next != NULL && q->next->potencija == newPoly->potencija) {
        q->next->koeficijent += newPoly->koeficijent;

        free(newPoly);

        if (q->next->koeficijent == 0) {
            Position temp = q->next;
            q->next = temp->next;
            free(temp);
        }

        return 0;
    }

    newPoly->next = q->next;
    q->next = newPoly;

    return 0;
}


int citanjePoly(FILE* fp, Position head)
{
    int koef, pot;
    int znak;
    Position temp;

    while (fscanf(fp, "%d %d", &koef, &pot) == 2) {

        temp = newPoly(koef, pot);

        if (temp == NULL) {
            return -1;
        }

        if (insertSorted(head, temp) == -1) {
            return -1;
        }

        znak = fgetc(fp);

        while (znak == ' ' || znak == '\t') {
            znak = fgetc(fp);
        }

        if (znak == '\n' || znak == EOF) {
            break;
        }

        ungetc(znak, fp);
    }

    return 0;
}


int printPoly(Position head)
{
    Position q = head->next;

    if (q == NULL) {
        printf("nema polinoma\n");
        return 0;
    }

    while (q != NULL) {
        if (q == head->next) {
            if (q->koeficijent < 0) {
                printf(" - ");
            }
        }
        else {
            if (q->koeficijent > 0) {
                printf(" + ");
            }
        }

        printf("%dx^%d", abs(q->koeficijent), q->potencija);
        q = q->next;
    }

    printf("\n");

    return 0;
}


int zbrajanjePoly(Position first, Position second, Position result)
{
    Position q, temp;

    for (q = first->next; q != NULL; q = q->next) {
        temp = newPoly(q->koeficijent, q->potencija);

        if (temp == NULL)
            return -1;

        if (insertSorted(result, temp) == -1)
            return -1;
    }

    for (q = second->next; q != NULL; q = q->next) {
        temp = newPoly(q->koeficijent, q->potencija);

        if (temp == NULL)
            return -1;

        if (insertSorted(result, temp) == -1)
            return -1;
    }

    return 0;
}


int mnozenjePoly(Position first, Position second, Position result)
{
    Position q, p, temp;
    int koef, pot;

    for (q = first->next; q != NULL; q = q->next) {

        for (p = second->next; p != NULL; p = p->next) {

            koef = q->koeficijent * p->koeficijent;
            pot = q->potencija + p->potencija;

            temp = newPoly(koef, pot);

            if (temp == NULL)
                return -1;

            if (insertSorted(result, temp) == -1)
                return -1;
        }
    }

    return 0;
}


int deletePoly(Position head)
{
    Position temp;

    while (head->next != NULL) {

        temp = head->next;
        head->next = temp->next;

        free(temp);
    }

    return 0;
}

int otvaranjeDatoteke(Position headFirst, Position headSecond)
{
    FILE* fp = fopen("polinomi.txt", "r");

    if (fp == NULL) {
        printf("greska pri otvaranju datoteke!\n");
        return -1;
    }

    if (citanjePoly(fp, headFirst) == -1) {
        printf("Greska pri citanju prvog polinoma!\n");
        fclose(fp);
        deletePoly(headFirst);
        return -1;
    }

    if (citanjePoly(fp, headSecond) == -1) {
        printf("Greska pri citanju drugog polinoma!\n");
        fclose(fp);
        deletePoly(headFirst);
        deletePoly(headSecond);
        return -1;
    }

    fclose(fp);

    return 0;
}

int main()
{

    struct Poly headFirst = {
    .koeficijent = 0,
    .potencija = 0,
    .next = NULL
    };

    struct Poly headSecond = {
        .koeficijent = 0,
        .potencija = 0,
        .next = NULL
    };

    struct Poly headZbroj = {
        .koeficijent = 0,
        .potencija = 0,
        .next = NULL
    };

    struct Poly headUmnozak = {
        .koeficijent = 0,
        .potencija = 0,
        .next = NULL
    };

    otvaranjeDatoteke(&headFirst, &headSecond);

    printf("Prvi polinom:\n");
    printPoly(&headFirst);

    printf("Drugi polinom:\n");
    printPoly(&headSecond);

    if (zbrajanjePoly(&headFirst, &headSecond, &headZbroj) == -1) {
        printf("Greska pri zbrajanju!\n");
        return -1;
    }

    printf("\nZbroj polinoma:\n");
    printPoly(&headZbroj);

    if (mnozenjePoly(&headFirst, &headSecond, &headUmnozak) == -1) {
        printf("Greska pri mnozenju!\n");
        return -1;
    }

    printf("Umnozak polinoma:\n");
    printPoly(&headUmnozak);


    deletePoly(&headFirst);
    deletePoly(&headSecond);
    deletePoly(&headZbroj);
    deletePoly(&headUmnozak);

    return 0;
}
