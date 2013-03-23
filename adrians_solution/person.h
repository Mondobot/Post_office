#pragma once

#ifndef PERSON_H
#define PERSON_H
#include <iostream>

using namespace std;

class Window;

class Person {

        private:
        public:
                int id;
                int packageWeight;
                Person(int id, int packageWeight) :
                        id(id), packageWeight(packageWeight) {
                }

                int getWeight() {
                        return packageWeight;
                }

                int getId() {
                        return id;
                }

                //friend ostream& operator<<(ostream&, Person&);
                friend class Window;

};

ostream& operator<<(ostream& out, Person p) {
        out << "(" << p.id << ", " << p.packageWeight << ")";
        return out;
}

#endif
