#include "info.h"
#include <QTime>
#include <QCoreApplication>

Info::Info(Scene *scene, QString text):QGraphicsSimpleTextItem::QGraphicsSimpleTextItem(text),scene(scene)
{
    setFont(QFont("Segoe UI Black",scene->width()*0.015));
    setBrush(Qt::white);
    opacityAnimation = new QPropertyAnimation(this,"opacity",this);
    opacityAnimation->setEasingCurve(QEasingCurve::InQuad);
    setOpacity(0);
    isShown = false;
}

qreal Info::opacity() const
{
    return m_opacity;
}

void Info::setanimopacity(qreal newOpacity)
{
    m_opacity = newOpacity;
    setOpacity(newOpacity);
}

void Info::startAnimation()
{
    opacityAnimation->setDuration(300);
    if(isShown){
        opacityAnimation->setStartValue(1);
        opacityAnimation->setEndValue(0);
        isShown = false;
    } else{
        opacityAnimation->setStartValue(0);
        opacityAnimation->setEndValue(1);
        isShown = true;

    }
    opacityAnimation->start();
}
