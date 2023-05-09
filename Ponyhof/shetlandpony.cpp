#include "shetlandpony.h"

Shetlandpony::Shetlandpony(int y, string n, bool k)
{
    geburtsJahr = y;
    name = n;
    kinderlieb = k;
}

const bool Shetlandpony::getSpecialFeature()
{
    return kinderlieb;
}

const string Shetlandpony::getRace()
{
    return "Shetlandpony";
}

const bool Shetlandpony::istReitbar(int age)
{
    if(age > 4 && age < 13)
    {
        if(age <= 8)
        {
            if(kinderlieb)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

const void Shetlandpony::zeigeInfo()
{
    cout << "Rasse: Shetlandpony" << endl;
    cout << "Name: " << name << endl;
    cout << "Geburtsjahr: " << geburtsJahr << endl;
    cout << "Kinderlieb: ";
    if(kinderlieb)
        cout << "Ja" << endl << endl;
    else
        cout << "Nein" << endl << endl;
}
