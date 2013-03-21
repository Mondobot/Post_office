#include <iostream>
#include <stdlib.h>

#ifndef __STACK__H
#define __STACK__H

#define FWD 1
#define REV -1

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
	Stack(int max_size): N(max_size), topLevel(-1) {
		stackArray = (T*)malloc((N + 1) * sizeof(T));
	}

	// destructor
	~Stack() {
		free(stackArray);
	}

	// operator de adaugare
	void push(T x) {
		if (isFull())
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

	int isFull() {
		return (topLevel == N - 1);
	}

	// This is a hackty hack
	void printStack(int dir) {
		int first, last;

		if (topLevel == -1)
			return;

		if (dir == FWD) {
			first = 0;
			last = topLevel;

		} else {
			first = topLevel;
			last = 0;
		}

		for (int i = first; i != last; i += dir)
			std::cout << stackArray[i] << ", ";

		if (!isEmpty())
			std::cout << stackArray[last] << std::endl;

		//std::cout << " SIZE: " << topLevel + 1;
	}

	void clear() {
		while (!isEmpty())
			pop();
	}
};
#endif // __STACK__H
