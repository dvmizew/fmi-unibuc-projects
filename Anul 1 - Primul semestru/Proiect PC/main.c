#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "angajat.h"

int main() {
    size_t nr_angajati;
    printf("Introduceti numarul de angajati: ");
    scanf("%llu", &nr_angajati);
    // Initializam un vector de angajati alocat dinamic
    angajat *vec_angajati = malloc(nr_angajati * sizeof(angajat));

    // Citim de la tastatura angajatii folosind pointerii la functia din structura angajat
    for (size_t i = 0; i < nr_angajati; i++) {
        printf("Nr: %llu\n", i + 1);
        vec_angajati[i].citireAngajat = citire_angajat;
        vec_angajati[i].afisareAngajat = afisare_angajat;
        vec_angajati[i].citireAngajat(&vec_angajati[i]);
    }

    // Afisam angajatii salvati in vector
    for (size_t i = 0; i < nr_angajati; i++) {
        printf("Nr: %llu\n", i + 1);
        vec_angajati[i].afisareAngajat(&vec_angajati[i]);
    }
    printf("Total salarii: %lld", calc_salariu_total(vec_angajati, nr_angajati));

    // Afisam angajatul cu cel mai mare salariu
    angajat max = cel_mai_mare_salariu(vec_angajati, nr_angajati);
    printf("\n\nAngajatul cu cel mai mare salariu este: \n");
    afisare_angajat(&max);
    
    // Scriem angajatii din vector intr-un fisier "export.txt"
    scriere_fisier(vec_angajati, nr_angajati);

    // Eliberam memoria alocata dinamic cu malloc folosind functia free
    free(vec_angajati);
    return 0;
}