#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtWidgets>
#include <cmath>

const int paddleSpeed = 5;
const int paddleWidth = 30;
const int paddleLength = 150;
const int windowWidth = 800;
const int windowHeight = 600;
const int pinballSize = 60;

class MyScene : public QGraphicsScene {
	Q_OBJECT
	public:
		MyScene(QObject *parent = 0);
		void keyPressEvent(QKeyEvent *ev);
		void keyReleaseEvent(QKeyEvent *ev);
		void movePaddles();
	private:
		QGraphicsPixmapItem *pinball;
		QGraphicsPixmapItem *paddleP1;
		QGraphicsPixmapItem *paddleP2;
		QGraphicsLineItem *line;
		QGraphicsTextItem *scoreBoardP1;
		QGraphicsTextItem *scoreBoardP2;
		QTimer *timer;
		int startTimer;
		float ballSpeedX, ballSpeedY;
		int wayToMovePaddleP1;
		int wayToMovePaddleP2;
		int scoreCountP1;
		int scoreCountP2;
	public slots:
		void update();
};

#endif
