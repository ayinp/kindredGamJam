#include <iostream>
#include "world.h"
#include "button.h"
#include "sprites.h"
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
    g.rect(groundPos, groundWH.x, groundWH.y, GREEN, GREEN);

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

    // sprites
    for(int j = 0; j < men.size(); j++)
    {
        men[j].drawAndUpdate(g);
    }
    for(int j = 0; j < trees.size(); j++)
    {
        trees[j].drawAndUpdate(g);
    }
    for(int j = 0; j < animals.size(); j++)
    {
        animals[j].drawAndUpdate(g);
    }
    for(int j = 0; j < flowers.size(); j++)
    {
        flowers[j].drawAndUpdate(g);
    }

}

void World::handleCard(Graphics& g, CardType type, int round)
{
    switch(type)
    {
    case CardType::Tree:
        doTree(g);
        break;
    case CardType::Person:
        doPerson(g);
        break;
    case CardType::Lightning:
        doLightning(g);
        break;
    case CardType::Wind:
        doWind(g);
        break;
    case CardType::Animal:
        doAnimal(g, round);
        break;
    case CardType::Drought:
        doDrought(g);
        break;
    case CardType::Garden:
        doGarden(g, round);
        break;
    case CardType::Plague:
        doPlague(g);
        break;
    case CardType::Reproduction:
        doReproduction(g, round);
        break;
    case CardType::Rain:
        doRain(g);
        break;
    case CardType::Feast:
        doFeast(g);
        break;
    case CardType::Sacrifice:
        doSacrifice(g, round);
        break;
    }
}

void World::doAnimal(Graphics& g, int round)
{
        food += 5;
        environment -= 5;
        // ^^increases every 5 rounds, makes animal every +10 food, do wind every -10 environment
}

void World::doGarden(Graphics& g, int round)
{
        environment += 5;
        water -= 5;
        // ^^increases every 5 rounds, do tree every +10 environment,
        flowers.push_back(Sprite(g, Type::Flower, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
}

void World::doReproduction(Graphics& g, int round)
{
        population += 5;
        food -= 5;
        // ^^increases every 5 rounds, do man every +10 population,
}

void World::doSacrifice(Graphics& g, int round)
{
        water += 5;
        population -= 5;
        // ^^increase every 5 rounds, do rain every +10 water,
}

void World::doLightning(Graphics& g)
{
    food -= 10;
    animals.erase(animals.begin());
//    events.push_back(Event));
}

void World::doTree(Graphics& g)
{
    environment += 10;
    trees.push_back(Sprite(g, Type::Tree, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
}

void World::doPerson(Graphics& g)
{
    population += 10;
    men.push_back(Sprite(g, Type::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
}

void World::doFeast(Graphics& g)
{
    food += 10;
    animals.push_back(Sprite(g, Type::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
}

void World::doRain(Graphics& g)
{
    water += 10;
}

void World::doPlague(Graphics& g)
{
    population -= 10;
    men.erase(men.begin());
}

void World::doDrought(Graphics& g)
{
    water -= 10;
}

void World::doWind(Graphics& g)
{
    environment -= 10;
    trees.erase(trees.begin());
}

