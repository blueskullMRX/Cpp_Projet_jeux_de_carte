#include "scene.h"
#include <QGraphicsSceneMouseEvent>

Scene::Scene():QGraphicsScene::QGraphicsScene()
{
    selectedCard = nullptr; //initialize selectedCard by nullptr
}


//function to call everytime the scene is clicked
/*void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qInfo("clicked");
    qInfo() << mouseEvent->lastScenePos();
    qInfo() << typeid(itemAt(lastclickedpos,QTransform())).name();
    QGraphicsScene::mousePressEvent(mouseEvent);
    lastclickedpos = mouseEvent->lastScenePos();
}*/



