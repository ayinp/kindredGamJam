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

World::World(Graphics& g)
{
    static Image cloud1("cloud1.png");
    static Image cloud2("cloud2.png");
    cloud1Pos = {0 - cloud1.width() - 200, g.height() - 100};
    cloud2Pos = {0 - cloud2.width() - 50, g.height() - 250};
    cloud3Pos = {0 - cloud2.width(), g.height() - 300};
}

void World::draw(mssm::Graphics &g, int round)
{

    // background
    static Image cardTable("cardTable.png");
    double tableRatio = 1.0*cardTable.height()/cardTable.width();
    g.image({0, 0}, g.width(), g.width()*tableRatio, cardTable);
    static Image ground("ground.png");
    g.image({groundPos.x, groundPos.y + 5}, g.width(), 55, ground);
    static Image sky("background.png");
    double skyRatio = 1.0*sky.height()/sky.width();
    g.image({0, groundPos.y + groundWH.y}, g.width(), g.width()*skyRatio, sky);

    //clouds
    static Image cloud1("cloud1.png");
    static Image cloud2("cloud2.png");

    g.image(cloud1Pos, 100, 100, cloud1);
    g.image(cloud2Pos, 200, 150, cloud2);
    g.image(cloud3Pos, 150, 100, cloud2);

    cloud1Pos += {1, 0};
    cloud2Pos += {2.5, 0};
    cloud3Pos += {2, 0};

    if(cloud1Pos.x > g.width())
    {
        cloud1Pos.x = 0 - cloud1.width();
    }
    if(cloud2Pos.x > g.width())
    {
        cloud2Pos.x = 0 - cloud2.width();
    }
    if(cloud3Pos.x > g.width())
    {
        cloud3Pos.x = 0 - cloud2.width();
    }

    //  initial sprites
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

    // stats but better
    static Image foodBar("foodBar.png");
    static Image popBar("popBar.png");
    static Image enviBar("enviBar.png");
    static Image waterBar("waterBar.png");
    int barWidth = 120;
    int barHeight = 70;
    int numBars = 4;
    int betweenSpacing = (g.width() - barWidth*numBars)/(numBars + 1);
    int barSpace = barWidth + betweenSpacing;
    foodLoc = {betweenSpacing + 0*barSpace, g.height() - 75};
    popLoc = {betweenSpacing + 1*barSpace, g.height() - 75};
    enviLoc = {betweenSpacing + 2*barSpace, g.height() - 75};
    waterLoc = {betweenSpacing + 3*barSpace, g.height() - 75};
    Color colorFood = barColor(1);
    Color colorPop = barColor(2);
    Color colorEnvi = barColor(3);
    Color colorWater = barColor(4);
    g.rect({foodLoc.x + 10, foodLoc.y+32.5}, food, 25, colorFood, colorFood);
    g.rect({popLoc.x + 10, popLoc.y+32.5}, population, 25, colorPop, colorPop);
    g.rect({enviLoc.x + 10, enviLoc.y+32.5}, environment, 25, colorEnvi, colorEnvi);
    g.rect({waterLoc.x + 10, waterLoc.y+32.5}, water, 25, colorWater, colorWater);
    g.image(foodLoc, barWidth, barHeight,foodBar);
    g.image(popLoc, barWidth, barHeight, popBar);
    g.image(enviLoc, barWidth, barHeight, enviBar);
    g.image(waterLoc, barWidth, barHeight, waterBar);

    // water tower
    static Image tower("tower.png");
    g.rect({g.width() - 50, groundPos.y + groundWH.y}, 20, 100, GREY, GREY);
    for (int i = 0; i <= water; i += 5)
    {
        g.rect({g.width() - 50, groundPos.y + groundWH.y}, 20, i, BLUE, BLUE);
    }
    g.image({g.width() - 75, groundPos.y + groundWH.y}, 70, 150, tower);

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
    static Sound baa1 ("baa1.wav");
    static Sound baa2 ("baa2.wav");
    static Sound baa3 ("baa3.wav");
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
    animations.push_back(new Numbers(foodLoc, 5));
    animations.push_back(new Numbers(enviLoc, -5));

    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(baa1);
        }
        else if(x == 1)
        {
            g.play(baa2);
        }
        else if(x == 2)
        {
            g.play(baa3);
        }
    }

}

void World::doGarden(Graphics& g)
{
    environment += 5;
    water -= 5;
    flowers.push_back(Sprite(g, SpriteType::Flower, PURPLE, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    continuous.push_back(new continGarden(*this));
    animations.push_back(new Numbers(enviLoc, 5));
    animations.push_back(new Numbers(waterLoc, -5));
    static Sound flowerPlop1 ("flower_plop1.wav");
    static Sound flowerPlop2 ("flower_plop2.wav");
    static Sound flowerPlop3 ("flower_plop3.wav");
    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(flowerPlop1);
        }
        else if(x == 1)
        {
            g.play(flowerPlop2);
        }
        else if(x == 2)
        {
            g.play(flowerPlop3);
        }
    }
}

