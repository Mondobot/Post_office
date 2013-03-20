#include <iostream.h>

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
	Stack(int max_size): topLevel(-1), N(max_size) {
		stackArray = malloc((N + 1) * sizeof(T));
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

		if (dir == FWD) {
			first = 0;
			last = topLevel;

		} else {
			first = topLevel;
			last = 1;
		}

		for (i = first; i < last; i += dir)
			std::cout << stackArray[i] << ", ";

		if (!isEmpty())
			std::cout << stackArray[last + dir] << std::endl;
	}

	void clear() {
		while (!isEmpty())
			pop();
	}
};
#endif // __STACK__H
