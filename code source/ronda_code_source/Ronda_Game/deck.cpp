#include "deck.h"
#include <iterator>
#include <vector>
#include <qstring.h>
#include <algorithm>
#include <QRandomGenerator>

Deck::Deck(Scene *sc)
{
    scene = sc; //set up the parent scene of the deck
    // set up the image of hiden card
    setPixmap(QPixmap(":/Cards/imgs/black.png").scaled(scene->width()*0.09625,scene->height()*0.193,Qt::KeepAspectRatio,Qt::SmoothTransformation));


    //add all 40 cards to the vector
    for(int i=0 ; i<4 ; i++) //all signs
    {
        for(int j=0 ; j<10 ; j++) //all numbers
        {
            Card *addingcard = new Card(QString::number(j),QString::number(i),0,scene);
            cardsDeck.push_back(addingcard);//adding cards to the vector
        }
    }
}

//shuffle the cardsvector
void Deck::shuffle(){
    srand(time(0));
    for(int i=1 ; i< rand() ; i++){ //shuffle vector a random number of times
        std::random_shuffle(cardsDeck.begin(),cardsDeck.end());
    }
}


//function to call to draw a card
Card *Deck::drawCard()
{
    std::vector<Card*>::reverse_iterator it = cardsDeck.rbegin();
    cardsDeck.pop_back();
    return(*it);
}