void World::doReproduction(Graphics& g)
{
    bool facingLeft;
    population += 5;
    food -= 5;
    men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    if(animals.size() > 0)
    {
        if(animals[0].velocity.x <0)
        {
            facingLeft = true;
        }
        else
        {
            facingLeft = false;
        }
        animations.push_back(new killAnimalAnim({animals[0].location}, facingLeft));
        animals.erase(animals.begin());
    }
    continuous.push_back(new continReproduction(*this));
    animations.push_back(new Numbers(popLoc, 5));
    animations.push_back(new Numbers(foodLoc, -5));
    static Sound hi1 ("hi1.wav");
    static Sound hi2 ("hi2.wav");
    static Sound hi3 ("hi3.wav");
    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(hi1);
        }
        else if(x == 1)
        {
            g.play(hi2);
        }
        else if(x == 2)
        {
            g.play(hi3);
        }
    }
}

void World::doSacrifice(Graphics& g)
{
    bool facingLeft;
    water += 5;
    population -= 5;
    animations.push_back(new RainAnim(g, groundPos, groundWH));
    if(men.size() > 0)
    {
        if(men[0].velocity.x < 0)
        {
            facingLeft = true;
        }
        else
        {
            facingLeft = false;
        }
        animations.push_back(new ManDeathAnim(men[0].location, facingLeft, men[0].x));
        men.erase(men.begin());
    }
    continuous.push_back(new continSacrifice(*this));
    animations.push_back(new Numbers(waterLoc, 5));
    animations.push_back(new Numbers(popLoc, -5));
    static Sound death1 ("death1.wav");
    static Sound death2 ("death2.wav");
    static Sound death3 ("death3.wav");
    static Sound rain ("rain.wav");
    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(death1);
        }
        else if(x == 1)
        {
            g.play(death2);
        }
        else if(x == 2)
        {
            g.play(death3);
        }
        g.play(rain);
    }
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
            animations.push_back(new Numbers(foodLoc, -10));
        }
    }
    static Sound lightening ("lightening.wav");
    if(sound == true)
    {
        g.play(lightening);
    }
}

void World::doTree(Graphics& g, int num)
{
    environment += 10;
    for(int i = 0; i < num; i++)
    {
        trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
    }
    animations.push_back(new Numbers(enviLoc, 10));

    static Sound treePlop1 ("tree_plop1.wav");
    static Sound treePlop2 ("tree_plop2.wav");
    static Sound treePlop3 ("tree_plop3.wav");
    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(treePlop1);
        }
        else if(x == 1)
        {
            g.play(treePlop2);
        }
        else if(x == 2)
        {
            g.play(treePlop3);
        }
    }
}

