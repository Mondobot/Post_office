#pragma once

#ifndef STACK_H
#define STACK_H

#include "list.h"

template<class T>
class Stack {
        private:
        public:
                List<T> *stack;
                Stack() {
                        stack = new List<T>;
                }

                ~Stack() {
                        delete stack;
                }

                void push(T x) {
                        stack->addFirst(x);
                }

                T top() {
                        if(!empty())
                                return stack->getFirst().getData();
                        T x(0, 0);
                        return x;
                }

                void pop() {
                        if(!empty())
                                stack->removeFirst();
                }

                bool empty() {
                        return stack->empty();
                }

                int size() {
                        stack->getSize();
                }

        //        friend ofstream& operator<<(ostream&, Stack<T>&);

};

template<class T>
ostream& operator<<(ostream& out, Stack<T>& stack)
{
        out << *(stack.stack);
        return out;
}
#endif
