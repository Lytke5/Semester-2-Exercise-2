#include "stall.h"
#include <ctime>
#include <fstream>


using namespace std;

Stall::Stall()
{
    for(int i = 0; i < SIZE; i++)
    {
        pferdeboxen[i] = NULL;
    }
}

int Stall::belegteBoxen()
{
    int count = 0;
    for(int i = 0; i < SIZE; i++)
    {
        if(pferdeboxen[i] != NULL)
            count++;
    }
    return count;
}

bool Stall::einstellen(Pony* newPony)
{
    for(int i = 0; i < SIZE; i++)
    {
        if(pferdeboxen[i] == NULL)
        {
            pferdeboxen[i] = newPony;
            return true;
        }
    }
    return false;
}

Pony* Stall::herausholen(string name)
{
    int age;
    Pony* currPony;
    for(int i = 0; i < SIZE; i++)
    {
        if(pferdeboxen[i]->gibName() == name)
        {
            currPony = pferdeboxen[i];
            pferdeboxen[i] = NULL;
            cout << "Alter des Reiters: ";
            cin >> age;
            if(currPony->istReitbar(age))
            {
                cout << "Pony wird geritten" << endl;
                return currPony;
            }
            else
            {
                cout << "Der Reiter enspricht nicht dem erforderlichen Alter" << endl;
                for(int i = 0; i < SIZE; i++)
                {
                    if(pferdeboxen[i] == NULL)
                    {
                        pferdeboxen[i] = currPony;
                        break;
                    }
                }
                return NULL;
            }
        }
    }
    cout << "Falscher Name" << endl;
    return NULL;
}
Pony* Stall::herausholen(int index)
{
    if(pferdeboxen[index] != NULL)
        return pferdeboxen[index];

    return NULL;
}

float Stall::durchschnittsalter()
{
    float count = 0;
    float ageTotal = 0;
    for(int i = 0; i < SIZE; i++)
    {
        if(pferdeboxen[i] != NULL)
        {
            count++;
            ageTotal+= berechneJahr() - pferdeboxen[i]->gibGeburtsjahr();
        }
    }

    return ageTotal/count;
}

int Stall::berechneJahr()
{
    time_t seconds = time(NULL);
    int years = (((seconds/60)/60)/24)/365.25;
    return 1970 + years;
}

void Stall::weidegang(vector<Pony*> *weide)
{
    float x,y;
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++)
    {
        if(pferdeboxen[i] != NULL)
        {
            x = (rand() % 30) + 30;
            y = rand() % 40;
            Position* pos = new Position(x,y);
            pferdeboxen[i]->setzePos(*pos);
            weide->push_back(pferdeboxen[i]);
            pferdeboxen[i] = NULL;
        }
    }
}

void Stall::zeigeInfo()
{
    cout << "Aktuell sind " << belegteBoxen() << " Boxen belegt" << endl;
    if(belegteBoxen() > 0)
        cout << "Das Durchschnittsalter der Ponys in den Boxen betraegt: " << durchschnittsalter() << " Jahre" << endl;
    cout << endl;

    for(int i = 0; i < SIZE; i++)
    {
        if(pferdeboxen[i] != NULL)
            pferdeboxen[i]->zeigeInfo();
    }
}
