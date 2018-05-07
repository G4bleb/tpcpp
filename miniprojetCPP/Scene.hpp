#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include "World.hpp"

class Scene : public QGraphicsScene {
	Q_OBJECT
	public:
		Scene(QObject *parent = 0);
		void displayAnimals();
	private:
		static const int ANIMAL_SIZE = 25;
		static const int WINDOW_WIDTH = 800;
		static const int WINDOW_HEIGHT = 600;

		World *sceneWorld;
		bool worldEnded;

		std::vector<QGraphicsPixmapItem*> graphAnimals;
		QGraphicsTextItem *victims;
		QTimer *timer;
		int startTimer;
	public slots:
		void step();
};

#endif
