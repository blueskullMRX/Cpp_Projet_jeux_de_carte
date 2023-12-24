#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsItemGroup>
#include "scene.h"

class Score : public QGraphicsItemGroup
{
public:
    explicit Score(Scene *scene, int hand);
    void updateScore();
    int value;

private:
    Scene *scene;
    int hand;
    QGraphicsPixmapItem *image;
    QGraphicsSimpleTextItem *text;


signals:

};

#endif // SCORE_H
