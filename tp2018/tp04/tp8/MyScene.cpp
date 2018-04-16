#include "MyScene.hpp"
MyScene::MyScene(QObject *parent) : QGraphicsScene(parent){
  this->setSceneRect(0,0,800,600);
  wayToMovePaddleP1 = 0;
  wayToMovePaddleP2 = 0;
  ballSpeedX = 1;
  ballSpeedY = 0;
  this->setBackgroundBrush(Qt::black);
  paddleP1 = new QGraphicsPixmapItem(QPixmap("random_gnome.png").scaled(paddleWidth,paddleLength));
  this->addItem(paddleP1);
  paddleP1->setPos(10 +paddleWidth, 600/2-paddleLength/2);

  paddleP2 = new QGraphicsPixmapItem(QPixmap("random_gnome.png").scaled(paddleWidth,paddleLength));
  this->addItem(paddleP2);
  paddleP2->setPos(790-paddleWidth, 600/2-paddleLength/2);

  line = new QGraphicsLineItem((paddleP2->x()+paddleP1->x())/2+paddleWidth/5, -70, (paddleP2->x()+paddleP1->x())/2+paddleWidth/5, 700);
  line->setPen(QPen(Qt::white));
  this->addItem(line);

  pinball = new QGraphicsPixmapItem(QPixmap("pinball.png").scaled(80,80));
  this->addItem(pinball);
  pinball->setPos(this->width()/2,this->height()/2);

  QGraphicsTextItem *textItem = new QGraphicsTextItem("Pongerini Pongerino");
  textItem->setPos(this->width()/2,this->height()/2);
  this->addItem(textItem);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(17);
}

void MyScene::update(){
  pinball->setPos(pinball->x()+ballSpeedX, pinball->y()+ballSpeedY);
  movePaddles();

}

void MyScene::keyPressEvent(QKeyEvent *ev){
  switch (ev->key()) {
    case Qt::Key_Z:
      wayToMovePaddleP1 = 1;
      break;
    case Qt::Key_S:
      wayToMovePaddleP1 = -1;
      break;
    case Qt::Key_Up:
      wayToMovePaddleP2 = 1;
      break;
    case Qt::Key_Down:
      wayToMovePaddleP2 = -1;
      break;
  }
  // movePaddles();
}

void MyScene::keyReleaseEvent(QKeyEvent *ev){
  switch (ev->key()) {
    case Qt::Key_Z:
    case Qt::Key_S:
      wayToMovePaddleP1 = 0;
      break;
    case Qt::Key_Up:
    case Qt::Key_Down:
      wayToMovePaddleP2 = 0;
      break;
  }
  // movePaddles();
}

void MyScene::movePaddles() {
  if (wayToMovePaddleP1 && paddleP1->y()-paddleSpeed*wayToMovePaddleP1 <= 370 && paddleP1->y()-paddleSpeed*wayToMovePaddleP1 >= -70) {
    paddleP1->setPos(paddleP1->x(), paddleP1->y()-paddleSpeed*wayToMovePaddleP1);
    qDebug() << "PaddleP1 x : " << paddleP1->x() << " PaddleP1 y : " << paddleP1->y();
  }
  if (wayToMovePaddleP2  && paddleP2->y()-paddleSpeed*wayToMovePaddleP2 <= 370 && paddleP2->y()-paddleSpeed*wayToMovePaddleP2 > -70) {
    paddleP2->setPos(paddleP2->x(), paddleP2->y()-paddleSpeed*wayToMovePaddleP2);
    qDebug() << "PaddleP2 x : " << paddleP2->x() << " PaddleP2 y : " << paddleP2->y();
  }
}
