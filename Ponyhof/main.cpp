#include <iostream>
#include <fstream>
#include "ponyhof.h"

using namespace std;

unsigned ponyHufe(unsigned numPonys)
{
    if(numPonys == 1)
        return 4;
    else
        return 4 + ponyHufe(--numPonys);
}

int main(int argc, char*argv[])
{


    //string s = "ponys.bin";
    //char* argv = &s[0];
    string file = argv[1];

    Ponyhof* myPonyhof = new Ponyhof(file);
    ponyHufe(10);

    myPonyhof->userDialog();
    delete myPonyhof;
    return 0;
}
