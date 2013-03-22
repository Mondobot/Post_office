#include <iostream>

#include "stack.h"
#include "queue.h"

#ifndef __BOOTH__H
#define __BOOTH__H

typedef struct Guy {
	int id;
	int package_weight;

	Guy(int id, int package_weight): id(id), package_weight(package_weight) {}

	friend std::ostream& operator<<(std::ostream& out, Guy& x) {
		out << "(" << x.id << ", " << x.package_weight << ")";
		return out;
	}

} guy;

class Booth {
private:
	int id;
	int stack_size;
	int p_w_min, p_w_max, current_w, w_max_on_stack;
	Stack<int> *ok_packages;
	Queue<Guy> *funny_ppl;

public:
	Booth(int id, int w_min, int w_max, int q, int k):
			id(id), stack_size(q), p_w_min(w_min),
			p_w_max(w_max), current_w(0), w_max_on_stack(k) {

		ok_packages = new Stack<int>(q);
		funny_ppl = new Queue<Guy>(2);
	}

	~Booth() {
		delete(ok_packages);
		delete(funny_ppl);
	}

	void addGuy(int id, int package_weight) {
		funny_ppl->enqueue(new Guy(id, package_weight));
	}

	Guy* process() {
		Guy *lucky_one = funny_ppl->dequeue();

		if (lucky_one == NULL)
			return NULL;

		if (lucky_one->package_weight >= p_w_min &&
			lucky_one->package_weight <= p_w_max) {
			if (ok_packages->isFull() ||
				current_w + lucky_one->package_weight > w_max_on_stack) {

				ok_packages->clear();
				current_w = 0;
			}

			//std::cout << "Adaug " << lucky_one << "\n";
			ok_packages->push(lucky_one->package_weight);
			current_w += lucky_one->package_weight;

			return NULL;
		}

		return lucky_one;
	}

	void flush() {
		std::cout << id << ": ";

		ok_packages->printStack(REV);
		std::cout << std::endl;
		ok_packages->clear();
		current_w = 0;
		
	}

	void printStack() {
		std::cout << id << ": ";
		ok_packages->printStack(REV);

		std::cout << std::endl;
	}

	void printQueue() {
		std::cout << id << ": ";
		funny_ppl->printQueue();
		std::cout << std::endl;
	}

	int getQueueSize() {
		return funny_ppl->getSize();
	}
};
#endif
