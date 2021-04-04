#include "button.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

Button::Button()
{

}

Button::Button(string label, int size)
{
    text = label;
    textSize = size;
    location = {0, 0};
    TextMetrics textMetrics;
    Vec2d rectPos;
    textMetrics.rect(location, text, textSize, rectPos, width, height);
}

bool  Button::inButton(Vec2d position)
{
    return position.x >= location.x &&
           position.x <= location.x + width &&
           position.y >= location.y &&
           position.y <= location.y + height;
}

void Button::draw(Graphics& g)
{
    TextMetrics textMetrics;
    Vec2d rectPos;
    textMetrics.rect(location, text, textSize, rectPos, width, height);
    g.rect(rectPos, width, height, outerColor, color);
    g.text(location, textSize, text, textColor);
    location = rectPos;
}

void Button::setColor(Color color, Color textColor, Color outerColor)
{
    this->color = color;
    this->textColor = textColor;
    this->outerColor = outerColor;
}
