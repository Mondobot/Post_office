
#include<iostream>
#include<fstream>
#include<vector>

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>

// CONSTANTE - !!! De testat cu diverse valori !!!
#define MAX_N 34515
#define AVR_WEIGHT 50000
#define LARGE 960997823
#define N_PACK 1300

using namespace std;

const char commands[][13] = {"OPEN_WINDOW",
                            "ADD_PERSON",
                            "PROCESS",
                            "PROCESS_ALL",
                            "PRINT_STACKS",
                            "FLUSH_STACKS",
                            "PRINT_QUEUES"};

// functie auxiliara pt verificari (daca value apare in vector)
template <class T>
bool occurrence(T value, vector<T>& v)
{
    for(int i = 0; i < v.size(); ++i) {
        if(v[i] == value)
            return true;
    }
    return false;
}

// genereaza o greutate a packetului intre min si max
int genPackageWeight(vector<int>& min, vector<int>& max)
{
    int j = 0;
    for(int i = 0; i < min.size(); ++i) {
        if(max[i] == 0)
            continue;
        j++;
    }

    int r = rand() % j;
    for(int i = 0; i < min.size(); ++i) {
        if(max[i] == 0)
            continue;
        if(r <= 0)
            return (rand() % (max[i] - min[i])) + min[i];

        r--;
    }

    return -1;
}


/*
 * ./main <test> <nWindows>
 * Primul parametru: numele fisierului de test (e.g. testXX.in)
 * Al 2lea parametru: cate ghisee sa avem
 *
 * */
int main(int argc, char** argv)
{

    srand(time(0));

    argc--;
    argv++;
    fstream out(argv[0], fstream::out);

    int nWindows;//= rand() % MAX_N;

    sscanf(argv[1], "%d", &nWindows);

    out << nWindows << endl;

    const int N_WINDOWS = nWindows;

    int globalMinWeight = rand() % 10;
    int globalMaxWeight = rand() % AVR_WEIGHT + AVR_WEIGHT;

    float averageWeightInterval = ((float)(globalMaxWeight - globalMinWeight) /
                                    (float) nWindows);

    int k, q;
    int w, id;

    const int nCommands = 7;

    const int MAX_N_PEOPLE = 1000000; // !!! De testat pe mai multe valori !!!
    int nPeople = rand() % MAX_N_PEOPLE; // alegem un nr de persoane

    /*
     * Vectori auxiliari
     */
    vector<bool> openWindow(N_WINDOWS, false);
    vector<bool> people(nPeople);

    vector<int> minWeights(N_WINDOWS, 0);
    vector<int> maxWeights(N_WINDOWS, 0);
    vector<int> queueSize(N_WINDOWS, 0);


    int weightInterval, minWeight, maxWeight, avrageWeight;
    int command;


    while(true) {
        vector<int> params(5);
        command = rand() % nCommands;
        if(!occurrence(false, openWindow))
            break;

        switch(command) {
        case 0: // OPEN_WINDOW
            // daca nu exista nicio fereastra inchisa, adica toate sunt deschise
            if(!occurrence<bool>(false,openWindow))
                break;

            for(w = rand() % N_WINDOWS; openWindow[w]; w = rand() % N_WINDOWS);
            // w este id-ul unei ferestre deschise, aleasa aleator
            params[0] = w;
            openWindow[w] = true;

            // generam aleator minimul de greutate acceptat de giseu si
            // lungimea intervalului (min, max)
            weightInterval = (int)(((float)(800 + rand() % 400) / 1000.0f) *
                                    averageWeightInterval);
            minWeight = (globalMinWeight +
                            rand() % (globalMaxWeight - weightInterval));

            maxWeight = minWeight + weightInterval;
            avrageWeight = (maxWeight + minWeight) / 2;

            params[1] = minWeight;
            minWeights[w] = minWeight;
            params[2] = maxWeight;
            maxWeights[w] = maxWeight;
            // params[3] = Q (nr max de elem din stiva)
            params[3] = (rand() % 2 + 1) + rand() % N_PACK;
            // params[4] = K (greutatea maxima admisa de stiva)
            params[4] = ((float)(rand() % 200 + 900) / 1000.0f) *
                            (params[3] * avrageWeight);


            // AFISAREA
            out << commands[command] << " "
                << params[0] << " "
                << params[1] << " "
                << params[2] << " "
                << params[3] << " "
                << params[4] << endl;
            break;
        case 1: // ADD_PERSON
            // Daca am "ramas fara" oameni
            if(!occurrence<bool>(false, people))
                break;

            // Daca nu exista niciun ghiseu deschis
            if(!occurrence<bool>(true, openWindow))
                break;

            for(id = rand() % nPeople; people[id]; id = rand() % nPeople);
            // id este un id _nou_ al persoanei introduse
            params[0] = id;
            people[id] = true;

            for(w = rand() % N_WINDOWS; !openWindow[w]; w = rand() % N_WINDOWS);
            //la ce ghiseu sa-l punem
            params[2] = w;

            // alegem daca sa fie acceptat de ghiseul la care l-am pus sau nu
            if(rand() % 2) {
                params[1] = (rand() % (maxWeights[w] - minWeights[w] + 1)) +
                            minWeights[w] - 1;
            }
            else {
                params[1] = genPackageWeight(minWeights, maxWeights);
            }

            queueSize[w]++;
            out << commands[command] << " "
                << params[0] << " "
                << params[1] << " "
                << params[2] << endl;
            break;
        case 2: // PROCESS
            // verificam sa existe ghisee deschise (pt cazul in care nu avem
            // inca niciun ghiseu deschis)
            if(!occurrence<bool>(true, openWindow))
                break;

            for(w = rand() % N_WINDOWS; !openWindow[w]; w = rand() % N_WINDOWS);

            params[0] = w;
            if(queueSize[w] == 0)
                break;

            params[1] = (rand() % (queueSize[w]) + 1);

            queueSize[w] -= params[1];

            out << commands[command] << " "
                << params[0] << " "
                << params[1] << endl;
            break;
        case 3: // PROCESS_ALL - similar cu PROCESS
            if(!occurrence<bool>(true, openWindow))
                break;

            for(w = rand() % N_WINDOWS; !openWindow[w]; w = rand() % N_WINDOWS);

            params[0] = w;
            queueSize[w] = 0;

            out << commands[command] << " "
                << params[0] << endl;
            break;
        default: // PRINT_STACKS/QUEUES, FLUSH - doar afisam coamnda
            if(!occurrence<bool>(true, openWindow))
                break;

            out << commands[command] << endl;
            break;
        }

    }

    return 0;
}
