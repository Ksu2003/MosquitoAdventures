#include "block.h"
#include "QGraphicsScene"
#include <QRandomGenerator>
#include <mosquito.h>
#include <scene.h>
#include <QDebug>

Block::Block() : topBlock(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/block1.png"))), bottomBlock(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/block.png"))), mosqPass(false)

{
    topBlock ->setPos(QPointF(0,0) - QPointF(topBlock ->boundingRect().width()/2,topBlock ->boundingRect().height() + 135));
    bottomBlock ->setPos(QPointF(0,0) + QPointF(-bottomBlock ->boundingRect().width()/2, 135));

    addToGroup(topBlock);
    addToGroup(bottomBlock);

    yPos = QRandomGenerator::global()->bounded(350);
    int xRandom =  QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0) - QPoint( 900 + xRandom, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation ->setStartValue(1500 + xRandom);
    xAnimation ->setEndValue(-1500);
    xAnimation ->setEasingCurve(QEasingCurve::Linear);
    xAnimation -> setDuration(3000);

    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        scene() -> removeItem(this);
        delete this;
    });
    xAnimation -> start();



}

qreal Block::x() const
{
    return m_x;
}

Block::~Block()
{
    qDebug() << "Deleting block";
    delete topBlock;
    delete bottomBlock;
}

void Block::stopBlock()
{
 xAnimation -> stop();
}

void Block::setX(qreal x){
    m_x = x;
    if( x < 0 && !mosqPass) {
        mosqPass = true;
        QGraphicsScene *mScene = scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if (myScene) {
            myScene -> scoreInc();
        }
    }
    if(collidesWithMosq()) {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x, yPos));
}

bool Block::collidesWithMosq()
{
QList<QGraphicsItem*> collidingItems = topBlock ->collidingItems();
collidingItems.append(bottomBlock -> collidingItems());
   foreach(QGraphicsItem *item, collidingItems) {
    Mosquito *mosq= dynamic_cast<Mosquito*>(item);
      if(mosq) {
          return true;
      }
   }
  return false;
}
