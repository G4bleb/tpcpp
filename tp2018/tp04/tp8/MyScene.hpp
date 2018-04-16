#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtWidgets>

const int paddleSpeed = 5;
const int paddleWidth = 30;
const int paddleLength = 300;

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
		QTimer *timer;
		float ballSpeedX, ballSpeedY;
		int wayToMovePaddleP1;
		int wayToMovePaddleP2;
	public slots:
		void update();
};

#endif
