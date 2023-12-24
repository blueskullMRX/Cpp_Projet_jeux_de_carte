#ifndef DECK_H
#define DECK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "card.h"
#include <QVector>
#include "scene.h"


class Deck : public QGraphicsPixmapItem
{
public:
    explicit Deck(Scene *sc);
    void shuffle(); //function to shuffle cards in cardsDeck vector
    std::vector<Card*> cardsDeck; // vecotr contains all cards before game started
    Card *drawCard(); //function that drop a card from the vector and return a pointer on it
    Scene *scene; //parent scene
private:
};

#endif // DECK_H
