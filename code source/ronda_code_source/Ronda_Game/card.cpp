#include "card.h"
#include "scene.h"

//constructor
Card::Card(QString n,QString s,int wh,Scene *sc):
    number(n),
    sign(s),
    whichhand(wh),
    isShown(false),
    scene(sc)
{
    //allow the card to be clickable
    setAcceptHoverEvents(true);
    hovered = false;

    // set up the card image
    QString link = "";
    link.append(":/Cards/imgs/").append(s).append(n).append(".png"); //select the right image
    image = QPixmap(link).scaled(scene->width()*0.09625,scene->height()*0.193,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    //image = QPixmap(":/backgrounds/imgs/11 jeben.png");

    //spawn the card hidden
    backImg = QPixmap(":/Cards/imgs/black.png").scaled(scene->width()*0.09625,scene->height()*0.193,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPixmap(backImg);

    //set up the position animation
    posAnimation = new QPropertyAnimation(this,"pos",this);
    posAnimation->setEasingCurve(QEasingCurve::InQuad); //animation easing cruve type


}

//copy constructor :)
Card::Card(Card *card):Card(card->number,card->sign,card->whichhand,card->scene)
{
}

//fonction to flip the card (change the QPixmap)
void Card::flip(){
    if(isShown) {
        //if card is shown-> hide it
        setPixmap(backImg);
        isShown = false;
    }
    else {
        //if card is hidden -> show it
        setPixmap(image);
        isShown = true;
    }
}
void Card::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    qInfo() << "eeeeeeeeeeeeeeeenteeeeeeeeeeeeeeeeeeer";
    if(scene->waiting && whichhand == 1){
        beforepos = this->pos();
        startAnim(this->pos()+QPointF(0,-10),100);
        hovered = true;
    }
    QGraphicsPixmapItem::hoverEnterEvent(event);
}
void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    qInfo() << "leeeeeeeeeeeeeeeeft";
    if(scene->waiting && whichhand == 1 && hovered){
        startAnim(beforepos,100);
        hovered = false;
    }
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}



// function to call everytime we click the card
void  Card::mousePressEvent(QGraphicsSceneMouseEvent *event) //override mousePressedEvent
{
    if(scene->waiting && whichhand == 1)
        scene->selectedCard=this; //set the parent scene selected card if the clicked card is in player hand only
    QGraphicsPixmapItem::mousePressEvent(event); // keep the parent class mousePressEvent method (GGrapgicsPixmapItem)
}

//setter of whichHand
void Card::setHand(int newHand){
    whichhand = newHand;
}

//getter of number (string to int)
int Card::getNumber()
{
    return number.toInt();
}

//getter of pos (animation)
QPointF Card::pos() const
{
    return m_pos;
}

//set up and start animation
void Card::startAnim(QPointF addingPos, int duration)
{
    posAnimation->setStartValue(this->pos());
    posAnimation->setEndValue(addingPos);
    posAnimation->setDuration(duration);
    posAnimation->start();

}

//set up and start animation (keep the last animation duration)
void Card::startAnim(QPointF addingPos)
{
    startAnim(addingPos,posAnimation->duration());
}


 //setter of pos (animation)
void Card::setpos(QPointF newPOS)
{
    m_pos = newPOS;
    setPos(newPOS); //affect pos to card actual position
}


