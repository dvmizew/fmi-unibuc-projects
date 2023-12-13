//
// Created by radud on 06.12.2023.
//

/*
Using (quicksort or mergesort or heapsort), implement the intersection of two multisets.
Each multiset is an array of pairs (element, occurrences), and the result is an array of pairs (element, occurrences),
containing the elements from the intersection. O(n log n + m log m) Hint: modify an interclass. 4a 2b 7c ∩ 2a 4b 3c = 2a 2b 3c -> we take the minimum
*/

#include <iostream>

struct Pair {
    char element;
    int frecv;
};

int alege_poz_pivot(Pair *v, int st, int dr) {
    return (st + dr) / 2;
}

int partition_Lomuto(Pair *v, int st, int dr) {
    int poz_pivot = alege_poz_pivot(v, st, dr);
    std::swap(v[poz_pivot], v[dr]);
    int i = st - 1;
    for (int j = st; j < dr; j++) {
        if (v[j].element < v[dr].element) {
            std::swap(v[++i], v[j]);
        }
    }
    std::swap(v[i + 1], v[dr]);
    return i + 1;
}

void quicksort(Pair *v, int st, int dr) {
    if (st < dr) {
        int poz_pivot = partition_Lomuto(v, st, dr);
        quicksort(v, st, poz_pivot - 1);
        quicksort(v, poz_pivot + 1, dr);
    }
}

void intersectie(Pair *multiset1, int size1, Pair *multiset2, int size2, Pair *rezultat) {
    quicksort(multiset1, 0, size1 - 1);
    quicksort(multiset2, 0, size2 - 1);

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (multiset1[i].element == multiset2[j].element) {
            int min_frecv = std::min(multiset1[i].frecv, multiset2[j].frecv);
            rezultat[k++] = {multiset1[i].element, min_frecv};
            i++;
            j++;
        } else if (multiset1[i].element < multiset2[j].element) {
            i++;
        } else {
            j++;
        }
    }
}

void afisare_pereche(const Pair &pair) {
    std::cout << pair.frecv << pair.element << " ";
}

void afisare_set(Pair *set, int size) {
    for (int i = 0; i < size; ++i) {
        afisare_pereche(set[i]);
    }
    std::cout << std::endl;
}

int main() {
    Pair set1[] = {{'a', 5},
                   {'b', 3},
                   {'c', 3}};
    Pair set2[] = {{'a', 2},
                   {'b', 6},
                   {'c', 2}};

    int size1 = sizeof(set1) / sizeof(Pair);
    int size2 = sizeof(set2) / sizeof(Pair);

    int dim_max = std::min(size1, size2);
    Pair *rezultat = new Pair[dim_max];

    intersectie(set1, size1, set2, size2, rezultat);

    std::cout << "Primul set: " << std::endl;
    afisare_set(set1, size1);
    std::cout << "Al doilea set: " << std::endl;
    afisare_set(set2, size2);
    std::cout << std::endl;

    std::cout << "Intersectie: ";
    for (int i = 0; i < dim_max; ++i) {
        std::cout << rezultat[i].frecv << rezultat[i].element << " ";
    }
    std::cout << std::endl;

    delete[] rezultat;

    return 0;
}
