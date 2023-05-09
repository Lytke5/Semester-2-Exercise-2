#include <fstream>
#include <typeinfo>
#include "pony.h"


Pony::Pony()
{
    ort = Position(0,0);
}
Pony::Pony(float x_, float y_)
{
    ort = Position(x_, y_);
}

const string Pony::gibName()
{
    return name;
}

const int Pony::gibGeburtsjahr()
{
    return geburtsJahr;
}

const bool Pony::getSpecialFeature()
{
}

const string Pony::getRace()
{
}

void Pony::setzePos(const Position &newPosition)
{
    ort = newPosition;
}

const bool Pony::istReitbar(int age)
{
}

const void Pony::zeigeInfo()
{

}

Pony::~Pony(){
}


