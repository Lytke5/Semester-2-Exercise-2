#ifndef ISLANDPFERD_H
#define ISLANDPFERD_H
#include "pony.h"


class IslandPferd : public Pony
{
private:
    bool ekzemer;
public:
    IslandPferd(int y, string n, bool e);
    const bool getSpecialFeature() override;
    const string getRace() override;
    const bool istReitbar(int) override;
    const void zeigeInfo() override;
};

#endif // ISLANDPFERD_H
