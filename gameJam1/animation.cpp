#include "animation.h"
#include <vector>
#include "sprites.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::draw(mssm::Graphics &g)
{

}

void Animation::update(Graphics &g)
{

}


LightningAnim::LightningAnim(Vec2d animalPos, bool facingLeft)
{
    this->animalPos = animalPos;
    this->facingLeft = facingLeft;
}

void LightningAnim::draw(mssm::Graphics &g)
{
    Image sheep("sheep.png");
    if(facingLeft)
    {
        if (animFrame < animLength/2)
        {
            g.image({animalPos.x, animalPos.y - 5}, 60, 60, sheep, 12, 12, 12, 12);
        }
        else if (animFrame >= animLength/2)
        {
            g.image({animalPos.x, animalPos.y - 10}, 60, 60, sheep, 0, 24, 12, 12);
        }
    }
    else
    {
        if (animFrame < animLength/2)
        {
            g.image({animalPos.x, animalPos.y - 5}, 60, 60, sheep, 24, 12, 12, 12);
        }
        else if(animFrame >= animLength/2)
        {
            g.image({animalPos.x, animalPos.y - 10}, 60, 60, sheep, 12, 24, 12, 12);
        }
    }
    animFrame++;
}

WindAnim::WindAnim(Vec2d treePos, Vec2d tornadoPos)
{
    this->treePos = treePos;
    this->tornadoPos = tornadoPos = {20, treePos.y};
}

void WindAnim::draw(Graphics &g)
{
    g.rect(tornadoPos, 40, 50, GREY, GREY);
}

void WindAnim::update(Graphics &g)
{
    static Image tree("treeSprite.png");
    static Image fallenTree("fallenTreeSprite.png");
    tornadoPos += {animFrame*5.0, 0};
    if(tornadoPos.x >= treePos.x)
    {
        g.image(treePos, 120, 80, fallenTree);
    }
    else
    {
        g.image(treePos, 80, 120, tree);
    }
    animFrame++;
}

ManDeathAnim::ManDeathAnim(Vec2d manPos, bool facingLeft, int whichMan)
{
    this->manPos = manPos;
    this->facingLeft = facingLeft;
    this->whichMan = whichMan;
}

void ManDeathAnim::draw(Graphics &g)
{
    Image deadMen("deadmen.png");
    if(facingLeft)
    {
        switch(whichMan)
        {
        case 0:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 0, 0, 12, 12);
            break;
        case 1:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 24, 0, 12, 12);
            break;
        case 2:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 0, 12, 12, 12);
            break;
        case 3:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 24, 12, 12, 12);
            break;
        case 4:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 0, 24, 12, 12);
            break;
        case 5:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 24, 24, 12, 12);
            break;
        case 6:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 0, 36, 12, 12);
            break;
        }
    }
    else
    {
        switch(whichMan)
        {
        case 0:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 12, 0, 12, 12);
            break;
        case 1:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 36, 0, 12, 12);
            break;
        case 2:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 12, 12, 12, 12);
            break;
        case 3:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 36, 12, 12, 12);
            break;
        case 4:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 12, 24, 12, 12);
            break;
        case 5:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 36, 24, 12, 12);
            break;
        case 6:
            g.image({manPos.x, manPos.y - 5}, 60, 60, deadMen, 12, 36, 12, 12);
            break;
        }
    }
    animFrame++;
}

RainAnim::RainAnim(Graphics& g, Vec2d groundPos, Vec2d groundWH)
{
    this->groundPos = groundPos;
    this->groundWH = groundWH;
    for(int i = 0; i < 1000; i++)
    {
        positions.push_back(Vec2d{rand()%g.width(), g.height() + g.randomDouble(0, 2*g.height())});
        velocity.push_back(Vec2d{0, -1*(10 +rand()%5)});
    }
}

void RainAnim::draw(Graphics &g)
{
    animFrame++;
    for(int i = 0; i < positions.size(); i++)
    {
        g.rect(positions[i], 1, rand()%5+1, BLUE, BLUE);
    }
}

void RainAnim::update(Graphics &g)
{
    for(int i = 0; i < positions.size(); i++)
    {
        positions[i] = positions[i] + velocity[i];
        if(positions[i].y <= groundPos.y + groundWH.y)
        {
            positions.erase(positions.begin()+i);
        }
    }
}

DroughtAnim::DroughtAnim(Vec2d groundPos, Vec2d groundWH)
{
    this->groundPos = groundPos;
    this->groundWH = groundWH;
}

void DroughtAnim::draw(Graphics &g)
{
    animFrame++;
    Image dryGround("dryGround.png");
    g.image(groundPos.x, groundPos.y + 5, groundWH.x, groundWH.y, dryGround);
    // needs art
}

void FeastAnim::draw(Graphics &g)
{
    int width = 300;
    g.rect({(g.width()-width)/2, (g.height()/4)*3}, width, 200, WHITE, WHITE);
    animFrame++;
    // needs art - "note" from god
}

Start::Start(std::vector<Sprite>& men, std::vector<Sprite>& animals, std::vector<Sprite>& trees, int numMen, int numAnimals, int numTrees, Vec2d groundPos, Vec2d groundWH)
{
    this->men = men;
    this->animals = animals;
    this->trees = trees;
    this->numMen = numMen;
    this->numAnimals = numAnimals;
    this->numTrees = numTrees;
    this->groundPos = groundPos;
    this->groundWH = groundWH;
}

void Start::draw(Graphics &g)
{
    for(int i = 0; i < numMen; i++)
    {
        men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
    for(int i = 0; i < numAnimals; i++)
    {
        animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
    for(int i = 0; i < numTrees; i++)
    {
        trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    }
}

killAnimalAnim::killAnimalAnim(Vec2d animalPos, bool facingLeft)
{
    this->animalPos = animalPos;
    this->facingLeft = facingLeft;
}

void killAnimalAnim::draw(Graphics &g)
{
    Image sheep ("sheep.png");
    animFrame++;
    if(facingLeft)
    {
        g.image(animalPos, 60, 60, sheep, 0, 12, 12, 12);
    }
    else
    {
        g.image(animalPos, 60, 60, sheep, 24, 0, 12, 12);
    }
}

Numbers::Numbers(Vec2d statLoc, int numType)
{
    this->numType = numType;
    this->statLoc = statLoc;
    switch(numType)
    {
    case 5: number.load("plusFive.png"); break;
    case -5: number.load("minusFive.png"); break;
    case 10: number.load("plusTen.png"); break;
    case -10: number.load("minusTen.png"); break;
    }
    location = {statLoc.x, statLoc.y - 30};
}

void Numbers::draw(Graphics &g)
{
    g.image(location, 50, 50, number);
    animFrame++;
}
