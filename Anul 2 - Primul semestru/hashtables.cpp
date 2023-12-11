//
// Created by radud on 11.12.2023.
//

/*
 * Using a hash table for the larger multiset, implement the intersection of two multisets.
 * The other multiset is an array of pairs (element, occurrences), and the result is an array of pairs (element, occurrences)
 * containing the elements from the intersection. Complexity is O(n + m + collisions). For instance, given 4a 2b 7c ∩ 2a 4b 3c = 2a 2b 3c,
 * taking the minimum count of occurrences for each element in the intersection.
 */

#include <iostream>
#include <cmath>

struct intrare {
    long long CNP;
    int numar;
    int frecventa;
};

struct nod {
    intrare info;
    nod *next;
};

struct lista {
    nod *primul_element;

    lista() {
        primul_element = nullptr;
    }

    void insert_la_inceput(long long cheie, int valoare) {
        nod *nou = new nod;
        nou->info.CNP = cheie;
        nou->info.numar = valoare;
        nou->next = primul_element;
        primul_element = nou;
    }

    intrare *cauta_dupa_cheie(long long cheie) {
        nod *curent = primul_element;
        while (curent != nullptr && curent->info.CNP != cheie)
            curent = curent->next;
        if (curent == nullptr)
            return nullptr;
        return &(curent->info);
    }

    void afisare() {
        nod *pointer;
        if (primul_element == nullptr)
            std::cout << "prim=NULL";
        else
            for (pointer = primul_element; pointer != nullptr; pointer = pointer->next)
                std::cout << "[" << (char) pointer->info.CNP << ", " << pointer->info.numar << "] -> ";
        std::cout << std::endl;
    }
};

int hash_diviziune(long long cheie, int N) {
    return cheie % 19;
}

const double PHI = 1.6180339887498948482045868343656;

int hash_multiplicare(long long cheie, int N) {
    double integer_part;
    return (int) (N * modf(PHI * cheie, &integer_part));
}

struct hashtable_chaining {
    lista *T;
    int n;

    int (*hashfunc)(long long, int);

    hashtable_chaining(int N, int (*H)(long long, int)) {
        n = N;
        hashfunc = H;
        T = new lista[n];
    }

    void put(long long cheie, int valoare) {
        int hash = hashfunc(cheie, n);
        int index = hash % n;
        intrare *gasit = T[index].cauta_dupa_cheie(cheie);
        if (gasit == nullptr)
            T[index].insert_la_inceput(cheie, valoare);
        else
            gasit->numar = valoare;
    }

    int get(long long cheie) {
        int hash = hashfunc(cheie, n);
        int index = hash % n;
        intrare *gasit = T[index].cauta_dupa_cheie(cheie);
        if (gasit == nullptr)
            return -1;
        else
            return gasit->numar;
    }

    void afisare() {
        for (int i = 0; i < n; i++)
            T[i].afisare();
    }
};

//void intersectieMultiset(hashtable_chaining &h1, hashtable_chaining &h2, hashtable_chaining &rezultat) {
//    for (int i = 0; i < h1.n; i++) {
//        for (int j = 0; j < h2.n; j++) {
//            nod *pointer;
//            for (pointer = h1.T[i].primul_element; pointer != nullptr; pointer = pointer->next) {
//                intrare *gasit = h2.T[j].cauta_dupa_cheie(pointer->info.CNP);
//                if (gasit != nullptr) {
//                    int min = pointer->info.numar < gasit->numar ? pointer->info.numar : gasit->numar;
//                    std::cout << min << (char) pointer->info.CNP << ' ';
//                    rezultat.put(pointer->info.CNP, min);
//                }
//            }
//        }
//    }
//}

void intersectieMultiset(hashtable_chaining &h1, hashtable_chaining &h2, hashtable_chaining &rezultat) {
    for (int i = 0; i < h1.n; i++) {
        for (int j = 0; j < h2.n; j++) {
            nod *pointer;
            for (pointer = h1.T[i].primul_element; pointer != nullptr; pointer = pointer->next) {
                intrare *gasit = h2.T[j].cauta_dupa_cheie(pointer->info.CNP);
                if (gasit != nullptr) {
                    int min = std::min(pointer->info.numar, gasit->numar);
                    min = std::min(min, gasit->frecventa); // Considering frecventa
                    std::cout << min << (char) pointer->info.CNP << ' ';
                    rezultat.put(pointer->info.CNP, min);
                }
            }
        }
    }
}


int main() {
    // 4a 2b 7c  ∩   2a 4b 3c = 2a 2b 3c
    hashtable_chaining h1(19, hash_diviziune);
    h1.put('a', 4);
    h1.put('b', 2);
    h1.put('c', 7);

    hashtable_chaining h2(19, hash_diviziune);
    h2.put('a', 2);
    h2.put('b', 4);
    h2.put('c', 3);

    hashtable_chaining rezultat(19, hash_diviziune);
    intersectieMultiset(h1, h2, rezultat);
    return 0;
}