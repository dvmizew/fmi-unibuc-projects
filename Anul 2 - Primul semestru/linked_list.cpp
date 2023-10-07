#include <iostream>

// Create a doubly linked list (with prev, next pointers) 
// with two insert and extract operations that insert or delete the same key (with changed sign) at both ends each time: 
// insert 1,2,3: ... -3 -2 -1 1 2 3 ...

struct nod {
	int data;
	nod* next;
	nod* prev;
};

struct list {
	nod* first_element;
	nod* last_element;
	list() {
		first_element = NULL;
		last_element = NULL;
	}
	void insert_at_beginning(int x) {
		nod* nou = new nod;
		nou->data = x;
		nou->next = first_element;
		nou->prev = NULL;
		if (first_element == NULL) // if the list was empty
			last_element = nou;
		else
			first_element->prev = nou;
		first_element = nou;
	}
	void insert_at_end(int x) {
		nod* nou = new nod;
		nou->data = x;
		nou->next = NULL;
		nou->prev = last_element;
		if (last_element == NULL) // if the list was empty
			first_element = nou;
		else
			last_element->next = nou;
		last_element = nou;
	}

	void afisare() {
		nod* pointer;
		for (pointer = first_element; pointer != NULL; pointer = pointer->next)
			std::cout << pointer->data << ' ';
		std::cout << '\n';
	}

	void insertion_at_the_ends(int* v, int number_of_elements) {
		for (int i = 0; i < number_of_elements; i++) {
			insert_at_beginning(v[i]);
			insert_at_end(-v[i]);
		}
	}
};

int main() {
	list list1;
	int vec[] = { 1, 2, 3 };
	int number_of_elements = sizeof(vec) / sizeof(int);
	list1.insertion_at_the_ends(vec, number_of_elements);
	list1.afisare();
	return 0;
}
