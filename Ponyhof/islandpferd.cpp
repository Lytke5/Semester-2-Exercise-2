#include "islandpferd.h"

IslandPferd::IslandPferd(int y, string n, bool e)
{
    geburtsJahr = y;
    name = n;
    ekzemer = e;
}

const bool IslandPferd::getSpecialFeature()
{
    return ekzemer;
}

const string IslandPferd::getRace()
{
    return "Islandpferd";
}

const bool IslandPferd::istReitbar(int age)
{
    if(age >= 10)
        return true;
    else
        return false;
}

const void IslandPferd::zeigeInfo()
{
    cout << "Rasse: Islandpferd" << endl;
    cout << "Name: " << name << endl;
    cout << "Geburtsjahr: " << geburtsJahr << endl;
    cout << "Ekzemer: ";
    if(ekzemer)
        cout << "Ja" << endl << endl;
    else
        cout << "Nein" << endl << endl;
}
