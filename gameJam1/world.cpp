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
    x++;
    if(x < 2)
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

    // water tower
    g.rect({g.width() - 100, groundPos.y + groundWH.y}, 75, 100, GREY, GREY);
    for (int i = 0; i <= water; i += 5)
    {
        g.rect({g.width() - 75, groundPos.y + groundWH.y}, 25, i, BLUE, BLUE);
    }

    // sprites
    for(int j = 0; j < trees.size(); j++)
    {
        trees[j].drawAndUpdate(g);
    }
    for(int j = 0; j < animals.size(); j++)
    {
        animals[j].drawAndUpdate(g);
    }
    for(int j = 0; j < men.size(); j++)
    {
        men[j].drawAndUpdate(g);
    }
    for(int j = 0; j < flowers.size(); j++)
    {
        flowers[j].drawAndUpdate(g);
    }
    for(int j = 0; j < animations.size(); j++)
    {
        animations[j]->draw(g);
        animations[j]->update(g);
        if(animations[j]->finished())
        {
            delete animations[j];
            animations.erase(animations.begin()+j);
            j--;
        }
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

void World::startScreen(Graphics &g)
{
    animations.push_back(new Start(men, animals, trees, numMen, numAnimals, numTrees, groundPos, groundWH));
}

// NOTE: remember:
// all of the things on screen should be directly proportional to the stats . . .


void World::doAnimal(Graphics& g, int round)
{
    food += 5;
    environment -= 5;
    animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    // ^^do every 5 rounds,
    if(flowers.size() > 0)
    {
        flowers.erase(flowers.begin());
    }
    else if(flowers.size() <= 0 && trees.size() > 0)
    {
        trees.erase(trees.begin());
    }
}

void World::doGarden(Graphics& g, int round)
{
    environment += 5;
    water -= 5;
    flowers.push_back(Sprite(g, SpriteType::Flower, PURPLE, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    // ^^do every 5 rounds
}

void World::doReproduction(Graphics& g, int round)
{
    population += 5;
    food -= 5;
    men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    if(animals.size() > 0)
    {
        animations.push_back(new killAnimalAnim{animals[0].location});
        animals.erase(animals.begin());
    }
    // ^^do every 5 rounds,
}

void World::doSacrifice(Graphics& g, int round)
{
    water += 5;
    population -= 5;
    animations.push_back(new RainAnim(g, groundPos, groundWH));
    if(men.size() > 0)
    {
        animations.push_back(new ManDeathAnim(men[0].location));
        men.erase(men.begin());
    }
    // ^^do every 5 rounds,
}

void World::doLightning(Graphics& g)
{
    bool facingLeft;
    food -= 10;
    if(animals.size() > 0)
    {
        if(animals[0].velocity.x > 0)
        {
            facingLeft = false;
        }
        else
        {
            facingLeft = true;
        }
        animations.push_back(new LightningAnim{animals[0].location, facingLeft});
        animals.erase(animals.begin());

        if(animals[0].velocity.x > 0)
        {
            facingLeft = false;
        }
        else
        {
            facingLeft = true;
        }
        animations.push_back(new LightningAnim{animals[0].location, facingLeft});
        animals.erase(animals.begin());
    }
}

void World::doTree(Graphics& g)
{
    environment += 10;
    trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
}

void World::doPerson(Graphics& g)
{
    population += 10;
    men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
}

void World::doFeast(Graphics& g)
{
    food += 10;
    animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    animations.push_back(new FeastAnim());
}

void World::doRain(Graphics& g)
{
    water += 10;
    animations.push_back(new RainAnim(g, groundPos, groundWH));

}

void World::doPlague(Graphics& g)
{
    population -= 10;
    if(men.size() > 0)
    {
        animations.push_back(new ManDeathAnim(men[0].location));
        men.erase(men.begin());
        animations.push_back(new ManDeathAnim(men[0].location));
        men.erase(men.begin());
    }
}

void World::doDrought(Graphics& g)
{
    water -= 10;
    animations.push_back(new DroughtAnim(groundPos, groundWH));
}

void World::doWind(Graphics& g)
{
    environment -= 10;
    if(trees.size() > 0)
    {
        animations.push_back(new WindAnim(trees[0].location));
        trees.erase(trees.begin());
        animations.push_back(new WindAnim(trees[0].location));
        trees.erase(trees.begin());
    }
}

