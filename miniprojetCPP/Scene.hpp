#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include "World.hpp"

class Scene : public QGraphicsScene {
	Q_OBJECT
	public:
		Scene(QObject *parent = 0);
		void displayAnimals();
		void startup(int msTickRate);
	private:
		static const int ANIMAL_SIZE = 25;

		World *sceneWorld;
		bool worldEnded;

		std::vector<QGraphicsPixmapItem*> graphAnimals;
		QGraphicsTextItem *victims;
		QTimer *timer;
	public slots:
		void step();
};

#endif
