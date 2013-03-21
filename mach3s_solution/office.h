#include <stdlib.h>
#include <iostream>

#include "booth.h"

#ifndef __OFFICE__H
#define __OFFICE__H

class Office {
	int no_booths;
	Booth **booths_list;

	Office(int no_booths): no_booths(no_booths) {
		booths_list = new Booth*[no_booths];

		for (int i = 0; i < no_booths; ++i)
			booths_list[i] = NULL;
	}

	~Office() {
		delete booths_list;
	}

	void AddBooth(int id, int w_min, int w_max, int q, int k) {
		if (id > no_booths || id < 0 || booths_list[id] != NULL)
			return;

		booths_list[id] = new Booth(id, w_min, w_max, q, k);
	}

	void addGuy(int id, int package_weight, int booth_id) {
		if (booths_list[booth_id] == NULL)
			return;

		booths_list[booth_id]->addGuy(id, package_weight);
	}

	void process(int id, int no) {
	}

	void printStacks() {
		std::cout << "<STACKS>\n";

		for (int i = 0; i < no_booths; ++i)
			if (booths_list[i] != NULL)
				booths_list[i]->printStack();
	}

	void printQueues() {
		std::cout << "<QUEUES>\n";

		for (int i = 0; i < no_booths; ++i)
			if (booths_list[i] != NULL)
				booths_list[i]->printQueue();
	}
	
	void flush() {
		std::cout << "<FLUSHED>\n";

		for (int i = 0; i < no_booths; ++i)
			if (booths_list[i] != NULL)
				booths_list[i]->flush();
	}
};

