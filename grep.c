#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Utilizare: %s f freg fisier\n", argv[0]);
        return 1;
    }

    // deschidem fisierul pentru pattern si pentru fisierul in care cautam
    FILE *pattern = fopen(argv[2], "r");
    if (!pattern) {
        perror(argv[2]);
        return 1;
    }
    FILE *fisier = fopen(argv[3], "r");
    if (!fisier) {
        perror(argv[3]);
        fclose(pattern);
        return 1;
    }

    // mergem pana la finalul fisierului cu fseek ca sa putem folosi ftell si sa aflam dimensiunea in biti a fisierului
    fseek(pattern, 0, SEEK_END);
    size_t dimensiune_pattern = ftell(pattern);
    if (dimensiune_pattern == 0) {
        fprintf(stderr, "Fisierul de pattern este gol\n");
        fclose(pattern);
        fclose(fisier);
        return 1;
    }
    rewind(pattern);

    // alocam dinamic in functie de dimensiunea pe care am gasit-o
    char *regula = malloc(sizeof(char) * (dimensiune_pattern + 1));
    if (!regula) {
        perror("Malloc-ul pentru array-ul in care salvam regula nu a functionat");
        fclose(pattern);
        fclose(fisier);
        return -1;
    }
    //salvam cuvantul in memorie
    if (!fgets(regula, dimensiune_pattern + 1, pattern)) {
        perror("Eroare la citirea fisierului de pattern");
        free(regula);
        fclose(pattern);
        fclose(fisier);
        return 1;
    }

    char *buff = malloc(sizeof(char) * 1024);
    if (!buff) {
        perror("Malloc-ul pentru array-ul in care salvam block-uri de 1024 de biti nu a functionat");
        free(regula);
        fclose(pattern);
        fclose(fisier);
        return -1;
    }

    while(fgets(buff, 1024, fisier)) {
        // am gasit un match, am afisat
        if (strstr(buff, regula) != NULL) {
            printf("%s", buff);
        }
        // alocam cate 1024 de biti bufferului ca sa fie cat de cat eficient
        char *temp = realloc(buff, sizeof(char) * 1024);
        if (!temp) {
            perror("Nu mai avem memorie pentru a aloca inca 1024 de biti");
        }
        buff = temp;
    }

    free(regula);
    free(buff);
    fclose(pattern);
    fclose(fisier);

    return 0;
}
