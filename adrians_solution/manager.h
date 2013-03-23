#pragma once

#ifndef MANAGER_H
#define MANAGER_H

#include<iostream>
#include<fstream>

#include<cstring>

#include "person.h"
#include "queue.h"
#include "window.h"
#include "list.h"

using namespace std;

class Manager {
        private:

                Window** windows;
                fstream in;
                int nWindows;

                int getId(char command[]) {
                        const char commands[][13] = {"OPEN_WINDOW",
                                        "ADD_PERSON",
                                        "PROCESS",
                                        "PROCESS_ALL",
                                        "PRINT_STACKS",
                                        "FLUSH_STACKS",
                                        "PRINT_QUEUES"};

                        for(int i = 0; i < 7; ++i) {
                                if(strcmp(command, commands[i]) == 0)
                                        return i;
                        }
                        return -1;
                }
        public:
                /*
                 * Constructor. Aloca spatiu necesar pentru vectorii de ghisee
                 */
                Manager(char *fname) {
                        in.open(fname);
                        in >> nWindows;

                        windows = new Window*[nWindows];

                        for(int i = 0; i < nWindows; ++i)
                                windows[i] = 0;
                }

                void run() {
                        char command[10];
                        int params[6];

                        in >> command;
                        while(!in.eof()) {

                                int commandId = readParams(command, params);
                                switch(commandId) {
                                        case 0: windows[params[0]] =
                                                new Window(params[1],
                                                                params[2],
                                                                params[3],
                                                                params[4]);
                                                break;
                                        case 1: windows[params[2]]->add(
                                                Person(params[0], params[1]));
                                                break;
                                        case 2: processN(params[0], params[1]);
                                                break;
                                        case 3: processAll(params[0]);
                                                break;
                                        case 4: cout << "STACKS:" << endl;
                                                printStacks();
                                                break;
                                        case 5: cout << "FLUSHING:" << endl;
                                                flushStacks();
                                                break;
                                        case 6: cout << "QUEUES:" << endl;
                                                printQueues();
                                                break;
                                }
                                in >> command;
                        }
                }

                void process(int i) {
                        if(windows[i]->acceptPackage()) {
                                windows[i]->process();
                        }
                        else {
                                windows[nextOpened(i)]->add(windows[i]->first());
                                windows[i]->remove();
                        }



                }

                void processN(int i, int n) {
                        //if(n > windows[i]->length())
                          //  n = windows[i]->length();
                        while(n--)
                                process(i);
                }

                void processAll(int i) {
                        processN(i, windows[i]->length());
                }

                void printStacks() {
                        for(int i = 0; i < nWindows; ++i)
                                if(windows[i] != 0) {
                                        cout << i << ": " <<
                                        windows[i]->getStack() << endl;
                                }
                }

                void printQueues() {
                        for(int i = 0; i < nWindows; ++i)
                                if(windows[i] != 0) {
                                        cout << i << ": " <<
                                        windows[i]->getQueue();
                                        cout << endl;
                                }
                }

                void flushStacks() {
                        printStacks();
                        for(int i = 0; i < nWindows; ++i) {
                                if(windows[i] != 0)
                                        windows[i]->emptyStack();
                        }
                }

                int nextOpened(int current) {
                        for(int i = (current + 1) % nWindows;
                                        i < nWindows; i = (i + 1) % nWindows) {

                                if(windows[i] != 0)
                                        return i;
                        }
                }

                int readParams(char* command, int* params) {
                        int nParam = 0;
                        int commandId = getId(command);
                        switch(commandId) {
                                case 0: nParam = 5; break;
                                case 1: nParam = 3; break;
                                case 2: nParam = 2; break;
                                case 3: nParam = 1; break;
                                default: nParam = 0;
                        }
                        for(int i = 0; i < nParam; ++i)
                                in >> params[i];

                        return commandId;
                }

                ~Manager() {
                        delete windows;
                }


};
#endif
