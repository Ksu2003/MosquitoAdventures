#include "mosquito.h"
#include <QTimer>
#include <QGraphicsScene>

Mosquito::Mosquito(QPixmap pixmap) : wingPos(WingPos::Up), wingDirection(0)

{
    setPixmap(pixmap);
    QTimer *mosqWingTimer = new QTimer(this);
    connect(mosqWingTimer,&QTimer::timeout,[=](){
        updatePixmap();
    });
    mosqWingTimer ->start(80);

    groundPosition = scenePos().y()  + 700;


    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation ->setStartValue( scenePos().y());
    yAnimation ->setEndValue(groundPosition);
    yAnimation ->setEasingCurve(QEasingCurve::InQuad);
    yAnimation -> setDuration(1000);
   /* yAnimation -> start(); */
}

void Mosquito::updatePixmap()
{
    if(wingPos == WingPos::Middle) {
        if (wingDirection)
        {
            setPixmap(QPixmap(":/new/prefix1/images/mosqup.png"));
            wingPos = WingPos::Up;
            wingDirection = 0;
        } else{
            setPixmap(QPixmap(":/new/prefix1/images/mosqdown.png"));
            wingPos = WingPos::Down;
            wingDirection = 1;
        }

    } else {
        setPixmap(QPixmap(":/new/prefix1/images/mosq.png"));
        wingPos = WingPos::Middle;
    }


}



qreal Mosquito::rotation() const
{
    return m_rotation;
}

void Mosquito::setRotation(qreal rotation)
{
    m_rotation = rotation;
}

qreal Mosquito::y() const
{
    return m_y;
}

void Mosquito::fly()
{
 yAnimation ->stop();
 qreal curPosY = y();
 yAnimation ->setStartValue(curPosY);
 yAnimation ->setEndValue(curPosY - scene() ->sceneRect().height()/8);
 yAnimation ->setEasingCurve(QEasingCurve::OutQuad);
 yAnimation -> setDuration(285);


 connect(yAnimation, &QPropertyAnimation::finished, [=](){
     fallDown();
 });
 yAnimation -> start();
}

void Mosquito::startFly()
{
 yAnimation -> start();
}

void Mosquito::fallDown()
{
 if(y() < groundPosition) {
     yAnimation ->stop();

     yAnimation ->setStartValue(y());
     yAnimation ->setEndValue(groundPosition);
     yAnimation ->setEasingCurve(QEasingCurve::InQuad);
     yAnimation -> setDuration(1200);
     yAnimation -> start();
 }
}

void Mosquito::stopping()
{
 yAnimation -> stop();

}

void Mosquito::setY(qreal y)
{
    moveBy(0, y - m_y);
    m_y = y;
}
