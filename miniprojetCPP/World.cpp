#include "World.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
World::World(unsigned int setNbAnimals, unsigned int setWorldX, unsigned int setWorldY){
  victims=0;
  nbAnimals=setNbAnimals;
  worldX=setWorldX;
  worldY=setWorldY;

  tabWorld = new char*[worldX];
  for (size_t j = 0; j < worldX; j++) {
    tabWorld[j] = new char[worldY];
    for (size_t i = 0; i < worldY; i++) {
      tabWorld[j][i] = ' ';
    }
  }
}

unsigned int World::getWorldX()const{
  return worldX;
}

unsigned int World::getWorldY()const{
  return worldY;
}

unsigned int World::getVictims()const{
  return victims;
}

unsigned int World::getNbAnimals()const{
  return nbAnimals;
}

char World::getAnimalType(unsigned int i)const{
  return vectorAnimals[i]->getType();
}

unsigned int World::getAnimalX(unsigned int i)const{
  return vectorAnimals[i]->getX();
}

unsigned int World::getAnimalY(unsigned int i)const{
  return vectorAnimals[i]->getY();
}

void World::spawning(){
  unsigned int lionRate = 1, gazelleRate = 1, nbGazelles = 0, nbLions = 0;
  for (unsigned int i = 0; i < nbAnimals; i++) {
    if (nbLions!=lionRate) {
      vectorAnimals.push_back(new Lion());
      nbLions++;
    }else if(nbGazelles!=gazelleRate){
      vectorAnimals.push_back(new Gazelle());
      nbGazelles++;
    }
    if (nbLions==lionRate && nbGazelles==gazelleRate) {
      nbLions=0;
      nbGazelles=0;
    }
  }
  for (unsigned int i = 0; i < nbAnimals; i++) {
    vectorAnimals[i]->setX(rand()%worldX);
    vectorAnimals[i]->setY(rand()%worldY);
    vectorAnimals[i]->setEnergy(rand()%100);
    tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = vectorAnimals[i]->getType();
  }
}

void World::display(){
  system("clear");

  for (size_t j = 0; j < worldY; j++) {
    for (size_t i = 0; i < worldX; i++){
      std::cout << tabWorld[i][j];
    }
    std::cout << '\n';
  }
  // usleep(80000);
  // getchar();
}

bool World::move(const int i){
  bool nourri = false;
  vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()-1);
  switch (rand()%4) {
    case 0: //Z
      if (checkForObstacle(0, vectorAnimals[i])) {
        tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
        vectorAnimals[i]->setY(vectorAnimals[i]->getY()-1);
      }
    break;
    case 1: //Q
      if (checkForObstacle(1, vectorAnimals[i])) {
        tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
        vectorAnimals[i]->setX(vectorAnimals[i]->getX()-1);
      }

    break;
    case 2: //S
      if (checkForObstacle(2, vectorAnimals[i])) {
        tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
        vectorAnimals[i]->setY(vectorAnimals[i]->getY()+1);
      }
    break;
    case 3: //D
      if (checkForObstacle(3, vectorAnimals[i])) {
        tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
        vectorAnimals[i]->setX(vectorAnimals[i]->getX()+1);
      }
    break;
  }
  if (vectorAnimals[i]->getType() == 'L' && tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] == 'G') {
    // std::cout << vectorAnimals[i]->getType() << i <<" is going to eat" << '\n';
    eat(i);
    nourri = true;
  }else{
    if (vectorAnimals[i]->getType() == 'G' && tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] == 'L') {
      // std::cout << vectorAnimals[i]->getType() << i <<" is going to be eaten" << '\n';
      getEaten(i);
      nourri = true;
    }
  }
  tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = vectorAnimals[i]->getType();
  // std::cout << "matrixMoved : " << vectorAnimals[i]->getType() << i << " to " << vectorAnimals[i]->getX() << ", "<< vectorAnimals[i]->getY() << '\n';
  return nourri;
}

bool World::passeuntour(){
  for (int i = 0; i < static_cast<int>(nbAnimals); i++) {
    if (move(i)) {
      victims++;
      i--;
      if (i<0) {
        i=0;
      }
    }
    if (vectorAnimals[i]->getEnergy()<=0) {
      death(i);
      i--;
    }
  }

  if (!nbAnimals) {
    return false;
  }
  return true;
}

void World::death(const int i){
  // std::cout << i << " died" << '\n';
  animalsDying.push(i);
  tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = 'X';
  vectorAnimals.erase(vectorAnimals.begin()+i);
  // nbAnimals = static_cast<int>(vectorAnimals.size());
  nbAnimals--;
}

void World::eat(const int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (vectorAnimals[j]->getType() == 'G' && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
      vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()+vectorAnimals[j]->getEnergy());
      // std::cout << vectorAnimals[i]->getType() << i <<" ate "<< vectorAnimals[j]->getType() << j << '\n';

      animalsDying.push(i);
      vectorAnimals.erase(vectorAnimals.begin()+j);

      // nbAnimals = static_cast<int>(vectorAnimals.size());
      nbAnimals--;
      return;
    }
  }
}

void World::getEaten(const int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (vectorAnimals[j]->getType() == 'L' && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
      vectorAnimals[j]->setEnergy(vectorAnimals[i]->getEnergy()+vectorAnimals[j]->getEnergy());
      // std::cout << vectorAnimals[i]->getType() << i <<" got eaten by "<< vectorAnimals[j]->getType() << j << '\n';

      animalsDying.push(i);
      vectorAnimals.erase(vectorAnimals.begin()+i);

      // nbAnimals = static_cast<int>(vectorAnimals.size());
      nbAnimals--;

      return;
    }
  }
}

char World::checkForObstacle(short dir, Animal *anim){
  switch (dir) {
    case 0: //Z
    if (anim->getY()==0) {
      break;
    }else{
    // }else if(anim->getType() == 'L' && tabWorld[anim->getX()][anim->getY()-1] == 'G'){
      return tabWorld[anim->getX()][anim->getY()-1];
    }
    case 1: //Q
    if (anim->getX()==0) {
      break;
    }else{
    // }else if (anim->getType() == 'L' && tabWorld[anim->getX()-1][anim->getY()] == 'G') {
      return tabWorld[anim->getX()-1][anim->getY()];
    }
    case 2: //S
    if (anim->getY()==worldY-1) {
      break;
    }else{
    // }else if (anim->getType() == 'L' && tabWorld[anim->getX()][anim->getY()+1] == 'G') {
      return tabWorld[anim->getX()][anim->getY()+1];
    }
    case 3: //D
    if (anim->getX()==worldX-1) {
      break;
    }else{
    // }else if (anim->getType() == 'L' && tabWorld[anim->getX()+1][anim->getY()] == 'G') {
      return tabWorld[anim->getX()+1][anim->getY()];
    }
    break;
  }
  return false;
}

bool World::hasAnimalDied(int &i){
  if (animalsDying.empty()) {
    return false;
  }else{
    i = animalsDying.top();
    animalsDying.pop();
    return true;
  }
}
