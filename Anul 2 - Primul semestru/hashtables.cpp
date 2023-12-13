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
    long long info;
    int frequency;
};

struct nod {
    intrare info;
    nod *next;
};

struct lista {
    nod *first_element;

    lista() {
        first_element = nullptr;
    }

    void insert_at_beginning(long long key, int value) {
        nod *nou = new nod;
        nou->info.info = key;
        nou->info.frequency = value;
        nou->next = first_element;
        first_element = nou;
    }

    intrare *search_after_key(long long key) {
        nod *current = first_element;
        while (current != nullptr && current->info.info != key)
            current = current->next;
        if (current == nullptr)
            return nullptr;
        return &(current->info);
    }

    void print() {
        nod *pointer;
        if (first_element == nullptr)
            std::cout << "prim=NULL";
        else
            for (pointer = first_element; pointer != nullptr; pointer = pointer->next)
                std::cout << "[" << (char) pointer->info.info << ", " << pointer->info.frequency << "] -> ";
        std::cout << std::endl;
    }
};

int hash_division(long long key, int N) {
    return key % 19;
}

const double PHI = 1.6180339887498948482045868343656;

int hash_multiply(long long key, int N) {
    double integer_part;
    return (int) (N * modf(PHI * key, &integer_part));
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

    void put(long long key, int value) {
        int hash = hashfunc(key, n);
        int index = hash % n;
        intrare *found = T[index].search_after_key(key);
        if (found == nullptr)
            T[index].insert_at_beginning(key, value);
        else
            found->frequency = value;
    }

    int get(long long key) {
        int hash = hashfunc(key, n);
        int index = hash % n;
        intrare *found = T[index].search_after_key(key);
        if (found == nullptr)
            return -1;
        else
            return found->frequency;
    }

    void print() {
        for (int i = 0; i < n; i++)
            T[i].print();
    }
};

void intersectionMultiset(hashtable_chaining &h1, hashtable_chaining &h2, hashtable_chaining &rezultat) {
    for (int i = 0; i < h1.n; ++i) {
        nod *pointer = h1.T[i].first_element;
        while (pointer != nullptr) {
            int key = pointer->info.info;
            int h2_value = h2.get(key);
            if (h2_value != -1) {
                int min_val = std::min(pointer->info.frequency, h2_value);
                rezultat.put(key, min_val);
                std::cout << min_val << (char) key << ' ';
            }
            pointer = pointer->next;
        }
    }
}

int main() {
    // 4a 2b 7c  ∩   2a 4b 3c = 2a 2b 3c
    hashtable_chaining h1(19, hash_division);
    h1.put('a', 4);
    h1.put('b', 2);
    h1.put('c', 7);

    hashtable_chaining h2(19, hash_division);
    h2.put('a', 2);
    h2.put('b', 4);
    h2.put('c', 3);

    hashtable_chaining result(19, hash_division);
    intersectionMultiset(h1, h2, result);
    //result.print();
    return 0;
}