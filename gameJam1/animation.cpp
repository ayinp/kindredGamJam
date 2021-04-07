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
    if(facingLeft)
    {
    g.rect(animalPos, 50, 30, YELLOW, YELLOW);
    }
    else
    {
        g.rect(animalPos, 50, 30, BLUE, BLUE);
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
    double tornadoWidth = 50;
    g.rect(tornadoPos, tornadoWidth, 50, GREY, GREY);
}

void WindAnim::update(Graphics &g)
{
    tornadoPos += {animFrame*5.0, 0};
    if(tornadoPos.x >= treePos.x)
    {
        g.rect(treePos, 60, 40, GREEN, GREEN);
    }
    else
    {
        g.rect(treePos, 40, 60, GREEN, GREEN);
    }
    animFrame++;
}

ManDeathAnim::ManDeathAnim(Vec2d manPos)
{
    this->manPos = manPos;
}

void ManDeathAnim::draw(Graphics &g)
{
    animFrame++;
    if(animFrame < animLength/4)
    {
        g.rect(manPos, 30, 50, RED, RED);
    }
    else
    {
        g.rect(manPos, 50, 30, RED, RED);
    }

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
    g.rect(groundPos, groundWH.x, groundWH.y, {139,69,19}, {139,69,19});
}

void FeastAnim::draw(Graphics &g)
{
    int width = 300;
    g.rect({(g.width()-width)/2, (g.height()/4)*3}, width, 200, WHITE, WHITE);
    animFrame++;
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

killAnimalAnim::killAnimalAnim(Vec2d animalPos)
{
    this->animalPos = animalPos;
}

void killAnimalAnim::draw(Graphics &g)
{
    animFrame++;
    g.rect(animalPos, 50, 30, PURPLE, PURPLE);
}
