#pragma once

#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template<class T>
class ListNode {
        public:
                ListNode(T x, ListNode<T>* next) : data(x), next(next) {}
                ListNode(T x) : data(x), next(0) {}

                void setNext(ListNode<T>* next) {
                        this->next = next;
                }

                T getData() {
                        return data;
                }


                ListNode<T>* next;
        protected:
                T data;
};

template<class T>
class List {
        public:
                List() : size(0), head(0), tail(0) {}

                ~List() {
                        while(!empty())
                                removeFirst();
                }

                void addFirst(T x) {
                        if(empty()) {
                                addLast(x);
                                return;
                        }

                        head = new ListNode<T>(x, head);
                        size++;
                }

                void addLast(T x) {
                        if(empty()) {
                                tail = new ListNode<T>(x, 0);
                                head = tail;
                                tail->next = 0;
                                size++;
                                return;
                        }

                        tail->setNext(new ListNode<T>(x, 0));
                        tail = tail->next;
                        size++;
                }

                ListNode<T> getFirst() {
                        return *head;
                }

                ListNode<T> getLast() {
                        return *tail;
                }

                void removeFirst() {
                        if(empty())
                                return;

                        ListNode<T>* aux = head;
                        head = head->next;
                        delete aux;
                        size--;
                        if(size <= 1)
                                tail = head;
                }

                void removeLast() {
                        if(empty())
                                return;

                        if(size == 1) {
                                removeFirst();
                                size--;
                                return;
                        }

                        ListNode<T>* aux = head;
                        while(aux->next != tail) {
                                aux = aux->next;
                        }
                        delete aux->next;
                        aux->next = 0;
                        size--;
                }

                int getSize() {
                        return size;
                }

                bool empty() {
                        return (size == 0);
                }

        //        friend ostream& operator<<(ostream&, List<T>);

                ListNode<T>* head;
                ListNode<T>* tail;
                int size;
        private:
};

template<class T>
ostream& operator<<(ostream& out, List<T>& l) {
        if(l.head == 0)
                return out;

        ListNode<T>* aux = l.head;

        out << aux->getData();
        while(aux->next != 0) {
                aux = aux->next;
                out << ", ";
                out << aux->getData();
        }

        return out;
}
#endif
