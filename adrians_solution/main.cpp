#include <iostream>
#include <fstream>
#include "manager.h"


int main(int argc, char** argv)
{

        argc--;
        argv++;

        int n;


        Manager manager(argv[0]);
        manager.run();

        return 0;
}

