#include "Scene.hpp"
#include "World.hpp"
Scene::Scene(QObject *parent, unsigned int parameters[]) : QGraphicsScene(parent){

  this->setBackgroundBrush(Qt::lightGray);
  sceneWorld = new World(parameters[0], parameters[1], parameters[2], parameters[6], parameters[7], parameters[8]);
  worldEnded = false;
  sceneWorld->spawning(parameters[3], parameters[4], parameters[5]);

  this->setSceneRect(0,0,ANIMAL_SIZE*sceneWorld->getWorldX(),ANIMAL_SIZE*sceneWorld->getWorldY());
  this->addRect(this->sceneRect(), QPen(Qt::black), Qt::white);
  // this->addRect(this->sceneRect(), QPen(Qt::black), QBrush(QPixmap("sand.jpg")));
  // std::cout << "getting into for" << '\n';
  for (unsigned int i = 0; i < sceneWorld->getNbAnimals(); i++) {
    if (sceneWorld->getAnimalType(i) == 'L') {
      graphAnimals.push_back(new QGraphicsPixmapItem(QPixmap("Lion.png").scaled(ANIMAL_SIZE,ANIMAL_SIZE)));
    }else if (sceneWorld->getAnimalType(i) == 'G') {
      graphAnimals.push_back(new QGraphicsPixmapItem(QPixmap("Gazelle.png").scaled(ANIMAL_SIZE,ANIMAL_SIZE)));
    }
    graphAnimals[i]->setPos(ANIMAL_SIZE*sceneWorld->getAnimalX(i), ANIMAL_SIZE*sceneWorld->getAnimalY(i));
    this->addItem(graphAnimals[i]);
  }

  population = new QGraphicsTextItem(tr("Nombre d'animaux en vie : ")+QString::number(sceneWorld->getNbAnimals()));
  population->setPos(0,0);
  // population->setScale(1.5);
  this->addItem(population);
  victims = new QGraphicsTextItem(tr(" Nombre d'animaux prédatés : ")+QString::number(sceneWorld->getNbAnimals()));
  victims->setPos(population->boundingRect().width(), 0);
  // victims->setScale(1.5);
  this->addItem(victims);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(step()));
}

void Scene::step(){
  // getchar();
  // std::cout << "update" << '\n';
  if (!worldEnded) {
    worldEnded = !sceneWorld->executeTurn();
    // sceneWorld->display();
    for (Animal *newBorn = NULL; sceneWorld->isAnimalBorn(newBorn);) {
      if (newBorn->getType()=='L') {
        graphAnimals.push_back(new QGraphicsPixmapItem(QPixmap("Lion.png").scaled(ANIMAL_SIZE,ANIMAL_SIZE)));
      }else{
        graphAnimals.push_back(new QGraphicsPixmapItem(QPixmap("Gazelle.png").scaled(ANIMAL_SIZE,ANIMAL_SIZE)));
      }
      this->addItem(graphAnimals.back());
      graphAnimals.back()->setPos(ANIMAL_SIZE*newBorn->getX(), ANIMAL_SIZE*newBorn->getY());
      // std::cout << sceneWorld->getAnimalType(i) << i << " SceneDied" << '\n';
      // graphAnimals[i]->setPixmap(QPixmap("dead.png").scaled(ANIMAL_SIZE, ANIMAL_SIZE));
      // this->update();
      // graphAnimals.erase(graphAnimals.begin()+i);
    }
    for (int i = 0; sceneWorld->hasAnimalDied(i);) {
      // std::cout << sceneWorld->getAnimalType(i) << i << " SceneDied" << '\n';
      this->removeItem(graphAnimals[i]);
      // graphAnimals[i]->setPixmap(QPixmap("dead.png").scaled(ANIMAL_SIZE, ANIMAL_SIZE));
      // this->update();
      graphAnimals.erase(graphAnimals.begin()+i);
    }
    for (unsigned int i = 0; i < sceneWorld->getNbAnimals(); i++) {
      graphAnimals[i]->setPos(ANIMAL_SIZE*sceneWorld->getAnimalX(i), ANIMAL_SIZE*sceneWorld->getAnimalY(i));
      // std::cout << "graphicMoved : " << sceneWorld->getAnimalType(i) << i << " to " << sceneWorld->getAnimalX(i) << ", "<< sceneWorld->getAnimalY(i) << '\n';
    }
    population->setPlainText(tr("Nombre d'animaux en vie : ")+QString::number(sceneWorld->getNbAnimals()));
    victims->setPlainText(tr(" Nombre d'animaux prédatés : ")+QString::number(sceneWorld->getVictims()));
    this->update();
  }
}

void Scene::startup(int msTickRate){
  // timer->start(17);
  timer->start(msTickRate);
}

void Scene::setTimerInterval(int setValue){
  timer->setInterval(setValue);
}

unsigned int Scene::getWorldVictims() const{
  return sceneWorld->getVictims();
}
unsigned int Scene::getWorldNbAnimals() const{
  return sceneWorld->getNbAnimals();
}
