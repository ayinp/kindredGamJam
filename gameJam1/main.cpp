#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>
#include <vector>
#include "man.h"
#include "button.h"
#include "card.h"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

using namespace std;
using namespace mssm;
// isCardClicked
bool isCardClicked(vector<Card> cards, Vec2d location, int& index)
{
    for(int i = 0; i < cards.size(); i++)
    {
        if (cards[i].inCard(location))
        {
            index = i;
            return true;
        }
    }
    return false;
}

// card randomisation
vector<Card> dealCards(Graphics& g,int numCards, int groundY, int spacing, int cardSpace)
{
    vector<Card> cards;
    for(int i = 0; i < numCards - 1; i++)
    {
        CardType CT = static_cast<CardType>(rand()%(static_cast<int>(CardType::Wind)+1));
        cards.push_back(Card{{spacing + cardSpace*i, groundY - 200}, CT});
    }
    return cards;
}



// game
void graphicsMain(Graphics& g)
{
    srand(time(nullptr));
    // environment things
    Vec2d groundPos{0, (g.height()/16)*8};

    // men things
    Vec2d manVelocity {0, -10};
    vector<Man> men;

    // card things
    int numCards = 6;
    Card example({0,0}, CardType::Tree);
    int spacing = (g.width()-example.width*numCards)/(numCards + 1);
    int cardSpace = example.width + spacing;
    vector<Card> cards = dealCards(g, numCards, groundPos.y, spacing, cardSpace);
    Image cardBack("back.png");

    Card animation{{0,0}, CardType::Tree};
    int animationCount = 0;


    // stats
    int population = 50;
    int environment = 50;
    int food = 50;
    int water = 50;

    // g.draw
    while (g.draw())
    {
        g.clear();

        //position of mouse
        Vec2d mousePos = g.mousePos();

        // environment
        Vec2d groundWH{g.width(), 50};
        g.rect(groundPos, groundWH.x, groundWH.y, GREEN, GREEN);
        g.image({spacing + cardSpace*(numCards-1), groundPos.y - 200}, example.width + 10, example.height + 10, cardBack);

        // men
        for(int i = 0; i < men.size(); i++)
        {
            men[i].draw(g);
            men[i].update(g);
        }

        //cards
        for(Card& c: cards)
        {
            c.draw(g, true);
        }

        //display stats
        int statSize = 30;
        int topMar = 30;
        Vec2d popLocation;
        Button pop{"population: " + to_string(population), statSize, popLocation};
        popLocation= {(g.width()-(pop.width/2))/5,g.height() - topMar};
        pop.draw(g);
        Vec2d disFoodLoc;
        Button disFood{"food: " + to_string(food), statSize, disFoodLoc};
        disFoodLoc = {((g.width()-(disFood.width/2))/5)*2,g.height() - topMar};
        disFood.draw(g);
        Vec2d disWaterLoc;
        Button disWater{"water: " + to_string(water), statSize, disWaterLoc};
        disWaterLoc = {((g.width()-(disWater.width/2))/5)*3,g.height() - topMar};
        disWater.draw(g);
        Vec2d enviLoc;
        Button envi{"environment: " + to_string(environment), statSize, enviLoc};
        enviLoc = {((g.width()-(envi.width/2))/5)*4,g.height() - topMar};
        envi.draw(g);

        //animate card
        if(animationCount > 0)
        {
            animation.location = animation.location + Vec2d{0, 7};
            animationCount--;
            animation.draw(g, false);
            if (animationCount == 0)
            {
                if(cards.size() <= 3)
                {
                    cards.clear();
                    cards = dealCards(g, numCards, groundPos.y, spacing, cardSpace);
                }
            }
        }

        //click things
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
            {
                int index;
                if(isCardClicked(cards, {e.x, e.y}, index) && animationCount == 0)
                {
                    switch(cards[index].type)
                    {
                    case CardType::Tree:
                        break;
                    case CardType::Person:
                        break;
                    case CardType::Lightning:
                        break;
                    case CardType::Wind:
                        break;
                    case CardType::Animal:
                        break;
                    case CardType::Drought:
                        break;
                    case CardType::Garden:
                        break;
                    case CardType::Plague:
                        break;
                    case CardType::Reproduction:
                        break;
                    case CardType::Rain:
                        break;
                    case CardType::Harvest:
                        break;
                    case CardType::Sacrifice:
                        break;
                    }
                    animation = cards[index];
                    cards.erase(cards.begin()+index);
                    animationCount = 90;
                }
            }
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }


    }

}


int main(int /*argc*/, char** /*argv*/)
{
    // main should be empty except for the following line:
    Graphics g("Graphics", 1200, 800, graphicsMain);
    return 0;
}



