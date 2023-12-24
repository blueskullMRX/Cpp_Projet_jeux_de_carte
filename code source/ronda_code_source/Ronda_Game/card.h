#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QPropertyAnimation>
#include <QtMultimedia>

class Scene;

class Card : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setpos) //position change animation
public:
    explicit Card(QString n,QString s,int wh,Scene *sc);
    explicit Card(Card *card); //copy constructor

    void flip(); //function that flip card
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; //mouse clicked function
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void setHand(int newHand); //function to set card hand
    int getNumber();//getter of number
    QPointF pos() const; //getter for pos (animation)
    QPropertyAnimation *posAnimation; //position animation
    void startAnim(QPointF addingPos,int duration); //function to set up and start animation
    void startAnim(QPointF addingPos);

public slots :
    void setpos(QPointF newPOS); //setter of position (animation)

signals:

private:
    QString number; // card number (8=jack , 9=queen , 10=king)
    QString sign; // 0 = dhouba , 1 = zrawet , 2 = syofa , 3 = tbou9a
    int whichhand;// hands that contains the card (1=player hand)
    bool isShown;// true is the card is shown
    Scene *scene; //parent scene

    QPixmap image; // Qpixmap that contain the right image
    QPixmap backImg; // Qpixmap that contain the back side image

    QPointF m_pos; //pos variable (animation)

    QPointF beforepos;
    bool hovered;

};

#endif // CARD_H
