#ifndef WORLD_H
#define WORLD_H
#include "graphics.h"
#include "card.h"
#include "sprites.h"
#include "animation.h"
#include "continuous.h"

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
    std::vector<Continuous*> continuous;
    std::vector<Continuous*> activeContin;
    Vec2d foodLoc;
    Vec2d popLoc;
    Vec2d enviLoc;
    Vec2d waterLoc;
    int x = 0;
    Vec2d cloud1Pos;
    Vec2d cloud2Pos;
    Vec2d cloud3Pos;
public:
    World(mssm::Graphics &g);
    void draw(mssm::Graphics& g, int round);
    void handleCard(mssm::Graphics& g, CardType type, int round);
    void startScreen(mssm::Graphics& g);
    void doAnimal(mssm::Graphics& g);
    void doGarden(mssm::Graphics& g);
    void doReproduction(mssm::Graphics& g);
    void doSacrifice(mssm::Graphics& g);
    void doLightning(mssm::Graphics& g, int num);
    void doTree(mssm::Graphics& g, int num);
    void doPerson(mssm::Graphics& g, int num);
    void doFeast(mssm::Graphics& g, int num);
    void doRain(mssm::Graphics& g, int num);
    void doPlague(mssm::Graphics& g, int num);
    void doDrought(mssm::Graphics& g, int num);
    void doWind(mssm::Graphics& g, int num);
    void removePlant(mssm::Graphics& g);
    void dropAnimalOrMan(mssm::Graphics& g, SpriteType type);
    void dropPlant(mssm::Graphics& g);
    void removeAnimalOrMan(mssm::Graphics& g, SpriteType type);
    void justRain(mssm::Graphics& g);
    void newRound(mssm::Graphics& g, int round);
    void addPlus5(int location);
    void addMinus5(int location);
    mssm::Color barColor(int whichStat);
    bool activeAnimations();
    bool hasActiveContin()
    {
        return activeContin.size() != 0;
    };
};

#endif // WORLD_H
