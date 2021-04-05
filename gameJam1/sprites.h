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
    int manWidth = 30;
    int manHeight = 50;
    int animalWidth = 50;
    int animalHeight = 30;
    int treeWidth = 40;
    int treeHeight = 60;
    int flowerWidth = 10;
    int flowerHeight = 20;
public:
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
