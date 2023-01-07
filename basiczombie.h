#ifndef BASICZOMBIE_H
#define BASICZOMBIE_H

#include "zombie.h"
#include "drops.h"

class BasicZombie : public Zombie
{
public:
    BasicZombie(std::vector<std::pair<int, int>> r, int su, int f);
    void advance(int phase) override;

};

#endif // BASICZOMBIE_H
