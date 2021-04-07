#include "sprites.h"
#include <cstdlib>
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;

Sprite::Sprite()
{

}

Sprite::Sprite(Graphics& g, SpriteType type, Color color, Vec2d platformPos, Vec2d platformWH, Vec2d location, Vec2d velocity)
{
    this->type = type;
    this->color = color;
    this->velocity = velocity;
    this->platformPos = platformPos;
    this->platformWH = platformWH;
    this->location = location;
}

void Sprite::drawAndUpdate(Graphics &g)
{
    switch(type)
    {
    case SpriteType::Man:
        drawMan(g);
        updateMan(g);
        break;
    case SpriteType::Animal:
        drawAnimals(g);
        updateAnimals(g);
        break;
    case SpriteType::Tree:
        drawTrees(g);
        updateTrees(g);
        break;
    case SpriteType::Flower:
        drawFlowers(g);
        updateFlowers(g);
        break;
    }
}

void Sprite::drawMan(Graphics& g)
{
        g.rect(location, manWidth, manHeight, color, color);
}

void Sprite::updateMan(Graphics& g)
{
    location = location + velocity;
    int x = rand()%2;
    if(location.y < platformPos.y + platformWH.y)
    {
        if(x == 1)
        {
        velocity = {rand()%8+2, 0};
        }
        else if(x == 0)
        {
            velocity = {rand()%8-10, 0};
        }
        location.y = platformPos.y + platformWH.y;
    }
    if(location.x <= 0)
    {
        velocity.x = velocity.x*-1;
        location.x = 0;
    }
    else if (location.x >= g.width() - manWidth)
    {
        velocity.x = velocity.x*-1;
        location.x = g.width() - manWidth;
    }

}

void Sprite::drawAnimals(Graphics &g)
{
    g.rect(location, animalWidth, animalHeight, color, color);
}

void Sprite::updateAnimals(Graphics &g)
{
    location = location + velocity;
    int x = rand()%2;
    if(location.y < platformPos.y + platformWH.y)
    {
        if(x == 0)
        {
        velocity = {rand()%2-5, 0};
        }
        else if(x == 1)
        {
            velocity = {rand()%2+3, 0};
        }
        location.y = platformPos.y + platformWH.y;
    }
    if(location.x <= 0)
    {
        velocity.x = velocity.x*-1;
        location.x = 0;
    }
    else if (location.x >= g.width() - animalWidth)
    {
        velocity.x = velocity.x*-1;
        location.x = g.width() - animalWidth;
    }

}

void Sprite::drawTrees(Graphics &g)
{
    g.rect(location, treeWidth, treeHeight, color, color);
}

void Sprite::updateTrees(Graphics &g)
{
    location = location + velocity;

    if(location.y < platformPos.y + platformWH.y)
    {
        velocity = {0, 0};
        location.y = platformPos.y + platformWH.y;
    }
}

void Sprite::drawFlowers(Graphics &g)
{
    g.rect(location, flowerWidth, flowerHeight, color, color);
}

void Sprite::updateFlowers(Graphics &g)
{
    location = location + velocity;

    if(location.y < platformPos.y + platformWH.y)
    {
        velocity = {0, 0};
        location.y = platformPos.y + platformWH.y;
    }
}

