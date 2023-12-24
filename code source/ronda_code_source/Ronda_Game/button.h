#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "scene.h"
class PlayWindow;

class Button:public QObject , public QGraphicsPixmapItem
{
public:
    Button(PlayWindow *playwindow, Scene *scene, int tp);
    void role();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
private :
    QPixmap icon;
    QPixmap iconHover;
    int type;
    Scene *scene;
    PlayWindow *playwindow;
};

#endif // BUTTON_H
