#ifndef MAN_H
#define MAN_H
#include "graphics.h"

enum class SpriteType
{
    Man,
    Tree,
    Animal,
    Flower
};


class Sprite
{
public:
    SpriteType type;
    mssm::Color color;
    int numSprites;
    Vec2d platformPos;
    Vec2d platformWH;
    Vec2d location;
    Vec2d velocity;
    int manWidth = 60;
    int manHeight = 60;
    int animalWidth = 60;
    int animalHeight = 60;
    int treeWidth = 80;
    int treeHeight = 120;
    int flowerWidth = 10;
    int flowerHeight = 20;
    int x = rand()%7;
    int frameRight = 0;
    int frameLeft = 12;
    int frame = 0;
public:
    Sprite();
    Sprite(mssm::Graphics& g, SpriteType type, mssm::Color color, Vec2d platformPos, Vec2d platformWH, Vec2d location, Vec2d velocity = {0, -10});
    void drawAndUpdate(mssm::Graphics& g);
    void drawMan(mssm::Graphics& g);
    void updateMan(mssm::Graphics& g);
    void drawAnimals(mssm::Graphics& g);
    void updateAnimals(mssm::Graphics& g);
    void drawTrees(mssm::Graphics& g);
    void updateTrees(mssm::Graphics& g);
    void drawFlowers(mssm::Graphics& g);
    void updateFlowers(mssm::Graphics& g);
};

#endif // MAN_H
