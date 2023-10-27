#include <iostream>

// Create a doubly linked list (with prev, next pointers) 
// with two insert and extract operations that insert or delete the same key (with changed sign) at both ends each time: 
// insert 1,2,3: ... -3 -2 -1 1 2 3 ...

struct nod_dublu {
    int data;
    nod_dublu* prev;
    nod_dublu* next;
};

struct doubly_linked_list {
    nod_dublu* first_element;
    nod_dublu* last_element;

    doubly_linked_list() {
        first_element = nullptr;
        last_element = nullptr;
    }

    void insert(int x) {
        nod_dublu* nou = new nod_dublu;
        nou->data = x;
        nou->prev = nullptr;
        nou->next = first_element;

        if (first_element != nullptr) {
            first_element->prev = nou;
        } else {
            last_element = nou;
        }

        first_element = nou;

        nod_dublu* nou_invers = new nod_dublu;
        nou_invers->data = -x;
        nou_invers->prev = last_element;
        nou_invers->next = nullptr;

        if (last_element != nullptr) {
            last_element->next = nou_invers;
        } else {
            first_element = nou_invers;
        }

        last_element = nou_invers;
    }

    void extract(int x) {
        nod_dublu* current = first_element;

        while (current != nullptr) {
            if (current->data == x || current->data == -x) {
                if (current->prev != nullptr)
                    current->prev->next = current->next;
                else
                    first_element = current->next;
                if (current->next != nullptr)
                    current->next->prev = current->prev;
                else
                    last_element = current->prev;

                nod_dublu* invers = (current->data == x) ? current->next : current->prev;
                if (invers != nullptr) {
                    if (invers->prev != nullptr) {
                        invers->prev->next = invers->next;
                    } else {
                        first_element = invers->next;
                    }
                    if (invers->next != nullptr) {
                        invers->next->prev = invers->prev;
                    } else {
                        last_element = invers->prev;
                    }
                }

                delete current;
                delete invers;

                return;
            }
            current = current->next;
        }
    }


    void show() const {
        nod_dublu* pointer;
        for (pointer = first_element; pointer != nullptr; pointer = pointer->next)
            std::cout << pointer->data << " ";
        std::cout << std::endl;
    }
};

int main() {
    doubly_linked_list LD;
    LD.insert(1);
    LD.insert(2);
    LD.insert(3);
    LD.show();
    std::cout << "Afterextract:\n";
    LD.extract(1);
    LD.extract(2);
    LD.extract(3);
    LD.show();

    return 0;
}
