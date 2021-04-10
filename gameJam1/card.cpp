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
    Color highlight;
    if(inCard(g.mousePos()) && hover)
    {
        string message;
        string effect;
        string typeOfCard;
        highlight = WHITE;
        switch(type)
        {
        case CardType::Tree:
            message = "TREE: This card places a tree on your planet";
            effect = "+10 environment";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Person:
            message = "PERSON: This card places a little person on your planet";
            effect = "+10 population";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Lightning:
            message = "LIGHTNING: This card will electrocute your livestock";
            effect = "-10 food";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Wind:
            message = "WIND: This card will blow away your trees";
            effect = "-10 environment";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Animal:
            message = "ANIMAL: This card places an animal into your world";
            effect = "+5 food, -5 environment";
            typeOfCard = "type: CONTINUOUS, this will take effect every 5 rounds";
            break;
        case CardType::Drought:
            message = "DROUGHT: This card will cause a short drought";
            effect = "-10 water";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Garden:
            message = "GARDEN: This card places a garden into your world";
            effect = "+5 environment, -5 water";
            typeOfCard = "type: CONTINUOUS, this will take effect every 5 rounds";
            break;
        case CardType::Plague:
            message = "PLAGUE: This card will cause a small plague";
            effect = "-10 population";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Reproduction:
            message = "REPRODUCTION: This card will make children continuously";
            effect = "+5 population, -5 food";
            typeOfCard = "type: CONTINUOUS, this will take effect every 5 rounds";
            break;
        case CardType::Rain:
            message = "RAIN: This card will cause a rain storm";
            effect = "+10 water";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Feast:
            message = "FEAST: This card will send a feast from the gods!";
            effect = "+10 food";
            typeOfCard = "type: EVENT, this event will happen once per placement";
            break;
        case CardType::Sacrifice:
            message = "SACRIFICE: This card will cause regular sacrifices to the god of water";
            effect = "+5 water, -5 population";
            typeOfCard = "type: CONTINUOUS, this will take effect every 5 rounds";
            break;

        }
        int buttonOffset = 50;
        int textSize = 25;
        Button button1{typeOfCard, textSize};
        Button button2{message, textSize};
        Button button3{effect, textSize};
        button1.location = {(g.width()-button1.width)/2, location.y - buttonOffset};
        button2.location = {(g.width()-button2.width)/2, button1.location.y - buttonOffset};
        button3.location = {(g.width()-button3.width)/2, button2.location.y - buttonOffset};
        button1.draw(g);
        button2.draw(g);
        button3.draw(g);
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
    case CardType::Feast:      return {255,128,170}; // pink
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

