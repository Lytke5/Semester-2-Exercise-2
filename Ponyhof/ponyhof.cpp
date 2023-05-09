#include <fstream>
#include <string.h>
#include <stdio.h>
#include "ponyhof.h"
#include "islandpferd.h"
#include "shetlandpony.h"
#define WRITE_BIN true


using namespace std;
Ponyhof::Ponyhof(string file)
{
    bool tryAgain;
    bool itWorked = true;
    bool useBin;


    if(file.compare(file.size()-4, 4, ".bin") == 0 && WRITE_BIN)
        useBin = true;
    else if(file.compare(file.size()-4, 4, ".txt") == 0 && !WRITE_BIN)
        useBin = false;
    else
    {
        cout << "Dateityp passt nicht mit Flag ueberein!"<<endl;
        throw "Fehler";
    }


    if(useBin)
    {
        struct data
        {
            char race[13];
            char name[30];
            int birthYear;
            char isSpecialFeature;
        };
        ifstream input("ponys.bin", ios::binary);
        if (input) {

            int ponyCount;
            input.read(reinterpret_cast<char*>(&ponyCount), sizeof(ponyCount));

            vector<data> readPonys(ponyCount);
            input.read(reinterpret_cast<char*>(&readPonys[0]), ponyCount * sizeof(data));

            for(int i = 0; i < ponyCount; i++)
            {
                if(strcmp(readPonys[i].race,"Shetlandpony"))
                {
                    Shetlandpony* newPony = new Shetlandpony(readPonys[i].birthYear, readPonys[i].name, readPonys[i].isSpecialFeature);
                    stallung.einstellen(newPony);
                }
                else if(strcmp(readPonys[i].race,"Islandpferd"))
                {
                    IslandPferd* newPony = new IslandPferd(readPonys[i].birthYear, readPonys[i].name, readPonys[i].isSpecialFeature);
                    stallung.einstellen(newPony);
                }
            }

            input.close();
        }

    }
    else
    {

        string race;
        string name;
        int birthYear;
        int lineCount = 0;
        bool isSpecialFeature;
        do{
            tryAgain = false;
            string line;
            ifstream myfile(file);
            if (myfile.is_open()) {
                try{
                    while (getline(myfile, line)) {
                        lineCount++;
                        race = line;
                        if(race != "Shetlandpony" && race !="Islandpferd")
                            throw bad_exception();

                        getline(myfile, line);
                        lineCount++;
                        name = line;

                        getline(myfile, line);
                        lineCount++;
                        birthYear = stoi(line);

                        getline(myfile, line);
                        lineCount++;
                        if(line == "y")
                            isSpecialFeature = true;
                        else if(line == "n")
                            isSpecialFeature = false;
                        else
                            throw bad_exception();
                        if(race == "Shetlandpony")
                        {
                            Shetlandpony* newPony = new Shetlandpony(birthYear, name, isSpecialFeature);
                            stallung.einstellen(newPony);
                        }
                        else
                        {
                            IslandPferd* newPony = new IslandPferd(birthYear, name, isSpecialFeature);
                            stallung.einstellen(newPony);
                        }
                    }
                }
                catch(const exception e)
                {
                    itWorked = false;
                    char input;
                    bool wrongInput = true;
                    for(int i = 0; i < 20; i++)
                        delete stallung.herausholen(i);
                    while(wrongInput)
                    {
                        cout << "Fehler beim Einlesen der Datei in Zeile " << lineCount << endl;
                        cout << "Erneut versuchen (v) oder abbrechen (a)?";
                        cin >> input;
                        if(input == 'v')
                        {
                            tryAgain = true;
                            wrongInput = false;
                        }
                        else if (input == 'a')
                            tryAgain = false;
                        wrongInput = false;
                    }


                }

                myfile.close();
            }
        }while (tryAgain);
    }
}
void Ponyhof::userDialog()
{
    int input;
    do{
        do{
            cout << endl;
            cout << "1 Pony einstellen" << endl;
            cout << "2 Pony zum Reiten holen" << endl;
            cout << "3 Ponys kontrollieren" << endl;
            cout << "4 Ponys auf Weide schicken" << endl;
            cout << "0 Programm beenden" << endl;
            cin >> input;
        }while(input < 0 || input > 4);

        switch (input) {
        case 1:
        {
            int race;
            string name;
            int birthYear;
            char yn;
            bool yesNo;
            cout << "Welche Rasse? (1: Shetlandpony, 2: Islandpferd)" << endl;

            cin >> race;
            cout << "Geburtsjahr: ";
            cin >> birthYear;
            cout << "Name: ";
            cin >> name;
            if(race == 1)
            {
                cout << "Kinderlieb (y/n): ";
                cin >> yn;
                if(yn == 'y')
                    yesNo = true;
                else
                    yesNo = false;
                Shetlandpony* newPony = new Shetlandpony(birthYear, name, yesNo);
                bool freeSpace = stallung.einstellen(newPony);
                if(freeSpace)
                    cout << "Das neue Pony ist nun im Stall" << endl;
                else
                {
                    delete newPony;
                    cout << "Kein Platz für das Pony mehr im Stall" << endl;
                }
            }
            else if(race == 2)
            {
                cout << "Ekzemer (y/n): ";
                cin >> yn;
                if(yn == 'y')
                    yesNo = true;
                else
                    yesNo = false;
                IslandPferd* newPony = new IslandPferd(birthYear, name, yesNo);
                bool freeSpace = stallung.einstellen(newPony);
                if(freeSpace)
                    cout << "Das neue Pony ist nun im Stall" << endl;
                else
                {
                    delete newPony;
                    cout << "Kein Platz für das Pony mehr im Stall" << endl;
                }
            }
            break;
        }
        case 2:
        {
            Pony* currPony;
            string name;
            cout << "Welches Pony soll herausgeholt werden: ";
            cin >> name;
            currPony = stallung.herausholen(name);

            if(currPony != NULL)
                beimReiten.push_back(currPony);

            break;
        }
        case 3:
            stallung.zeigeInfo();
            cout << "Aktuell werden " << beimReiten.size() << " Ponys geritten" << endl << endl;
            for(int i = 0; i < weide.size(); i++)
                weide[i]->zeigeInfo();
            cout << "Aktuell sind " << weide.size() << " Ponys auf der Weide" << endl;
            break;

        case 4:
            stallung.weidegang(&weide);
            break;
        }
    }while(input != 0);

    for(int i = 0; i < beimReiten.size(); i++)
    {
        stallung.einstellen(beimReiten[i]);
    }
}

