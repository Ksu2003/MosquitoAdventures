#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Block : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE  setX );
public:
    explicit Block();
    qreal x() const;
    ~Block();
     void stopBlock();
signals:
     void collideFail();
public slots:
    void setX(qreal x);
private:

    bool collidesWithMosq();
    QGraphicsPixmapItem *topBlock;
    QGraphicsPixmapItem *bottomBlock;
    QPropertyAnimation *xAnimation;
    qreal m_x;
    int yPos;
    bool mosqPass;
};

#endif // BLOCK_H
