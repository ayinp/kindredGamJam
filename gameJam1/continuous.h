#ifndef CONTINUOUS_H
#define CONTINUOUS_H
#include "sprites.h"
#include "graphics.h"
#include "animation.h"

class World;

class Continuous
{
public:
    World& world;
public:
    Continuous(World& world);
    virtual void execute(mssm::Graphics& g);
};


class continAnimal : public Continuous
{
public:

public:
    continAnimal(World& world);
    virtual void execute(mssm::Graphics &g) override;
};

class continGarden : public Continuous
{
public:

public:
    continGarden(World& world);
    virtual void execute(mssm::Graphics &g) override;
};

class continReproduction : public Continuous
{
public:

public:
    continReproduction(World& world);
    virtual void execute(mssm::Graphics &g) override;

};

class continSacrifice : public Continuous
{
public:

public:
    continSacrifice(World& world);
    virtual void execute(mssm::Graphics &g) override;
};

#endif // CONTINUOUS_H
