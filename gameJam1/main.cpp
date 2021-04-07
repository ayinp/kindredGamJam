#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>
#include <vector>
#include "sprites.h"
#include "button.h"
#include "card.h"
#include "world.h"
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
    // world
    World world;
    Vec2d groundPos{0, (g.height()/16)*8};
    Vec2d groundWH{g.width(), 50};
    world.groundPos = groundPos;
    world.groundWH = groundWH;

    // sprite things
    Vec2d manVelocity {0, -10};
    vector<Sprite> men;

    // card things
    int numCards = 6;
    Card example({0,0}, CardType::Tree);
    int spacing = (g.width()-example.width*numCards)/(numCards + 1);
    int cardSpace = example.width + spacing;
    vector<Card> cards = dealCards(g, numCards, groundPos.y, spacing, cardSpace);
    Image cardBack("back.png");

    Card animation{{0,0}, CardType::Tree};
    int animationCount = 0;

    // rounds
    int round = 1;

    // g.draw
    while (g.draw())
    {
        g.clear();

        //position of mouse
        Vec2d mousePos = g.mousePos();

        // environment
        world.draw(g, round);
        g.image({spacing + cardSpace*(numCards-1), groundPos.y - 200}, example.width + 10, example.height + 10, cardBack);

        //cards
        for(Card& c: cards)
        {
            c.draw(g, true);
        }

        //animate card
        if(animationCount > 0)
        {
            animation.location = animation.location + Vec2d{0, 15};
            animationCount--;
            animation.draw(g, false);
            if (animationCount == 0)
            {
                world.handleCard(g, animation.type, round);
                if(cards.size() <= 3)
                {
                    cards.clear();
                    cards = dealCards(g, numCards, groundPos.y, spacing, cardSpace);
                    round++;
                    world.newRound(g, round);
                }
            }
        }

        // display round
        g.text(20, 20, 50, to_string(round), WHITE);

        //click things
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
            {
                // men.push_back(Man{g, WHITE, manVelocity, groundPos, {g.width(), 50}});
                int index;
                if(isCardClicked(cards, {e.x, e.y}, index) && animationCount == 0)
                {
                    animation = cards[index];
                    cards.erase(cards.begin()+index);
                    animationCount = 50;
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
    Graphics g("Graphics", 1600, 900, graphicsMain);
    return 0;
}



