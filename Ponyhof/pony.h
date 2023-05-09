#ifndef PONY_H
#define PONY_H
#include <iostream>
#include <fstream>
#include "position.h"

using namespace std;

class Pony
{
protected:
    int geburtsJahr;
    string name;
    Position ort;
public:
    Pony();
    Pony(float x_, float y_);
    const string gibName();
    const int gibGeburtsjahr();
    const virtual string getRace();
    const virtual bool getSpecialFeature();
    void setzePos(const Position&);
    const virtual bool istReitbar(int);
    const virtual void zeigeInfo();
    ~Pony();
};

#endif // PONY_H
