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
    vector<Card> cards;
    Card example({0,0}, CardType::Tree);
    int numCards = 6;
    int cardSpace = example.width + 20;
    int cardMargin = (g.width()-(cardSpace*numCards))/2;
    for(int i = 0; i < numCards - 1; i++)
    {
        CardType CT = static_cast<CardType>(rand()%(static_cast<int>(CardType::Wind)+1));
        cards.push_back(Card({((g.width()/numCards)*i)+cardMargin/2, groundPos.y - 200}, CT));
    }


    // stats
    int population = 50;
    int environment = 50;
    int food = 50;
    int water = 50;

    //position of mouse
    Vec2d mousePos = g.mousePos();

    // g.draw
    while (g.draw())
    {
        g.clear();
        // environment
        Vec2d groundWH{g.width(), 50};
        g.rect(groundPos, groundWH.x, groundWH.y, GREEN, GREEN);
        g.rect({(((g.width()/6)*5)+40),groundPos.y - 200}, 100, 150, BLUE, BLUE);

        // men
        for(int i = 0; i < men.size(); i++)
        {
            men[i].draw(g);
            men[i].update(g);
        }

        //cards
        for(Card& c: cards)
        {
            c.draw(g, mousePos);
//            if(c.inCard(mousePos))
//            {
//                c.rim = WHITE;
//            }
        }

        //display stats
        int statSize = 30;
        int topMar = 30;
        Button pop{"population: " + to_string(population), statSize};
        pop.location = {(g.width()-(pop.width/2))/5,g.height() - topMar};
        pop.draw(g);
        Button disFood{"food: " + to_string(food), statSize};
        disFood.location = {((g.width()-(disFood.width/2))/5)*2,g.height() - topMar};
        disFood.draw(g);
        Button disWater{"water: " + to_string(water), statSize};
        disWater.location = {((g.width()-(disWater.width/2))/5)*3,g.height() - topMar};
        disWater.draw(g);
        Button envi{"environment: " + to_string(environment), statSize};
        envi.location = {((g.width()-(envi.width/2))/5)*4,g.height() - topMar};
        envi.draw(g);

        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                men.push_back(Man{g, WHITE, manVelocity, groundPos, groundWH});
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



