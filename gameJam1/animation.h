#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "sprites.h"
#include "graphics.h"


class Animation
{
public:
    int animLength = 100;
    int animFrame = 0;
public:
    Animation();
    virtual ~Animation();
    virtual void draw(mssm::Graphics& g);
    virtual void update(mssm::Graphics& g );
    bool finished(){ return animFrame >= animLength; }
};

class Start : public Animation
{
public:
    std::vector<Sprite> men;
    std::vector<Sprite> animals;
    std::vector<Sprite> trees;
    int numMen;
    int numAnimals;
    int numTrees;
    Vec2d groundPos;
    Vec2d groundWH;

public:
    Start(std::vector<Sprite>& men, std::vector<Sprite>& animals, std::vector<Sprite>& trees, int numMen, int numAnimals, int numTrees, Vec2d groundPos, Vec2d groundWH);
    virtual void draw(mssm::Graphics &g) override;
};


class LightningAnim : public Animation
{
public:
    Vec2d animalPos;
    bool facingLeft;
    // Animation interface
public:
    LightningAnim(Vec2d animalPos, bool facingLeft);
    virtual void draw(mssm::Graphics &g) override;
};

class WindAnim : public Animation
{
public:
    Vec2d treePos;
    Vec2d tornadoPos;
public:
    WindAnim(Vec2d treePos, Vec2d tornadoPos = {0,0});
    virtual void draw(mssm::Graphics &g) override;
    virtual void update(mssm::Graphics&g) override;
};



class ManDeathAnim : public Animation
{
public:
    Vec2d manPos;
    bool facingLeft;
    int whichMan;
public:
    ManDeathAnim(Vec2d manPos, bool facingLeft, int whichMan);
    virtual void draw(mssm::Graphics& g) override;
};

class RainAnim : public Animation
{
public:
    std::vector<Vec2d> positions;
    std::vector<Vec2d> velocity;
    Vec2d groundPos;
    Vec2d groundWH;
public:
    RainAnim(mssm::Graphics& g, Vec2d groundPos, Vec2d groundWH);
    virtual void draw(mssm::Graphics& g) override;
    virtual void update(mssm::Graphics& g) override;
};

class DroughtAnim : public Animation
{
public:
    Vec2d groundPos;
    Vec2d groundWH;
public:
    DroughtAnim(Vec2d groundPos, Vec2d groundWH);
    virtual void draw(mssm::Graphics& g) override;
};

class FeastAnim : public Animation
{
public:

public:
    virtual void draw(mssm::Graphics& g) override;
};

class killAnimalAnim : public Animation
{
public:
    Vec2d animalPos;
    bool facingLeft;
public:
    killAnimalAnim(Vec2d animalPos, bool facingLeft);
    virtual void draw(mssm::Graphics& g) override;
};

class Numbers : public Animation
{
public:
    Vec2d location;
    int numType;
    mssm::Image number;
    Vec2d statLoc;

public:
    Numbers(Vec2d statLoc, int numType);
    virtual void draw(mssm::Graphics& g) override;
};






#endif // ANIMATIONS_H
