#ifndef TABLE_H
#define TABLE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include "scene.h"
#include "hand.h"
#include <qvector.h>


class Table : public Hand
{
public:
    explicit Table(Scene *sc);
    QVector<QPointF> emptyPos;
    QVector<QPointF> usedPos;
    void fillPos(QPointF pos);
    void freePos(QPointF pos);
};

#endif // TABLE_H
