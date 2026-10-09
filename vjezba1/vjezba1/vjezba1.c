#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define max_br_bodova 110

typedef struct _Student {
	char ime[20];
	char prezime[30];
	int bodovi;
} stud;

int main() {
	char buffer[50];
	int brojac = 0;
	FILE* fp = fopen("popis.txt", "r");
	if (fp == NULL) {
		printf("Greska!");
		return -1;
	}

	while (fgets(buffer, 50, fp) != NULL) {
		brojac++;
	}

	rewind(fp);

	stud* Studenti = NULL;
	Studenti = (stud*)malloc(sizeof(stud) * brojac);

	if (Studenti == NULL && brojac > 0) {
		printf("Greska2!");
		fclose(fp);
		return -2;
	}

	int i;
	for (i = 0; i < brojac; i++) {
		fscanf(fp, " %s %s %d", Studenti[i].ime, Studenti[i].prezime, &Studenti[i].bodovi);
	}


	for (i = 0; i < brojac; i++) {
		double relativni_br_bodova = (double)Studenti[i].bodovi / max_br_bodova * 100;
		printf(" %s %s %d %.2f\n", Studenti[i].ime, Studenti[i].prezime, Studenti[i].bodovi, relativni_br_bodova);
	}

	fclose(fp);
	free(Studenti);

	return 0;
}