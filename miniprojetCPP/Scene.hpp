#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include "World.hpp"

class Scene : public QGraphicsScene {
	Q_OBJECT
	public:
		Scene(QObject *parent, unsigned int setNbAnimals, unsigned int setWorldX, unsigned int setWorldY, unsigned int lionRate, unsigned int gazelleRate);
		void displayAnimals();
		void startup(int msTickRate);
		void setTimerInterval(int setValue);
		unsigned int getWorldVictims() const;
	  unsigned int getWorldNbAnimals() const;
	private:
		static const int ANIMAL_SIZE = 25;

		World *sceneWorld;
		bool worldEnded;

		std::vector<QGraphicsPixmapItem*> graphAnimals;
		QGraphicsTextItem *population;
		QGraphicsTextItem *victims;

		QTimer *timer;
	public slots:
		void step();
};

#endif
