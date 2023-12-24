#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "card.h"

class Scene : public QGraphicsScene
{
public:
    explicit Scene();
    //void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //QPointF lastclickedpos;
    Card *selectedCard; //card selected bby the player in his turn
    bool waiting;

signals:

};

#endif // SCENE_H
