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
    int numMen = 10;
    int numTrees = 10;
    int numAnimals = 10;
    int waterLevel = 10;
    int population = numMen*5;
    int environment = numTrees*5;
    int food = numAnimals*5;
    int water = waterLevel*5;
    std::vector<Sprite> men;
    std::vector<Sprite> animals;
    std::vector<Sprite> flowers;
    std::vector<Sprite> trees;
    std::vector<Animation*> animations;
    int x = 0;
public:
    World();
    void draw(mssm::Graphics& g);
    void handleCard(mssm::Graphics& g, CardType type, int round);
    void startScreen(mssm::Graphics& g);
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
