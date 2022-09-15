#ifndef SCENE_H
#define SCENE_H

#include "mosquito.h"
#include <QObject>
#include <QGraphicsScene>
#include <block.h>
#include <QTimer>
#include <QPushButton>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addMosq();
    void startGame();
    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void scoreInc();

    void setScore(int newScore);

signals:
private:
    void gameOverGraphics();
    void hidegameOverGraphics();
    void cleanScene();
 void setUpBlockTimer();
 void stoppingMosqAndBlock();
 QTimer * blockTimer;
 Mosquito *mosq;
 bool gameOn;
  QPushButton *button;
protected:
 void keyPressEvent(QKeyEvent *event) override;
 void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

 int score;
 int bestScore;
 QGraphicsPixmapItem *gameOver;
 QGraphicsTextItem *scoreTextItem;

};

#endif // SCENE_H
