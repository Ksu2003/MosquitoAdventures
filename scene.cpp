#include "scene.h"
#include "mosquito.h"
#include "block.h"
#include "QPushButton"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}, gameOn(false), score(0), bestScore(0)
{
  setUpBlockTimer();

}

void Scene::addMosq()
{
    mosq = new Mosquito(QPixmap(":/new/prefix1/images/mosqup.png"));
    addItem(mosq);
}

void Scene::startGame()
{

 mosq ->startFly();
 if (!blockTimer -> isActive())
 {    setGameOn(true);
     setScore(0);
     cleanScene();
     hidegameOverGraphics();
     blockTimer -> start(1000);
 }
}
void Scene::setUpBlockTimer()
{
blockTimer = new QTimer(this);
connect(blockTimer,&QTimer::timeout, [=](){
    Block *block = new Block();
    connect(block, &Block::collideFail, [=]()
    {
       blockTimer -> stop();
       stoppingMosqAndBlock();
       setGameOn(false);
       gameOverGraphics();
    });
    addItem(block);
});
/*blockTimer ->start(1000); */
}

void Scene::stoppingMosqAndBlock()
{
 mosq ->stopping();

 QList<QGraphicsItem*> sceneItems = items();

    foreach(QGraphicsItem *item, sceneItems) {
    Block *block = dynamic_cast<Block*>(item);
    if (block){
        block -> stopBlock();
    }
    }
    mosq ->fallDown();
    QPushButton *button = new QPushButton("&Replay");

}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::scoreInc()
{
    score++;
    if (score > bestScore){
        bestScore = score;
    }
}

void Scene::gameOverGraphics()
{
    gameOver = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/gameOver.png"));
    addItem(gameOver);
        gameOver->setPos(QPointF(0,0)- QPointF(gameOver ->boundingRect().width()/2,gameOver ->boundingRect().height()/2));
    scoreTextItem = new  QGraphicsTextItem();
     QString htmlString = "<p> Score :" + QString::number(score) + "</p>" "<p> BestScore :" + QString::number(bestScore) + "</p>";
    scoreTextItem -> setHtml(htmlString);
    scoreTextItem -> setDefaultTextColor(Qt::red);
    addItem(scoreTextItem);
}

void Scene::hidegameOverGraphics()
{
    if(gameOver) {
        removeItem(gameOver);
        delete gameOver;
        gameOver = nullptr;
    }
    if (scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }

}

void Scene::cleanScene()
{
    QList<QGraphicsItem*> sceneItems = items();

       foreach(QGraphicsItem *item, sceneItems) {
       Block *block = dynamic_cast<Block*>(item);
       if (block){
           removeItem(block);
           delete block;
       }
         }

}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
        if (gameOn) {
        mosq->fly();
        }
    }
  QGraphicsScene::keyPressEvent(event);
    if(event->key() == Qt::Key_Space) {
        if (gameOn) {
          mosq->fly();
        }
    }

    QGraphicsScene::keyPressEvent(event);

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event-> button() == Qt::LeftButton ){
       if (gameOn) {
           mosq->fly();
       }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::setScore(int newScore)
{
    score = newScore;
}



