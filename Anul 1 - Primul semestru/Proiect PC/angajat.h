#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_LEN 50

typedef struct angajat {
    int ID, varsta, salariu;
    char nume[MAX_LEN], prenume[MAX_LEN];
    char post[MAX_LEN];
    void (*citireAngajat)(struct angajat *);
    void (*afisareAngajat)(struct angajat *);
} angajat;

void citire_angajat(angajat *ang) {
    printf("Introduceti ID-ul angajatului: ");
    scanf("%d", &ang->ID);
    printf("Introduceti numele angajatului: ");
    scanf("%s", ang->nume);
    printf("Introduceti prenumele angajatului: ");
    scanf("%s", ang->prenume);
    printf("Introduceti varsta angajatului: ");
    scanf("%d", &ang->varsta);
    printf("Introduceti salariul angajatului: ");
    scanf("%d", &ang->salariu);
    printf("Post: \n");
    printf("1 - Casier\n2 - Ingrijitor\n3 - Director\n");
    unsigned int nr_post;
    printf("Introduceti cifra corespunzatoare postului angajatului: \n");
    scanf("%u", &nr_post);

    switch(nr_post) {
        case 1:
        strcpy(ang->post, "Casier");
        break;
        case 2:
        strcpy(ang->post, "Ingrijitor");
        break;
        case 3:
        strcpy(ang->post, "Director");
        break;
        default:
        printf("Nu ai introdus un post valid\n");
        strcpy(ang->post, "Niciun post");
        break;
    }
}

long long int calc_salariu_total(angajat *vec_angajati, size_t nr_elemente) {
    long long int total = 0;
    for (size_t i = 0; i < nr_elemente; i++)
        total += vec_angajati[i].salariu;
    return total;
}

angajat cel_mai_mare_salariu(angajat *vec_angajati, size_t nr_elemente) {
    int max_salariu = 0;
    angajat angajat_cu_salariu_maxim;
    for (size_t i = 0; i < nr_elemente; i++) {
        if (vec_angajati[i].salariu > max_salariu) {
            max_salariu = vec_angajati[i].salariu;
            angajat_cu_salariu_maxim = vec_angajati[i];
        }
    }
    return angajat_cu_salariu_maxim;
}

void afisare_angajat(angajat *ang) {
    printf("ID: %d, Nume: %s, Prenume: %s, Varsta: %d, Post: %s, Salariu: %d.\n", ang->ID, ang->nume, ang->prenume, ang->varsta, ang->post, ang->salariu);
}

void scriere_fisier(angajat *vec_angajati, size_t nr_elemente) {
    FILE *fisier = fopen("export.txt", "w+");
    if (!fisier) {
        printf("Eroare la scrierea fisierului pe disc");
        return;
    }
    for (size_t i = 0; i < nr_elemente; i++)
        fprintf(fisier, "ID: %d, Nume: %s, Prenume: %s, Varsta: %d, Post: %s, Salariu: %d.\n", vec_angajati[i].ID, vec_angajati[i].nume, vec_angajati[i].prenume, vec_angajati[i].varsta, vec_angajati[i].post, vec_angajati[i].salariu);
    
    fprintf(fisier,"\nTotal salarii: %lld", calc_salariu_total(vec_angajati, nr_elemente));
    fclose(fisier);
}