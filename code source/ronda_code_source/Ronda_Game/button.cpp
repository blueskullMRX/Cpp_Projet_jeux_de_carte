#include "button.h"
#include "playwindow.h"
#include <QApplication>

Button::Button(PlayWindow *playwindow,Scene *scene, int tp):type(tp),scene(scene),playwindow(playwindow){
    setAcceptHoverEvents(true);
    if(type==1){
        icon = QPixmap(":/Icons/imgs/close.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        iconHover = QPixmap(":/Icons/imgs/closeH.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }else if(type==2){
        icon = QPixmap(":/Icons/imgs/home.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        iconHover = QPixmap(":/Icons/imgs/homeH.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }else if(type ==3){
        icon = QPixmap(":/Icons/imgs/notmuted.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        iconHover = QPixmap(":/Icons/imgs/notmutedH.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
    setPixmap(icon);
}
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    setPixmap(iconHover);
    QGraphicsPixmapItem::hoverEnterEvent(event);
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    setPixmap(icon);
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    role();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Button::role()
{
    if(type==1){
        playwindow->backgroundMusic->stop();
        playwindow->~PlayWindow();
        delete playwindow;
        QApplication::quit();
    }else if(type==2){
        playwindow->close();
        playwindow->backgroundMusic->stop();
        playwindow->~PlayWindow();
    }
    else if(type==3){
        if(playwindow->muted){
            icon = QPixmap(":/Icons/imgs/notmuted.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            iconHover = QPixmap(":/Icons/imgs/notmutedH.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            playwindow->backgroundMusic->play();
            playwindow->muted=false;
        }else {
            icon = QPixmap(":/Icons/imgs/muted.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            iconHover = QPixmap(":/Icons/imgs/mutedH.png").scaled(scene->width()*0.05,scene->height()*0.05,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            playwindow->backgroundMusic->pause();
            playwindow->muted=true;
        }
    }
}
