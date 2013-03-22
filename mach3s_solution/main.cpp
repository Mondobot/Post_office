#include <fstream>
#include <string.h>

#include "office.h"

#define NEW_WINDOW "OPEN_WINDOW"
#define NEW_GUY "ADD_PERSON"
#define PROCESS "PROCESS"
#define PROCESS_ALL "PROCESS_ALL"
#define STACKS "PRINT_STACKS"
#define FLUSH "FLUSH_STACKS"
#define QUEUES "PRINT_QUEUES"

void read_params(std::ifstream& fin, int params[6],int no)
{
	for (int i = 0; i < no; ++i)
		fin >> params[i];
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		exit(2);

	std::ifstream fin;
	fin.open(argv[1]);

	int N;
	fin >> N;

	Office *center = new Office(N);
	char command[20];
	int params[6];

	fin >> command;

	while(!fin.eof()) {
		if (strcmp(command, NEW_WINDOW) == 0) {
			read_params(fin, params, 5);

			center->AddBooth(params[0], params[1], params[2],
						params[3], params[4]);

		} else if (strcmp(command, NEW_GUY) == 0) {
		 	read_params(fin, params, 3);

			center->addGuy(params[0], params[1], params[2]);

		} else if (strcmp(command, PROCESS) == 0) {
			read_params(fin, params, 2);

			center->process(params[0], params[1]);

		} else if (strcmp(command, PROCESS_ALL) == 0) {
			read_params(fin, params, 1);
			center->processAll(params[0]);

		} else if (strcmp(command, STACKS) == 0) {
			center->printStacks();

		} else if (strcmp(command, FLUSH) == 0) {
			center->flush();

		} else if (strcmp(command, QUEUES) == 0) {
			center->printQueues();

		} else {
			std::cout << "COMMAND NOT FOUND -> " << command << std::endl;
			exit(1);
		}

		fin >> command;
	}

	return 0;
}
