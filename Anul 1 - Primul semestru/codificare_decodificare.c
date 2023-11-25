#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int nr_legitimatie;
    char nume[30];
} student;

int rotatie_stanga(int n, unsigned int biti) {
    return (n << biti) | (n >> (8 * sizeof(int) - biti));
}

int rotatie_dreapta(int n, unsigned int biti) {
    return (n >> biti) | (n >> (8 * sizeof(int) - biti));
}

void citire(student *stud, size_t nr_studenti) {
    for (size_t i = 1; i <= nr_studenti; i++) {
        printf("Introdu datele pentru studentul %d :\n", i);
        scanf("%s %d", stud[i].nume, &stud[i].nr_legitimatie);
    }
}

void codificare(student *stud, size_t nr_studenti, int r, int key) {
    if (r < 0 || r > (8 * sizeof(int) - 1)) {
        printf("Cheia nu este intre 0 si (2 ^ 5) - 1");
        return;
    }
    for (size_t i = 1; i <= nr_studenti; i++) {
        // Codificare nume student
        strcpy(stud[i].nume, strrev(stud[i].nume));
        // Codificare nr_legitimatie
        int nr_legitimatie = stud[i].nr_legitimatie;
        nr_legitimatie = rotatie_stanga(nr_legitimatie, r);
        nr_legitimatie ^= key;
        stud[i].nr_legitimatie = nr_legitimatie;
    }
}

void scriere_fisier(const char *nume_fisier, student *stud, int nr_studenti) {
    FILE *fisier = fopen(nume_fisier, "w");
    if (fisier == NULL) {
        printf("Fisierul nu a putut fi deschis pentru scriere");
        return;
    }
    for (size_t i = 1; i <= nr_studenti; i++) {
        fprintf(fisier, "%s %d\n", stud[i].nume, stud[i].nr_legitimatie);
    }
    fclose(fisier);
}

int vocala(char s) {
    if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'A' || s == 'E' || s == 'I' || s == 'O' ||
        s == 'U')
        return 1;
    return 0;
}

void afisare_decodificat(const char *nume_fisier, student *stud, size_t nr_studenti, int r, int key,
                         const char *nume_fisier_output) {
    FILE *fisier = fopen(nume_fisier, "r");
    if (fisier == NULL) {
        printf("Fisierul nu a putut fi deschis pentru decodificare");
        return;
    }

    FILE *fisier_iesire = fopen(nume_fisier_output, "w");
    if (fisier_iesire == NULL) {
        printf("Fisierul de output nu a putut fi deschis/creat");
        return;
    }

    student curent;
    size_t i = 0;
    while (fscanf(fisier, "%s %d", curent.nume, &curent.nr_legitimatie) > 0) {
        // decodificare nume
        char *nume_decodificat;
        strcpy(nume_decodificat, strrev(curent.nume));
        nume_decodificat[strlen(nume_decodificat)] = '\0';
        // decodificare nr_legitimatie
        int nr_legitimatie = curent.nr_legitimatie;
        nr_legitimatie ^= key;
        nr_legitimatie = rotatie_dreapta(nr_legitimatie, r); // il rotim in sens invers codificarii

        if (nr_legitimatie % 3 == 0 && vocala(nume_decodificat[0])) {
            fprintf(fisier_iesire, "%s %d\n", nume_decodificat, nr_legitimatie);
        }
        i++;
    }
    fclose(fisier);
    fclose(fisier_iesire);
}

int main() {
    student studenti[100];
    unsigned int nr_studenti, r = 7, key = 15;
    printf("Cati studenti?: \n");
    scanf("%d", &nr_studenti);
    citire(studenti, nr_studenti);
    codificare(studenti, nr_studenti, r, key);
    scriere_fisier("rez.txt", studenti, nr_studenti);
    afisare_decodificat("rez.txt", studenti, nr_studenti, r, key, "rez_decodificat.txt");
}