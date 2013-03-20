#include <iostream.h>

#ifndef __STACK__H
#define __STACK__H

// Primul argument al template-ului este tipul de date T
// Al doilea argument este dimensiunea maxim a stivei N
template<typename T>
class Stack {
private:
	// vectorul de stocare
	T *stackArray;
	int N;

	// pozitia in vector a varfului stivei
	int topLevel;
public:
	// constructor
	Stack(int max_size): topLevel(-1), N(max_size) {
		stackArray = malloc((N + 1) * sizeof(T));
	}

	// destructor
	~Stack() {
		free(stackArray);
	}

	// operator de adaugare
	void push(T x) {
		if (topLevel == N - 1)
			return;

		stackArray[++topLevel] = x;
	}

	// operatorul de stergere
	T* pop() {
		if (isEmpty())
			return NULL;

		return &stackArray[topLevel--];
	}

	// operatorul de consultare
	T peek() {
		if (isEmpty())
			return NULL;

		return &stackArray[topLevel];
	}

	// operatorul de verificare dimensiune
	int isEmpty() {
		return (topLevel == -1);
	}

	void printStack() {
		for (i = 0; i < topLevel; ++i)
			std::cout << stackArray[i] << ", ";

		if (!isEmpty())
			std::cout << stackArray[topLevel];
	}
};
#endif // __STACK__H
