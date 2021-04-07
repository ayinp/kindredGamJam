#include <iostream>
#include "world.h"
#include "button.h"
#include "sprites.h"
#include "continuous.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

World::World()
{
}

void World::draw(mssm::Graphics &g, int round)
{
    // background
    g.rect(groundPos, groundWH.x, groundWH.y, GREEN, GREEN);
    static Image sky("background.png");
    double skyRatio = 1.0*sky.width()/sky.height();
    g.image({0,groundPos.y + groundWH.y}, skyRatio*(g.height()-groundPos.y - groundWH.y), g.height()-groundPos.y - groundWH.y, sky);

    // initial sprites
    //    x++;
    //    if(x < 2)
    //    {
    //        for(int i = 0; i < numMen; i++)
    //        {
    //            men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    //        }
    //        for(int i = 0; i < numAnimals; i++)
    //        {
    //            animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    //        }
    //        for(int i = 0; i < numTrees; i++)
    //        {
    //            trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    //        }
    //    }

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
        doTree(g, 2);
        break;
    case CardType::Person:
        doPerson(g, 2);
        break;
    case CardType::Lightning:
        doLightning(g, 2);
        break;
    case CardType::Wind:
        doWind(g, 2);
        break;
    case CardType::Animal:
        doAnimal(g);
        break;
    case CardType::Drought:
        doDrought(g, 2);
        break;
    case CardType::Garden:
        doGarden(g);
        break;
    case CardType::Plague:
        doPlague(g, 2);
        break;
    case CardType::Reproduction:
        doReproduction(g);
        break;
    case CardType::Rain:
        doRain(g, 2);
        break;
    case CardType::Feast:
        doFeast(g, 2);
        break;
    case CardType::Sacrifice:
        doSacrifice(g);
        break;
    }
}

void World::startScreen(Graphics &g)
{
    animations.push_back(new Start(men, animals, trees, numMen, numAnimals, numTrees, groundPos, groundWH));
}

void World::doAnimal(Graphics& g)
{
    food += 5;
    environment -= 5;
    animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    if(flowers.size() > 0)
    {
        flowers.erase(flowers.begin());
    }
    else if(flowers.size() <= 0 && trees.size() > 0)
    {
        trees.erase(trees.begin());
    }
    continuous.push_back(new continAnimal(*this));

}

void World::doGarden(Graphics& g)
{
    environment += 5;
    water -= 5;
    flowers.push_back(Sprite(g, SpriteType::Flower, PURPLE, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    continuous.push_back(new continGarden(*this));
}

void World::doReproduction(Graphics& g)
{
    population += 5;
    food -= 5;
    men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    if(animals.size() > 0)
    {
        animations.push_back(new killAnimalAnim{animals[0].location});
        animals.erase(animals.begin());
    }
    continuous.push_back(new continReproduction(*this));
}

void World::doSacrifice(Graphics& g)
{
    water += 5;
    population -= 5;
    animations.push_back(new RainAnim(g, groundPos, groundWH));
    if(men.size() > 0)
    {
        animations.push_back(new ManDeathAnim(men[0].location));
        men.erase(men.begin());
    }
    continuous.push_back(new continSacrifice(*this));
}

void World::doLightning(Graphics& g, int num)
{
    bool facingLeft;
    food -= 10;
    for(int i = 0; i < num; i++)
    {
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
        }
    }
}

void World::doTree(Graphics& g, int num)
{
    environment += 10;
    for(int i = 0; i < num; i++)
    {
        trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    }
}

void World::doPerson(Graphics& g, int num)
{
    population += 10;
    for(int i = 0; i < num; i++)
    {
        men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
}

void World::doFeast(Graphics& g, int num)
{
    food += 10;
    for(int i = 0; i < num; i++)
    {
        animals.push_back(Sprite(g, SpriteType::Animal, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
    animations.push_back(new FeastAnim());
}

void World::doRain(Graphics& g, int num)
{
    water += 10;
    animations.push_back(new RainAnim(g, groundPos, groundWH));

}

void World::doPlague(Graphics& g, int num)
{
    population -= 10;
    for(int i = 0; i < num; i++)
    {
        if(men.size() > 0)
        {
            animations.push_back(new ManDeathAnim(men[0].location));
            men.erase(men.begin());

        }
    }
}

void World::doDrought(Graphics& g, int num)
{
    water -= 10;
    animations.push_back(new DroughtAnim(groundPos, groundWH));
}

void World::doWind(Graphics& g, int num)
{
    environment -= 10;
    for(int i = 0; i < num; i++)
    {
        if(trees.size() > 0)
        {
            animations.push_back(new WindAnim(trees[0].location));
            trees.erase(trees.begin());
        }
    }
}

void World::removePlant(Graphics &g)
{
    int x = rand()%2;

    if(x == 0)
    {
        if(flowers.size() > 0)
        {
            flowers.erase(flowers.begin());
        }
        else if(trees.size() > 0)
        {
            trees.erase(trees.begin());
        }
    }

    else if(x == 1)
    {
        if(trees.size() > 0)
        {
            trees.erase(trees.begin());
        }
        else if(flowers.size() > 0)
        {
            flowers.erase(flowers.begin());
        }
    }
}

void World::dropAnimalOrMan(Graphics &g, SpriteType type)
{
    if(type == SpriteType::Animal)
    {
        animals.push_back(Sprite(g, type, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
    else if(type == SpriteType::Man)
    {
        men.push_back(Sprite(g, type, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
}

void World::dropPlant(Graphics &g)
{
    int x = rand()%2;

    if(x == 0)
    {
        flowers.push_back(Sprite(g, SpriteType::Flower, PURPLE, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    }

    else if(x == 1)
    {
        trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    }
}

void World::removeAnimalOrMan(Graphics &g, SpriteType type)
{
    if(type == SpriteType::Animal)
    {
        animals.erase(animals.begin());
    }
    else if(type == SpriteType::Man)
    {
        men.erase(men.begin());
    }

}

void World::justRain(Graphics &g)
{
    animations.push_back(new RainAnim(g, groundPos, groundWH));
}

void World::newRound(Graphics &g, int round)
{
    if(round%5 == 0)
    {
        for(int i = 0; i < continuous.size(); i++)
        {
            continuous[i]->execute(g);
        }
    }

}

