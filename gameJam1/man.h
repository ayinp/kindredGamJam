#ifndef MAN_H
#define MAN_H
#include "graphics.h"


class Man
{
public:
    mssm::Color color;
    Vec2d velocity;
    int numMan;
    Vec2d platformPos;
    Vec2d platformWH;
    Vec2d location;
    int width = 30;
    int height = 50;
public:
    Man();
    Man(mssm::Graphics& g, mssm::Color color, Vec2d velocity, Vec2d platformPos, Vec2d platformWH);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics& g);
};

#endif // MAN_H
