#ifndef SHETLANDPONY_H
#define SHETLANDPONY_H
#include "pony.h"


class Shetlandpony : public Pony
{
private:
    bool kinderlieb;
public:
    Shetlandpony(int y, string n, bool k);
    const bool getSpecialFeature() override;
    const string getRace() override;
    const bool istReitbar(int) override;
    const void zeigeInfo() override;
};

#endif // SHETLANDPONY_H
