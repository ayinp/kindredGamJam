#ifndef WORLD_H
#define WORLD_H
#include "graphics.h"
#include "card.h"

class World
{
public:
    Vec2d groundPos;
    int population = 50;
    int environment = 50;
    int food = 50;
    int water = 50;
public:
    World();
    void draw(mssm::Graphics& g);
    void handleCard(CardType type);
};

#endif // WORLD_H
