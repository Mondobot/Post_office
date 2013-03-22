#include <stdlib.h>
#include <iostream>

#ifndef __QUEUE__H
#define __QUEUE__H

template <typename T>
class Queue {
private:
	int head;
	int tail;
	int size;
	int N;
	T **queueArray;

public:
	// Constructor
	Queue(int max_size): head(-1), tail(-1), size(0), N(max_size) {
		queueArray = (T**)malloc((N + 1) * sizeof(T*));
	}

	// Destructor
	~Queue() {
		free(queueArray);
	}

	// Adauga la coada
	void enqueue(T *e) {
		if (size == N) {
			int i = -1;
			T **aux = (T**)malloc(2 * N * sizeof(T*));

			while (!isEmpty())
				aux[++i] = dequeue();

			N *= 2;
			head = 0;
			tail = i;
			size = i + 1;
			free(queueArray);
			queueArray = aux;
		}

		if (head == -1)
			head = 0;

		queueArray[++tail % N] = e;
		++size;
	}

	// Extrage din coada
	T* dequeue() {
		//std::cout << "FAC DQ!\n";
		if (isEmpty())
			return NULL;

		T* ret_val = queueArray[head];
		head = (head + 1) % N;
		--size;
		//std::cout << "NEW_HEAD " << head << "  <__> SIZE " << size << "\n";

		return ret_val;
	}

	// Afla primul element
	T* front() {
		if (isEmpty())
			return NULL;

		return queueArray[head];
	}

	bool isEmpty() {
		return (size == 0);
	}

	void printQueue() {
		//std::cout << "~TAIL = " << tail << "~ ";
		//std::cout << head << " " << tail << " " << size << "\n";
		for (int i = 0; i < size - 1; ++i)
			//std::cout << 
			std::cout << *(queueArray[(head + i) % N]) << ", ";

		if (!isEmpty())
			std::cout << *(queueArray[(head + size - 1) % N]);
	}

	int getSize() {
		return size;
	}
};
#endif
