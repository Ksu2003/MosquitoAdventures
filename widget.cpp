#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <block.h>
#include <mosquito.h>
#include <scene.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new Scene(this);
   scene ->setSceneRect(-200, -200, 500, 500);
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/field.png"));
    scene ->addItem(pixItem);
    pixItem->setPos(QPointF(0,0)- QPointF(pixItem ->boundingRect().width()/2,pixItem ->boundingRect().height()/2));





    /* scene -> addLine(-400, 0, 400, 0, QPen(Qt::blue));
     scene -> addLine(0, -400, 0, 400, QPen(Qt::blue)); */

    /* Mosquito *mosq = new Mosquito(QPixmap(":/new/prefix1/images/mosqup.png"));
     scene -> addItem(mosq); */
      ui ->graphicsView -> setScene(scene);
      scene -> addMosq();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startGameButton_clicked()
{
    scene -> startGame();

    ui->startGameButton->setText("Replay");
}



