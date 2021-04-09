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
    static Image men("men.png");
    int imageWidth = 12;
    int imageHeight = 12;
    int cw = 12;
    int rw = 12;
    frame++;
    if(frame%5 == 0)
    {
    frameRight += 2*cw;
    frameLeft += 2*cw;
    }
    if(frameRight >= 6*cw)
    {
        frameRight = 0;
    }
    if(frameLeft > 6*cw)
    {
        frameLeft = 12;
    }
    if(frame > 50)
    {
        frame = 0;
    }

        switch(x)
        {
        case 0:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x <= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        case 1:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x <= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        case 2:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x <= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        case 3:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x <= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        case 4:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x <= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        case 5:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x < 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        case 6:
            if(velocity.x >= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameRight, x*rw, imageWidth, imageHeight);
            }
            else if(velocity.x <= 0)
            {
                g.image({location.x, location.y - 5}, manWidth, manHeight, men, frameLeft, x*rw, imageWidth, imageHeight);
            }
            break;
        }
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
        doneFalling = true;
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
    static Image sheep ("sheep.png");
    if(velocity.x >= 0)
    {
        g.image({location.x, location.y - 5}, animalWidth, animalHeight, sheep, 0, 0, 12, 12);
    }
    else if(velocity.x <= 0)
    {
        g.image({location.x, location.y - 5}, animalWidth, animalHeight, sheep, 12, 0, 12, 12);
    }
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
        doneFalling = true;
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
    static Image tree("treeSprite.png");
    g.image(location, treeWidth, treeHeight, tree);
}

void Sprite::updateTrees(Graphics &g)
{
    location = location + velocity;

    if(location.y < platformPos.y + platformWH.y)
    {
        velocity = {0, 0};
        location.y = platformPos.y + platformWH.y;
        doneFalling = true;
    }
}

void Sprite::drawFlowers(Graphics &g)
{
    static Image flower("flower.png");
    g.image(location, flowerWidth, flowerHeight, flower);
}

void Sprite::updateFlowers(Graphics &g)
{
    location = location + velocity;

    if(location.y < platformPos.y + platformWH.y)
    {
        velocity = {0, 0};
        location.y = platformPos.y + platformWH.y;
        doneFalling = true;
    }
}