void World::doPerson(Graphics& g, int num)
{
    population += 10;
    for(int i = 0; i < num; i++)
    {
        men.push_back(Sprite(g, SpriteType::Man, YELLOW, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
    }
    animations.push_back(new Numbers(popLoc, 10));
    static Sound hi1 ("hi1.wav");
    static Sound hi2 ("hi2.wav");
    static Sound hi3 ("hi3.wav");
    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(hi1);
        }
        else if(x == 1)
        {
            g.play(hi2);
        }
        else if(x == 2)
        {
            g.play(hi3);
        }
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
    animations.push_back(new Numbers(foodLoc, 10));
    static Sound ding ("blink.wav");
    static Sound baa1 ("baa1.wav");
    static Sound baa2 ("baa2.wav");
    static Sound baa3 ("baa3.wav");
    if(sound == true)
    {
        g.play(ding);
        int x = rand()%3;
        if(x == 0)
        {
            g.play(baa1);
        }
        else if(x == 1)
        {
            g.play(baa2);
        }
        else if(x == 2)
        {
            g.play(baa3);
        }
    }
}

void World::doRain(Graphics& g, int num)
{
    water += 10;
    animations.push_back(new RainAnim(g, groundPos, groundWH));
    animations.push_back(new Numbers(waterLoc, 10));
    static Sound rain ("rain.wav");
    if(sound == true)
    {
        g.play(rain);
    }

}

void World::doPlague(Graphics& g, int num)
{
    bool facingLeft;
    population -= 10;
    for(int i = 0; i < num; i++)
    {
        if(men.size() > 0)
        {
            if(men[0].velocity.x < 0)
            {
                facingLeft = true;
            }
            else
            {
                facingLeft = false;
            }
            animations.push_back(new ManDeathAnim(men[0].location, facingLeft, men[0].x));
            men.erase(men.begin());

        }
    }
    animations.push_back(new Numbers(popLoc, 10));
    static Sound death1 ("death1.wav");
    static Sound death2 ("death2.wav");
    static Sound death3 ("death3.wav");
    if(sound == true)
    {
        int x = rand()%3;
        if(x == 0)
        {
            g.play(death1);
        }
        else if(x == 1)
        {
            g.play(death2);
        }
        else if(x == 2)
        {
            g.play(death3);
        }
    }
}

void World::doDrought(Graphics& g, int num)
{
    water -= 10;
    animations.push_back(new DroughtAnim(groundPos, groundWH));
    animations.push_back(new Numbers(waterLoc, -10));
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
    animations.push_back(new Numbers(enviLoc, -10));
    static Sound wind ("wind.wav");
    if(sound == true)
    {
            g.play(wind);
    }
}

void World::removePlant(Graphics &g)
{
    int x = rand()%2;
    static Sound flowerPlop1 ("flower_plop1.wav");
    static Sound flowerPlop2 ("flower_plop2.wav");
    static Sound flowerPlop3 ("flower_plop3.wav");
    static Sound treePlop1 ("tree_plop1.wav");
    static Sound treePlop2 ("tree_plop2.wav");
    static Sound treePlop3 ("tree_plop3.wav");

    if(x == 0)
    {
        if(flowers.size() > 0)
        {
            flowers.erase(flowers.begin());
            if(sound == true)
            {
                int x = rand()%3;
                if(x == 0)
                {
                    g.play(flowerPlop1);
                }
                else if(x == 1)
                {
                    g.play(flowerPlop2);
                }
                else if(x == 2)
                {
                    g.play(flowerPlop3);
                }
            }

        }
        else if(trees.size() > 0)
        {
            trees.erase(trees.begin());
            if(sound == true)
            {
                int x = rand()%3;
                if(x == 0)
                {
                    g.play(treePlop1);
                }
                else if(x == 1)
                {
                    g.play(treePlop2);
                }
                else if(x == 2)
                {
                    g.play(treePlop3);
                }
            }
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
    static Sound baa1 ("baa1.wav");
    static Sound baa2 ("baa2.wav");
    static Sound baa3 ("baa3.wav");
    static Sound hi1 ("hi1.wav");
    static Sound hi2 ("hi2.wav");
    static Sound hi3 ("hi3.wav");
    if(type == SpriteType::Animal)
    {
        animals.push_back(Sprite(g, type, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
        if(sound == true)
        {
            int x = rand()%3;
            if(x == 0)
            {
                g.play(baa1);
            }
            else if(x == 1)
            {
                g.play(baa2);
            }
            else if(x == 2)
            {
                g.play(baa3);
            }
        }
    }
    else if(type == SpriteType::Man)
    {
        men.push_back(Sprite(g, type, RED, groundPos, groundWH, {rand()%(g.width() - 50)+25, g.height()}));
        if(sound == true)
        {
            int x = rand()%3;
            if(x == 0)
            {
                g.play(hi1);
            }
            else if(x == 1)
            {
                g.play(hi2);
            }
            else if(x == 2)
            {
                g.play(hi3);
            }
        }
    }
}

void World::dropPlant(Graphics &g)
{
    static Sound flowerPlop1 ("flower_plop1.wav");
    static Sound flowerPlop2 ("flower_plop2.wav");
    static Sound flowerPlop3 ("flower_plop3.wav");
    static Sound treePlop1 ("tree_plop1.wav");
    static Sound treePlop2 ("tree_plop2.wav");
    static Sound treePlop3 ("tree_plop3.wav");
    int x = rand()%2;

    if(x == 0)
    {
        flowers.push_back(Sprite(g, SpriteType::Flower, PURPLE, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));
        int x = rand()%3;
        if(x == 0)
        {
            g.play(flowerPlop1);
        }
        else if(x == 1)
        {
            g.play(flowerPlop2);
        }
        else if(x == 2)
        {
            g.play(flowerPlop3);
        }
    }

    else if(x == 1)
    {
        trees.push_back(Sprite(g, SpriteType::Tree, CYAN, groundPos, groundWH, {rand()%(g.width() - 150)+25, g.height()}));

        int x = rand()%3;
        if(x == 0)
        {
            g.play(treePlop1);
        }
        else if(x == 1)
        {
            g.play(treePlop2);
        }
        else if(x == 2)
        {
            g.play(treePlop3);
        }
    }
}

void World::removeAnimalOrMan(Graphics &g, SpriteType type)
{
    static Sound baa1 ("baa1.wav");
    static Sound baa2 ("baa2.wav");
    static Sound baa3 ("baa3.wav");
    static Sound death1 ("death1.wav");
    static Sound death2 ("death2.wav");
    static Sound death3 ("death3.wav");
    if(type == SpriteType::Animal)
    {
        animals.erase(animals.begin());
        int x = rand()%3;
        if(x == 0)
        {
            g.play(baa1);
        }
        else if(x == 1)
        {
            g.play(baa2);
        }
        else if(x == 2)
        {
            g.play(baa3);
        }
    }
    else if(type == SpriteType::Man)
    {
        men.erase(men.begin());
        if(sound == true)
        {
            int x = rand()%3;
            if(x == 0)
            {
                g.play(death1);
            }
            else if(x == 1)
            {
                g.play(death2);
            }
            else if(x == 2)
            {
                g.play(death3);
            }
        }
    }

}

void World::justRain(Graphics &g)
{
    animations.push_back(new RainAnim(g, groundPos, groundWH));
    static Sound rain ("rain.wav");
    if(sound == true)
    {
        g.play(rain);
    }
}

void World::newRound(Graphics &g, int round)
{
    if(round%5 == 0)
    {
        for(int i = 0; i < continuous.size(); i++)
        {
            continuous[i]->numUsed--;
            if(continuous[i]->numUsed <= 0)
            {
                continuous.erase(continuous.begin() + i);
            }
        }

        activeContin = continuous;
    }

}

void World::addPlus5(int location)
{
    switch(location)
    {
    case 1:
        animations.push_back(new Numbers(popLoc, 5));
        break;
    case 2:
        animations.push_back(new Numbers(enviLoc, 5));
        break;
    case 3:
        animations.push_back(new Numbers(foodLoc, 5));
        break;
    case 4:
        animations.push_back(new Numbers(waterLoc, 5));
        break;
    }
}

void World::addMinus5(int location)
{
    switch(location)
    {
    case 1:
        animations.push_back(new Numbers(popLoc, -5));
        break;
    case 2:
        animations.push_back(new Numbers(enviLoc, -5));
        break;
    case 3:
        animations.push_back(new Numbers(foodLoc, -5));
        break;
    case 4:
        animations.push_back(new Numbers(waterLoc, -5));
        break;
    }
}

Color World::barColor(int whichStat)
{
    switch(whichStat)
    {
    case 1:
        if(food > 75 && food <= 100)
        {
            return RED;
        }
        else if(food > 55 && food <= 75)
        {
            return YELLOW;
        }
        else if(food >= 45 && food <= 55)
        {
            return GREEN;
        }
        else if (food >= 25 && food < 45)
        {
            return YELLOW;
        }
        else if (food < 25)
        {
            return RED;
        }
    case 2:
        if(population > 75 && population <= 100)
        {
            return RED;
        }
        else if(population > 55 && population <= 75)
        {
            return YELLOW;
        }
        else if(population >= 45 && population <= 55)
        {
            return GREEN;
        }
        else if (population >= 25 && population < 45)
        {
            return YELLOW;
        }
        else if (population < 25)
        {
            return RED;
        }
    case 3:
        if(environment > 75 && environment <= 100)
        {
            return RED;
        }
        else if(environment > 55 && environment <= 75)
        {
            return YELLOW;
        }
        else if(environment >= 45 && environment <= 55)
        {
            return GREEN;
        }
        else if (environment >= 25 && environment < 45)
        {
            return YELLOW;
        }
        else if (environment < 25)
        {
            return RED;
        }
    case 4:
        if(water > 75 && water <= 100)
        {
            return RED;
        }
        else if(water > 55 && water <= 75)
        {
            return YELLOW;
        }
        else if(water >= 45 && water <= 55)
        {
            return GREEN;
        }
        else if (water >= 25 && water < 45)
        {
            return YELLOW;
        }
        else if (water < 25)
        {
            return RED;
        }
    default:
        return WHITE;
    }
}

bool World::activeAnimations()
{
    for(int i = 0; i < men.size(); i++)
    {
        if(men[i].doneFalling == false)
        {
            return true;
        }
    }
    for(int i = 0; i < animals.size(); i++)
    {
        if(animals[i].doneFalling == false)
        {
            return true;
        }
    }
    for(int i = 0; i < trees.size(); i++)
    {
        if(trees[i].doneFalling == false)
        {
            return true;
        }

    }
    for(int i = 0; i < flowers.size(); i++)
    {
        if(flowers[i].doneFalling == false)
        {
            return true;
        }
    }
    for(int i = 0; i < animations.size(); i++)
    {
        if(animations[i]->finished() == false)
        {
            return true;
        }
    }
    return false;
}

