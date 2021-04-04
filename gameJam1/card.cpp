#include "card.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

Card::Card(Vec2d location, CardType type)
    :location{location}, type{type}
{

}

void Card::draw(Graphics& g, Vec2d position)
{
//    if(inCard(position))
//    {
//        rim = WHITE;
//    }
    g.rect(location, width, height, rim, outerColor());
    g.rect(location.x+10, location.y+10, width - 20, height - 20, rim, innerColor());
}

bool Card::isEvent()
{
    return type >= CardType::Lightning;
}

Color Card::innerColor()
{
    switch(type)
    {
    case CardType::Tree:         return {0,51,0};      // dark green
    case CardType::Person:       return {160,82,45};   // brown
    case CardType::Lightning:    return {255,255,25};  // yellow
    case CardType::Wind:         return {84,84,84};    // grey
    case CardType::Animal:       return {128,0,32};    // burgundy
    case CardType::Drought:      return {255,0,0};     // red
    case CardType::Garden:       return {34,204,0};    // light green
    case CardType::Plague:       return {0,0,26};      // onyx
    case CardType::Reproduction: return {153,51,255};  // purple
    case CardType::Rain:         return {0,255,255};   // auqua
    case CardType::Harvest:      return {255,128,170}; // pink
    case CardType::Sacrafice:    return {255,255,255}; //white

    }
}

Color Card::outerColor()
{
    return isEvent() ? Color{255,165,0} : Color{135,206,250};
}

bool Card::inCard(Vec2d position)
{
    return position.x >= location.x &&
           position.x <= location.x + width &&
           position.y >= location.y &&
           position.y <= location.y+height;
}

//void Card::changeRim(Vec2d position)
//{
//    if (inCard(position))
//    {
//        rim = WHITE;
//    }
//}


