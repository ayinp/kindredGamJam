#ifndef CARD_H
#define CARD_H
#include "graphics.h"

enum class CardType
{
    //continuous type
    Animal,
    Garden,
    Reproduction,
    Sacrifice,
    // event type
    Lightning, // keep this as first event type :)
    Tree,
    Person,
    Harvest,
    Rain,
    Plague,
    Drought,
    Wind // keep this as last event type :)
};

class Card
{
public:
    Vec2d location;
    CardType type;
    int width = 100;
    int height = 150;
    mssm::Image image;
public:
    Card(Vec2d location, CardType type);
    void draw(mssm::Graphics& g, bool hover);
    bool isEvent();
    mssm::Color innerColor();
    mssm::Color outerColor();
    bool inCard(Vec2d position);
};

#endif // CARD_H
