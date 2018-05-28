#include "MyScene.hpp"
MyScene::MyScene(QObject *parent) : QGraphicsScene(parent){
  this->setSceneRect(0,0,windowWidth,windowHeight);
  wayToMovePaddleP1 = 0;
  wayToMovePaddleP2 = 0;
  ballSpeedX = 8;
  ballSpeedY = 0;
  startTimer = 0;
  scoreCountP1 = 0;
  scoreCountP2 = 0;
  this->setBackgroundBrush(Qt::darkGray);
  paddleP1 = new QGraphicsPixmapItem(QPixmap("random_gnome.png").scaled(paddleWidth,paddleHeight));
  this->addItem(paddleP1);
  paddleP1->setPos(10+paddleWidth, windowHeight/2-paddleHeight/2);

  paddleP2 = new QGraphicsPixmapItem(QPixmap("random_gnome.png").scaled(paddleWidth,paddleHeight));
  this->addItem(paddleP2);
  paddleP2->setPos(windowWidth-10-paddleWidth, windowHeight/2-paddleHeight/2);

  line = new QGraphicsLineItem((paddleP2->x()+paddleP1->x())/2, 0, (paddleP2->x()+paddleP1->x())/2, windowHeight);
  line->setPen(QPen(Qt::white));
  this->addItem(line);

  pinball = new QGraphicsPixmapItem(QPixmap("pinball.png").scaled(pinballSize,pinballSize));
  this->addItem(pinball);
  pinball->setPos(this->width()/2,this->height()/2);

  scoreBoardP1 = new QGraphicsTextItem(QString::number(scoreCountP1));
  scoreBoardP1->setPos(this->width()/3,this->height()/2);
  scoreBoardP1->setScale(2);
  this->addItem(scoreBoardP1);

  scoreBoardP2 = new QGraphicsTextItem(QString::number(scoreCountP2));
  scoreBoardP2->setPos(this->width()/3*2,this->height()/2);
  scoreBoardP2->setScale(2);
  this->addItem(scoreBoardP2);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(17);
}

void MyScene::update(){
  movePaddles();
  if (startTimer <= 100) {
    startTimer++;
  }else{
  if (paddleP1->collidesWithItem(pinball)) {
    float bounceAngle = ((paddleP1->y()+(paddleHeight/2)) - (pinball->y()+(pinballSize/2)))/(paddleHeight/2)*maxBounceAngle;
    ballSpeedX = maxBallSpeed*cos(bounceAngle);
    ballSpeedY = -maxBallSpeed*sin(bounceAngle);
    // ballSpeedX = abs(ballSpeedX);
  }else if (paddleP2->collidesWithItem(pinball)) {
    float bounceAngle = ((paddleP2->y()+(paddleHeight/2)) - (pinball->y()+(pinballSize/2)))/(paddleHeight/2)*maxBounceAngle;
    // ballSpeedX = -abs(ballSpeedX);
    ballSpeedX = -maxBallSpeed*cos(bounceAngle);
    ballSpeedY = -maxBallSpeed*sin(bounceAngle);
  }
  if (pinball->y()<0 || pinball->y()>windowHeight-pinballSize) {
    ballSpeedY = -ballSpeedY;
  }
  pinball->setPos(pinball->x()+ballSpeedX, pinball->y()+ballSpeedY);
  }
  if (pinball->x()>windowWidth) {
    scoreCountP1++;
    scoreBoardP1->setPlainText(QString::number(scoreCountP1));
    pinball->setPos(this->width()/2-pinballSize/2,this->height()/2-pinballSize/2);
    ballSpeedY=0;
    ballSpeedX=maxBallSpeed;
    startTimer=0;
  }else if(pinball->x()<0){
    scoreCountP2++;
    scoreBoardP2->setPlainText(QString::number(scoreCountP2));
    pinball->setPos(this->width()/2-pinballSize/2,this->height()/2-pinballSize/2);
    ballSpeedY=0;
    ballSpeedX=-maxBallSpeed;
    startTimer=0;
  }
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
  if (wayToMovePaddleP1 && paddleP1->y()-paddleSpeed*wayToMovePaddleP1 < windowHeight-paddleHeight && paddleP1->y()-paddleSpeed*wayToMovePaddleP1 > 0) {

    paddleP1->setPos(paddleP1->x(), paddleP1->y()-paddleSpeed*wayToMovePaddleP1);
    // qDebug() << "PaddleP1 x : " << paddleP1->x() << " PaddleP1 y : " << paddleP1->y();
  }
  if (wayToMovePaddleP2  && paddleP2->y()-paddleSpeed*wayToMovePaddleP2 < windowHeight-paddleHeight && paddleP2->y()-paddleSpeed*wayToMovePaddleP2 > 0) {

    paddleP2->setPos(paddleP2->x(), paddleP2->y()-paddleSpeed*wayToMovePaddleP2);
    // qDebug() << "PaddleP2 x : " << paddleP2->x() << " PaddleP2 y : " << paddleP2->y();
  }
}
