#ifndef ANIMATIONS_H
#define ANIMATIONS_H
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
    virtual void update(mssm::Graphics& g);
    bool finished(){ return animFrame >= animLength; }
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
public:
    ManDeathAnim(Vec2d manPos);
    virtual void draw(mssm::Graphics& g) override;
};

class RainAnim : public Animation
{
public:
    std::vector<Vec2d> positions;
    std::vector<Vec2d> velocity;
public:
    RainAnim(mssm::Graphics& g);
    virtual void draw(mssm::Graphics& g) override;
    virtual void update(mssm::Graphics& g) override;
};







#endif // ANIMATIONS_H
