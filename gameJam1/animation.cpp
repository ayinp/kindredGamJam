#include "animation.h"
#include <vector>
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

RainAnim::RainAnim(Graphics& g)
{
    for(int i = 0; i < 500; i++)
    {
        positions.push_back(Vec2d{rand()%g.width(), g.height() + g.randomDouble(0, g.height())});
        velocity.push_back(Vec2d{0, -1*(10 +rand()%5)});
    }
}

void RainAnim::draw(Graphics &g)
{
    for(int i = 0; i < positions.size(); i++)
    {
        g.rect(positions[i], 1, rand()%3+1, BLUE, BLUE);
    }
}

void RainAnim::update(Graphics &g)
{
    for(int i = 0; i < positions.size(); i++)
    {
        positions[i] = positions[i] + velocity[i];
    }
}
