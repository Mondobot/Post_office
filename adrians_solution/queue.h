#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template<class T>
class Queue {
        private:
        public:
                List<T> *queue;

                Queue() {
                        queue = new List<T>;
                }

                ~Queue() {
                        delete queue;
                }

                void enque(T x) {
                        queue->addLast(x);
                }

                T front() {
                        return queue->getFirst().getData();
                }

                void deque() {
                        queue->removeFirst();
                }

                bool empty() {
                        return queue->empty();
                }

                int size() {
                        queue->getSize();
                }

                //friend ostream& operator<<<T>(ostream&, Queue<T>&);
};

template<class T>
ostream& operator<<(ostream& out, Queue<T>& q) {
        out << *(q.queue);
        return out;
}

#endif // QUEUE_H
