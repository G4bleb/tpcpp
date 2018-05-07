#include "Scene.hpp"
#include "World.hpp"
Scene::Scene(QObject *parent) : QGraphicsScene(parent){
  // this->setSceneRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
  this->setBackgroundBrush(Qt::lightGray);

  sceneWorld = new World(30, 30, 20);
  worldEnded = false;
  sceneWorld->spawning();

  this->setSceneRect(0,0,ANIMAL_SIZE*sceneWorld->getWorldX(),ANIMAL_SIZE*sceneWorld->getWorldY());
  this->addRect(this->sceneRect(), QPen(Qt::black), Qt::white);
  // this->addRect(this->sceneRect(), QPen(Qt::black), QBrush(QPixmap("sand.jpg")));
  std::cout << "getting into for" << '\n';
  for (unsigned int i = 0; i < sceneWorld->getNbAnimals(); i++) {
    if (sceneWorld->getAnimalType(i) == 'L') {
      graphAnimals.push_back(new QGraphicsPixmapItem(QPixmap("Lion.png").scaled(ANIMAL_SIZE,ANIMAL_SIZE)));
    }else if (sceneWorld->getAnimalType(i) == 'G') {
      graphAnimals.push_back(new QGraphicsPixmapItem(QPixmap("Gazelle.png").scaled(ANIMAL_SIZE,ANIMAL_SIZE)));
    }
    graphAnimals[i]->setPos(ANIMAL_SIZE*sceneWorld->getAnimalX(i), ANIMAL_SIZE*sceneWorld->getAnimalY(i));
    this->addItem(graphAnimals[i]);
  }

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(step()));
}

void Scene::step(){
  // std::cout << "update" << '\n';
  if (!worldEnded) {
    worldEnded = !sceneWorld->passeuntour();
    // sceneWorld->display();
    for (int i = 0; sceneWorld->hasAnimalDied(i);) {
      // std::cout << i << " died" << '\n';
      this->removeItem(graphAnimals[i]);
      // graphAnimals[i]->setPixmap(QPixmap("dead.png").scaled(ANIMAL_SIZE, ANIMAL_SIZE));
      // this->update();
      graphAnimals.erase(graphAnimals.begin()+i);
    }
    for (unsigned int i = 0; i < sceneWorld->getNbAnimals(); i++) {
      graphAnimals[i]->setPos(ANIMAL_SIZE*sceneWorld->getAnimalX(i), ANIMAL_SIZE*sceneWorld->getAnimalY(i));
      this->update();
      // std::cout << "graphicMoved : " << sceneWorld->getAnimalType(i) << i << " to " << sceneWorld->getAnimalX(i) << ", "<< sceneWorld->getAnimalY(i) << '\n';
    }
  }else{
    // QApplication::quit();
  }
}

void Scene::startup(int msTickRate){
  // timer->start(17);
  timer->start(msTickRate);
}
