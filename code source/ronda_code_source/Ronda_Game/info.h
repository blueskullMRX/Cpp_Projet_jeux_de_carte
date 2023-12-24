#ifndef INFO_H
#define INFO_H

#include <QObject>
#include <QGraphicsSimpleTextItem>
#include <QPropertyAnimation>
#include "scene.h"



class Info : public QObject , public QGraphicsSimpleTextItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setanimopacity)
public:
    explicit Info(Scene *scene, QString text);

    qreal opacity() const;
    void setanimopacity(qreal newOpacity);
    QPropertyAnimation *opacityAnimation;
    void startAnimation();

signals:

private:
    qreal m_opacity;
    Scene *scene;
    bool isShown;
};

#endif // INFO_H
