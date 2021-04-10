#include "card.h"
#include "button.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"
using namespace mssm;
using namespace std;

Card::Card(Vec2d location, CardType type, bool hover)
    :location{location}, type{type}, hover{hover}
{
    int x = rand()%100 +1;
    switch(type)
    {
    case CardType::Tree:         image.load("tree.png");         break;
    case CardType::Person:
        if(x > 1)
        {
        image.load("betterPerson.png");
        }
        else
        {
            image.load("person.png");
        }
        break;
    case CardType::Lightning:    image.load("lightning.png");    break;
    case CardType::Wind:         image.load("wind.png");         break;
    case CardType::Animal:       image.load("animals.png");       break;
    case CardType::Drought:      image.load("drought.png");      break;
    case CardType::Garden:       image.load("garden.png");       break;
    case CardType::Plague:       image.load("plague.png");       break;
    case CardType::Reproduction: image.load("reproduction.png"); break;
    case CardType::Rain:         image.load("rain.png");         break;
    case CardType::Feast:      image.load("harvest.png");      break;
    case CardType::Sacrifice:    image.load("sacrifice.png");    break;

    }
}

void Card::draw(Graphics& g)
{
    Image tree("treeDes.png");
    Image person("personDes.png");
    Image lightning("lightningDes.png");
    Image wind("windDes.png");
    Image drought("droughtDes.png");
    Image animal("animalsDes.png");
    Image garden("gardenDes.png");
    Image plague("plagueDes.png");
    Image reproduction("reproductionDes.png");
    Image rain("rainDes.png");
    Image feast("foodDes.png");
    Image sacrifice("sacrificeDes.png");
    int imageWidth = 500;
    int imageHeight = 150;
    Vec2d popUpLocation{(g.width() - imageWidth)/2, g.height()/16- 20};

    Color highlight;
    if(inCard(g.mousePos()) && hover)
    {
        highlight = WHITE;
        switch(type)
        {
        case CardType::Tree:
            g.image(popUpLocation, imageWidth, imageHeight, tree);
            break;
        case CardType::Person:
            g.image(popUpLocation, imageWidth, imageHeight, person);
            break;
        case CardType::Lightning:
            g.image(popUpLocation, imageWidth, imageHeight, lightning);
            break;
        case CardType::Wind:
            g.image(popUpLocation, imageWidth, imageHeight, wind);
            break;
        case CardType::Animal:
            g.image(popUpLocation, imageWidth, imageHeight, animal);
            break;
        case CardType::Drought:
            g.image(popUpLocation, imageWidth, imageHeight, drought);
            break;
        case CardType::Garden:
            g.image(popUpLocation, imageWidth, imageHeight, garden);
            break;
        case CardType::Plague:
            g.image(popUpLocation, imageWidth, imageHeight, plague);
            break;
        case CardType::Reproduction:
            g.image(popUpLocation, imageWidth, imageHeight, reproduction);
            break;
        case CardType::Rain:
            g.image(popUpLocation, imageWidth, imageHeight, rain);
            break;
        case CardType::Feast:
            g.image(popUpLocation, imageWidth, imageHeight, feast);
            break;
        case CardType::Sacrifice:
            g.image(popUpLocation, imageWidth, imageHeight, sacrifice);
            break;

        }
    }
    else
    {
        highlight = outerColor();
    }

    g.rect(location, width, height, outerColor(), highlight);
    g.image({location.x+10, location.y+10}, width - 20, height - 20, image);
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
    case CardType::Feast:      return {255,128,170};   // pink
    case CardType::Sacrifice:    return {255,255,255}; //white

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

