#ifndef MOSQUITO_H
#define MOSQUITO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Mosquito : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE  setRotation );
    Q_PROPERTY(qreal y READ y WRITE  setY );
public:
    explicit Mosquito(QPixmap pixmap);

    qreal rotation() const;


    qreal y() const;
    void fly();
    void startFly();

    void fallDown();
    void stopping();
signals:
public slots:
    void setRotation(qreal rotation);
    void setY(qreal y);

private:
    enum WingPos{
        Up,
        Middle,
        Down};
 void updatePixmap();
 WingPos wingPos;
 bool wingDirection;
 QPropertyAnimation *yAnimation;
 QPropertyAnimation *rotationAnimation;
 qreal m_rotation;
 qreal m_y;
 qreal groundPosition;
};

#endif // MOSQUITO_H
