#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include "person.h"
#include "queue.h"
#include "stack.h"

using namespace std;

class WindowStack {
        private:
        public:
                int maxWeight;
                int maxSize;
                Stack<int> *stack;
                int currWeight;
                WindowStack(int q, int k) :
                        maxSize(q), maxWeight(k), currWeight(0) {

                        stack = new Stack<int>;
                }

                ~WindowStack() {
                        delete stack;
                }

                void push(int x) {
                        if(stack->size() >= maxSize ||
                           currWeight + x > maxWeight)
                                emptyStack();

                        stack->push(x);
                        currWeight += x;
                }

                void pop() {
                        stack->pop();
                }

                void emptyStack() {
                        delete stack;
                        stack = new Stack<int>;
                        currWeight = 0;
                }


        //        friend ostream& operator<<(ostream&, WindowStack&);
};

ostream& operator<<(ostream& out, WindowStack& ws) {
        out << *(ws.stack);
        return out;
}

class Window {
        private:
        public:
                Queue<Person> *queue;
                WindowStack *windowStack;
                int minWeight;
                int maxWeight;
                Window(int minW, int maxW, int q, int k) :
                        minWeight(minW), maxWeight(maxW) {

                        queue = new Queue<Person>;
                        windowStack = new WindowStack(q, k);
                }

                ~Window() {
                        delete queue;
                        delete windowStack;
                }

                void add(Person x) {
                        queue->enque(x);
                }

                void remove() {
                        queue->deque();
                }

                Person first() {
                        return queue->front();
                }

                void process() {
                        windowStack->push(first().getWeight());
                        remove();
                }

                WindowStack& getStack() {
                        return *windowStack;
                }

                Queue<Person>& getQueue() {
                        return *queue;
                }

                void emptyStack() {
                        windowStack->emptyStack();
                }

                bool acceptPackage() {
                        return (first().packageWeight >= minWeight &&
                                first().packageWeight <= maxWeight);
                }

                int length() {
                        return queue->queue->size;
                }
};
#endif