Ponyhof::~Ponyhof()
{

    if(WRITE_BIN)
    {
        struct data
        {
            char race[13];
            char name[30];
            int birthYear;
            char isSpecialFeature;
        };

        ofstream output("ponys.bin", ios::binary);
        if (output) {
            vector<data> ponys;

            for(int i = 0; i < SIZE; i++)
            {
                Pony* currPony = stallung.herausholen(i);
                if(currPony != NULL)
                {
                    string race;
                    char yesNo;
                    data d;
                    strcpy(d.race, currPony->getRace().c_str());
                    strcpy(d.name, currPony->gibName().c_str());
                    d.birthYear = currPony->gibGeburtsjahr();
                    d.isSpecialFeature =  currPony->getSpecialFeature();
                    ponys.push_back(d);
                    delete currPony;
                }
            }
            for(int i = 0; i < weide.size(); i++)
            {
                Pony* currPony = weide[i];
                if(currPony != NULL)
                {
                    string race;
                    char yesNo;
                    data d;
                    strcpy(d.race, currPony->getRace().c_str());
                    strcpy(d.name, currPony->gibName().c_str());
                    d.birthYear = currPony->gibGeburtsjahr();
                    d.isSpecialFeature =  currPony->getSpecialFeature();
                    ponys.push_back(d);
                    delete currPony;
                }
            }


            int num_ponys = ponys.size();
            output.write(reinterpret_cast<const char*>(&num_ponys), sizeof(num_ponys));
            output.write(reinterpret_cast<const char*>(&ponys[0]), num_ponys * sizeof(data));
            output.close();
        }
    }
    else
    {
        ofstream myfile;
        myfile.open("ponys.txt");
        string race;
        char yesNo;
        for(int i = 0; i < SIZE; i++)
        {
            Pony* currPony = stallung.herausholen(i);
            if(currPony != NULL)
            {
                myfile << currPony->getRace() << endl;
                myfile << currPony->gibName() << endl;
                myfile << currPony->gibGeburtsjahr() << endl;
                myfile << currPony->getSpecialFeature() << endl;
                delete currPony;
            }
        }
        for(int i = 0; i < weide.size(); i++)
        {
            Pony* currPony = weide[i];
            if(currPony != NULL)
            {
                myfile << currPony->getRace() << endl;
                myfile << currPony->gibName() << endl;
                myfile << currPony->gibGeburtsjahr() << endl;
                myfile << currPony->getSpecialFeature() << endl;
                delete currPony;
            }
        }
        myfile.close();
    }
}


