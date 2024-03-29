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

int choose_pivot_pos(Pair *v, int left, int right) {
    return (left + right) / 2;
}

int partition_Lomuto(Pair *v, int left, int right) {
    int pivot_pos = choose_pivot_pos(v, left, right);
    std::swap(v[pivot_pos], v[right]);
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (v[j].element < v[right].element) {
            std::swap(v[++i], v[j]);
        }
    }
    std::swap(v[i + 1], v[right]);
    return i + 1;
}

void quicksort(Pair *v, int left, int right) {
    if (left < right) {
        int poz_pivot = partition_Lomuto(v, left, right);
        quicksort(v, left, poz_pivot - 1);
        quicksort(v, poz_pivot + 1, right);
    }
}

void intersectie(Pair *multiset1, int size1, Pair *multiset2, int size2, Pair *result) {
    quicksort(multiset1, 0, size1 - 1);
    quicksort(multiset2, 0, size2 - 1);

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (multiset1[i].element == multiset2[j].element) {
            int min_frecv = std::min(multiset1[i].frecv, multiset2[j].frecv);
            result[k++] = {multiset1[i].element, min_frecv};
            i++;
            j++;
        } else if (multiset1[i].element < multiset2[j].element) {
            i++;
        } else {
            j++;
        }
    }
}

void print_pair(const Pair &pair) {
    std::cout << pair.frecv << pair.element << " ";
}

void print_set(Pair *set, int size) {
    for (int i = 0; i < size; ++i) {
        print_pair(set[i]);
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
    Pair *result = new Pair[dim_max];

    intersectie(set1, size1, set2, size2, result);

    std::cout << "First set: " << std::endl;
    print_set(set1, size1);
    std::cout << "Second set: " << std::endl;
    print_set(set2, size2);
    std::cout << std::endl;

    std::cout << "Intersection: ";
    for (int i = 0; i < dim_max; ++i) {
        std::cout << result[i].frecv << result[i].element << " ";
    }
    std::cout << std::endl;

    delete[] result;

    return 0;
}
