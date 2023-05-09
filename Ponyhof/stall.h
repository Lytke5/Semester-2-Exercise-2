#ifndef STALL_H
#define STALL_H
#include "pony.h"
#include <vector>
#define SIZE 20


class Stall
{
private:
    Pony* pferdeboxen[SIZE];
public:
    Stall();
    int belegteBoxen();
    bool einstellen(Pony*);
    Pony* herausholen(std::string);
    Pony* herausholen(int);
    float durchschnittsalter();
    int berechneJahr();
    void weidegang(vector<Pony*> *weide);
    void zeigeInfo();
};

#endif // STALL_H
