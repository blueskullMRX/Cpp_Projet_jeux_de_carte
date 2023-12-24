#ifndef HAND_H
#define HAND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include "card.h"
#include "scene.h"


class Hand : public QGraphicsPixmapItem
{
public:
    explicit Hand(Scene *sc);
    void addCard(Card *addingCard); //adding card to this hand
    QVector<Card*> cardsHand; //vector contains the cards in this hand
    Card *checkCard(Card *checkingCard); //check if a card with the same number exist in theb vector
    void dropCard(Card *checkingCard); //check for a card and remove it from the vector



private :
    Scene * scene; //parent scene




};

#endif // HAND_H
