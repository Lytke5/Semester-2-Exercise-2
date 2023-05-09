#ifndef PONYHOF_H
#define PONYHOF_H
#include "stall.h"
#include "pony.h"
#include <vector>


class Ponyhof
{
private:
    Stall stallung;
    std::vector<Pony*> beimReiten;
    std::vector<Pony*> weide;
public:
    Ponyhof(string file);
    void userDialog();
    ~Ponyhof();

};

#endif // PONYHOF_H
