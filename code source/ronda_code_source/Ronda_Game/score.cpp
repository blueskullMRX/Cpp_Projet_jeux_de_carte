#include "score.h"

Score::Score(Scene *scene, int hand):
    scene(scene),
    hand(hand)
{
    value = 0;
    text = new QGraphicsSimpleTextItem("0");
    text->setFont(QFont("Segoe UI Black",scene->width()*0.015));
    if(hand){
        image = new QGraphicsPixmapItem(QPixmap(":/backgrounds/imgs/ScoreNormal.png").scaled(scene->width()*0.2,scene->height()*0.2,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        addToGroup(image);
        text->setPos(QPointF(this->boundingRect().width()*0.725,this->boundingRect().height()*0.25)+QPointF(-text->boundingRect().width()/2,-text->boundingRect().height()/2));
    }
    else{
        image = new QGraphicsPixmapItem(QPixmap(":/backgrounds/imgs/ScoreFliped.png").scaled(scene->width()*0.2,scene->height()*0.2,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        addToGroup(image);
        text->setPos(QPointF(this->boundingRect().width()*0.725,this->boundingRect().height()*0.7)+QPointF(-text->boundingRect().width()/2,-text->boundingRect().height()/2));
    }
    addToGroup(text);






}

void Score::updateScore()
{

    text->setText(QString::number(value));
    if(hand) text->setPos(QPointF(this->boundingRect().width()*0.725,this->boundingRect().height()*0.25)+QPointF(-text->boundingRect().width()/2,-text->boundingRect().height()/2));
    else text->setPos(QPointF(this->boundingRect().width()*0.725,this->boundingRect().height()*0.7)+QPointF(-text->boundingRect().width()/2,-text->boundingRect().height()/2));



}
