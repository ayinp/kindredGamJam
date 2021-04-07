#include "continuous.h"
#include "sprites.h"
#include "graphics.h"
#include "animation.h"
#include "world.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

Continuous::Continuous(World& world)
    :world{world}
{

}

void Continuous::execute(mssm::Graphics &g)
{

}


continAnimal::continAnimal(World& world)
    :Continuous{world}
{

}

void continAnimal::execute(mssm::Graphics &g)
{
    world.food += 5;
    world.environment -= 5;
    world.dropAnimalOrMan(g, SpriteType::Animal);
    world.removePlant(g);
}

continGarden::continGarden(World &world)
    :Continuous{world}
{

}

void continGarden::execute(Graphics &g)
{
    world.environment += 5;
    world.water -= 5;
    world.dropPlant(g);
}

continReproduction::continReproduction(World &world)
    :Continuous{world}
{

}

void continReproduction::execute(Graphics &g)
{
    world.population += 5;
    world.food -= 5;
    world.dropAnimalOrMan(g, SpriteType::Man);
    world.removeAnimalOrMan(g, SpriteType::Animal);
}

continSacrifice::continSacrifice(World &world)
    :Continuous{world}
{

}

void continSacrifice::execute(Graphics &g)
{
    world.water += 5;
    world.population -= 5;
    world.justRain(g);
    world.removeAnimalOrMan(g, SpriteType::Man);
}
