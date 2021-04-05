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
    bool finished(){ return animFrame >= animLength; }
};


class LightningAnim : public Animation
{



    // Animation interface
public:
    virtual void draw(mssm::Graphics &g) override;
};











#endif // ANIMATIONS_H
