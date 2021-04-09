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

// declarations
void game(Graphics& g);
void instructions(Graphics& g);

// is mouse in a spot?
bool mousePos (Vec2d mousePosition, Vec2d location, int width, int height)
{
    return mousePosition.x >= location.x &&
            mousePosition.x <= location.x + width &&
            mousePosition.y >= location.y &&
            mousePosition.y <= location.y+height;
}

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
vector<Card> dealCards(int numCards, int groundY, int spacing, int cardSpace)
{
    vector<Card> cards;
    for(int i = 0; i < numCards - 1; i++)
    {
        CardType CT = static_cast<CardType>(rand()%(static_cast<int>(CardType::Wind)+1));
        cards.push_back(Card{{spacing + cardSpace*i, groundY - 200}, CT, true});
    }
    return cards;
}

// welcome page
void welcome(Graphics& g)
{
    while(g.draw())
    {
        g.clear();
        static Image mainMenu("main_menu.png");
        static Image begin("begin.png");
        static Image beginSelected("beginSelected.png");
        static Image howToPlay("howToPlay.png");
        static Image howToPlaySelected("howToPlaySelected.png");
        double ratio = 1.0*mainMenu.width()/mainMenu.height();
        int buttonWidth = 300;
        int buttonHeight = 150;
        g.image({g.width()/2 - (g.height()*ratio)/2, 0}, g.height()*ratio, g.height(), mainMenu);
        int betweenSpacing = (g.width() - buttonWidth*2)/3;
        int barSpace = buttonWidth + betweenSpacing;
        Vec2d beginPos = {betweenSpacing + 0*barSpace, g.height()/5};
        Vec2d howToPlayPos = {betweenSpacing + barSpace, g.height()/5};
        g.image(beginPos, buttonWidth, buttonHeight, begin);
        g.image(howToPlayPos, buttonWidth, buttonHeight, howToPlay);

        if(mousePos(g.mousePos(), beginPos, buttonWidth, buttonHeight))
        {
            g.image(beginPos, buttonWidth, buttonHeight, beginSelected);
        }
        if(mousePos(g.mousePos(), howToPlayPos, buttonWidth, buttonHeight))
        {
            g.image(howToPlayPos, buttonWidth, buttonHeight, howToPlaySelected);
        }

        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
            {
                if(mousePos(g.mousePos(), beginPos, buttonWidth, buttonHeight))
                {
                    game(g);
                }
                if(mousePos(g.mousePos(), howToPlayPos, buttonWidth, buttonHeight))
                {
                    instructions(g);
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

// instructions Page
void instructions(Graphics& g)
{

}

// win case
void winCase(Graphics& g, Image winCase)
{
    Image mainMenu("mainMenu.png");
    Image mainMenuSelected("mainMenuSelected.png");
    Image playAgain("newGame.png");
    Image playAgainSelected("newGameSelected.png");
    while(g.draw())
    {
        g.clear();
        double ratio = 1.0*mainMenu.width()/mainMenu.height();
        int buttonWidth = 300;
        int buttonHeight = 150;
        g.image({g.width()/2 - (g.height()*ratio)/2, 0}, g.height()*ratio, g.height(), winCase);
        int betweenSpacing = (g.width() - buttonWidth*2)/3;
        int barSpace = buttonWidth + betweenSpacing;
        Vec2d button1Pos = {betweenSpacing + 0*barSpace, g.height()/5};
        Vec2d button2Pos = {betweenSpacing + barSpace, g.height()/5};
        g.image(button1Pos, buttonWidth, buttonHeight, mainMenu);
        g.image(button2Pos, buttonWidth, buttonHeight, playAgain);

        if(mousePos(g.mousePos(), button1Pos, buttonWidth, buttonHeight))
        {
            g.image(button1Pos, buttonWidth, buttonHeight, mainMenuSelected);
        }
        if(mousePos(g.mousePos(), button2Pos, buttonWidth, buttonHeight))
        {
            g.image(button2Pos, buttonWidth, buttonHeight, playAgainSelected);
        }

        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
            {
                if(mousePos(g.mousePos(), button1Pos, buttonWidth, buttonHeight))
                {
                    welcome(g);
                }
                if(mousePos(g.mousePos(), button2Pos, buttonWidth, buttonHeight))
                {
                    game(g);
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




// game
void game(Graphics& g)
{
    // world
    World world(g);
    Vec2d groundPos{0, (g.height()/16)*7};
    Vec2d groundWH{g.width(), 50};
    world.groundPos = groundPos;
    world.groundWH = groundWH;

    // sprite things
    vector<Sprite> men;

    // card things
    int numCards = 6;
    Card example({0,0}, CardType::Tree, true);
    int spacing = (g.width()-example.width*numCards)/(numCards + 1);
    int cardSpace = example.width + spacing;
    vector<Card> cards = dealCards(numCards, groundPos.y, spacing, cardSpace);
    Image cardBack("back.png");

    Card animation{{0,0}, CardType::Tree, false};
    int animationCount = 0;

    // rounds
    int round = 1;

    // g.draw
    while (g.draw())
    {
        g.clear();

        // environment
        world.draw(g, round);
        g.image({spacing + cardSpace*(numCards-1), groundPos.y - 200}, example.width + 10, example.height + 10, cardBack);

        //cards
        for(Card& c: cards)
        {
            c.draw(g);
        }

        //animate card
        if(animationCount > 0)
        {
            animation.location = animation.location + Vec2d{0, 15};
            animationCount--;
            animation.hover = false;
            animation.draw(g);
            if (animationCount == 0)
            {
                world.handleCard(g, animation.type, round);
                if(cards.size() <= 3)
                {
                    cards.clear();
                    cards = dealCards(numCards, groundPos.y, spacing, cardSpace);
                    round++;
                    world.newRound(g, round);
                }
            }
        }

        if(world.hasActiveContin())
        {
            if(!world.activeAnimations())
            {
                world.activeContin[0]->execute(g);
                world.activeContin.erase(world.activeContin.begin());
            }
            int rectHeight = 150;
            int rectWidth = 300;
            g.rect({0,0}, g.width(), groundPos.y+5, {0, 0, 0, 150}, {0, 0, 0, 150});
            Image continuousInEffect("continuousInEffect.png");
            g.image({(g.width()-rectWidth)/2, g.height()/8}, rectWidth, rectHeight, continuousInEffect);
            for(int i = 0; i < cards.size(); i++)
            {
                cards[i].hover = false;
            }
        }



        // display round
        g.text(20, 20, 50, "round: " + to_string(round), WHITE);

        //click things
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
            {
                // men.push_back(Man{g, WHITE, manVelocity, groundPos, {g.width(), 50}});
                int index;
                if(isCardClicked(cards, {e.x, e.y}, index) && animationCount == 0 && world.hasActiveContin() == false)
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


        bool resetGame = false;
        // win conditions
        if(world.population <= 0)
        {
            winCase(g, Image("underPop.png"));
            resetGame = true;
        }
        else if(world.population >=  100)
        {
            winCase(g, Image("overPop.png"));
            resetGame = true;
        }
        else if(world.environment <= 0)
        {
            winCase(g, Image("underEnvi.png"));
            resetGame = true;
        }
        else if(world.environment >=  100)
        {
            winCase(g, Image("overEnvi.png"));
            resetGame = true;
        }
        else if(world.food <= 0)
        {
            winCase(g, Image("underFood.png"));
            resetGame = true;
        }
        else if(world.food >=  100)
        {
            winCase(g, Image("overFood.png"));
            resetGame = true;
        }
        else if(world.water <= 0)
        {
            winCase(g, Image("underWater.png"));
            resetGame = true;
        }
        else if(world.water >=  100)
        {
            winCase(g, Image("overWater.png"));
            resetGame = true;
        }

        else if(round >= 50)
        {
            winCase(g, Image("vicrory.png"));
            resetGame = true;
        }

        if(resetGame == true)
        {
            world.food = 50;
            world.water = 50;
            world.population = 50;
            world.environment = 50;
        }

    }
}



// graphics main
void graphicsMain(Graphics& g)
{
    srand(time(nullptr));
    welcome(g);

}


int main(int /*argc*/, char** /*argv*/)
{
    // main should be empty except for the following line:
    Graphics g("Graphics", 1600, 900, graphicsMain);
    return 0;
}



