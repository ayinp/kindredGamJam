#ifndef WORLD_H
#define WORLD_H
#include "graphics.h"
#include "card.h"
#include "sprites.h"
#include "animation.h"

class World
{
public:
    Vec2d groundPos;
    Vec2d groundWH;
    int population = 50;
    int environment = 50;
    int food = 50;
    int water = 50;
    int numMen = floor(population/10);
    int numTrees = floor(environment/10);
    int numAnimals = floor(food/10);
    int waterLevel = floor(water/10);
    std::vector<Sprite> men;
    std::vector<Sprite> animals;
    std::vector<Sprite> flowers;
    std::vector<Sprite> trees;
    std::vector<Animation*> animations;
public:
    World();
    void draw(mssm::Graphics& g);
    void handleCard(mssm::Graphics& g, CardType type, int round);
    void doAnimal(mssm::Graphics& g, int round);
    void doGarden(mssm::Graphics& g, int round);
    void doReproduction(mssm::Graphics& g, int round);
    void doSacrifice(mssm::Graphics& g, int round);
    void doLightning(mssm::Graphics& g);
    void doTree(mssm::Graphics& g);
    void doPerson(mssm::Graphics& g);
    void doFeast(mssm::Graphics& g);
    void doRain(mssm::Graphics& g);
    void doPlague(mssm::Graphics& g);
    void doDrought(mssm::Graphics& g);
    void doWind(mssm::Graphics& g);
};

#endif // WORLD_H
