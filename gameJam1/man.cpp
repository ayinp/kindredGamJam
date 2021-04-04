#include "man.h"
#include <cstdlib>
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;

Man::Man()
{

}

Man::Man(Graphics& g, Color color, Vec2d velocity, Vec2d platformPos, Vec2d platformWH)
{
    this->color = color;
    this->velocity = velocity;
    this->platformPos = platformPos;
    this->platformWH = platformWH;
    this->location = location = {rand()%(g.width() - width), g.height()};
}

void Man::draw(Graphics& g)
{
        g.rect(location, width, height, color, color);
}

void Man::update(Graphics& g)
{
    location = location + velocity;

    if(location.y < platformPos.y + platformWH.y)
    {
        velocity = {rand()%20 - 10, 0};
        location.y = platformPos.y + platformWH.y;
    }
    if(location.x <= 0)
    {
        velocity.x = velocity.x*-1;
        location.x = 0;
    }
    else if (location.x >= g.width() - width)
    {
        velocity.x = velocity.x*-1;
        location.x = g.width() - width;
    }

}
