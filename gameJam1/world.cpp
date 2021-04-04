#include "world.h"
#include "button.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

World::World()
{

}

void World::draw(mssm::Graphics &g)
{
    // ground
    g.rect(groundPos, g.width(), 50, GREEN, GREEN);

    // stats
    int statSize = 30;
    int topMar = 30;
    Button pop{"population: " + to_string(population), statSize};
    pop.location= {(g.width()-(pop.width/2))/5,g.height() - topMar};
    pop.draw(g);
    Button disFood{"food: " + to_string(food), statSize};
    disFood.location = {((g.width()-(disFood.width/2))/5)*2,g.height() - topMar};
    disFood.draw(g);
    Button disWater{"water: " + to_string(water), statSize};
    disWater.location = {((g.width()-(disWater.width/2))/5)*3,g.height() - topMar};
    disWater.draw(g);
    Button envi{"environment: " + to_string(environment), statSize};
    envi.location = {((g.width()-(envi.width/2))/5)*4,g.height() - topMar};
    envi.draw(g);

}

void World::handleCard(CardType type)
{
    switch(type)
    {
    case CardType::Tree:
        break;
    case CardType::Person:
        break;
    case CardType::Lightning:
        break;
    case CardType::Wind:
        break;
    case CardType::Animal:
        break;
    case CardType::Drought:
        break;
    case CardType::Garden:
        break;
    case CardType::Plague:
        break;
    case CardType::Reproduction:
        break;
    case CardType::Rain:
        break;
    case CardType::Harvest:
        break;
    case CardType::Sacrifice:
        break;
    }
}

