#include "animation.h"
using namespace mssm;

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::draw(mssm::Graphics &g)
{

}


void LightningAnim::draw(mssm::Graphics &g)
{
    g.rect({100, g.height() - animFrame}, 2, animFrame, YELLOW, YELLOW);
    animFrame++;
}
