#include "World.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

//==============================================================================
// Fonction : World::World()
// Rôle : Constructeur de World
// Entrée : unsigned int setNbAnimals,
//          unsigned int setWorldX,
//          unsigned int setWorldY,
//          unsigned int setHealthThreshold,
//          unsigned int setBirthHealth,
//          unsigned int setBirthCost
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

World::World(unsigned int setNbAnimals, unsigned int setWorldX, unsigned int setWorldY,  unsigned int setHealthThreshold, unsigned int setBirthHealth, unsigned int setBirthCost){
  victims=0;
  nbAnimals=setNbAnimals;
  worldX=setWorldX;
  worldY=setWorldY;
  healthThreshold = static_cast<float>(setHealthThreshold)/100; //Conversion des pourcentages en coefficients
  birthHealth = static_cast<float>(setBirthHealth)/100; //Conversion des pourcentages en coefficients
  birthCost =static_cast<float> (setBirthCost)/100; //Conversion des pourcentages en coefficients

  tabWorld = new char*[worldX];
  for (unsigned int j = 0; j < worldX; j++) {
    tabWorld[j] = new char[worldY];
    for (unsigned int i = 0; i < worldY; i++) {
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

//==============================================================================
// Fonction : World::spawning()
// Rôle : Apparition des animaux
// Entrée : unsigned int lionRate : Ratio de lions
//          unsigned int gazelleRate : Ratio de gazelles
//          unsigned int initStartingLife : Santé initiale des animaux
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

void World::spawning(unsigned int lionRate, unsigned int gazelleRate, unsigned int initStartingLife){
  unsigned int nbGazelles = 0, nbLions = 0;
  startingLife = initStartingLife;
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
    // vectorAnimals[i]->setEnergy(rand()%startingLife);
    vectorAnimals[i]->setEnergy(startingLife);
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

//==============================================================================
// Fonction : World::move()
// Rôle : Déplace l'animal vectorAnimals[i]
// Entrée : const unsigned int i : Numéro de l'Animal à déplacer
// Entrée/sortie : non
// Sortie : non
// Return : true si l'animal a chassé ou s'est fait chasser
//==============================================================================

bool World::move(const unsigned int i){
  bool nourri = false;
  bool moved = false;
  if (vectorAnimals[i]->getEnergy()==0) {
    death(i);
    return false;
  }
  vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()-1);
  switch (rand()%4) {
    case 0: //Z
    if ((moved = checkForObstacle(0, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setY(vectorAnimals[i]->getY()-1);
    }
    break;
    case 1: //Q
    if ((moved = checkForObstacle(1, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setX(vectorAnimals[i]->getX()-1);
    }

    break;
    case 2: //S
    if ((moved = checkForObstacle(2, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setY(vectorAnimals[i]->getY()+1);
    }
    break;
    case 3: //D
    if ((moved = checkForObstacle(3, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setX(vectorAnimals[i]->getX()+1);
    }
    break;
  }
  if (moved) {
    if (vectorAnimals[i]->getType() == 'L' && tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] == 'G') {
      // std::cout << vectorAnimals[i]->getType() << i <<" is going to eat" << '\n';
      eat(i);
      nourri = true;
    }else if (vectorAnimals[i]->getType() == 'G' && tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] == 'L') {
      // std::cout << vectorAnimals[i]->getType() << i <<" is going to be eaten" << '\n';
      getEaten(i);
      nourri = true;
    }else if (vectorAnimals[i]->getType() == tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()]){
      //reproduction
      std::cout << vectorAnimals[i]->getType() << i << " wants to mate" << '\n';
      // reproduceIfPossible(i, tabWorld[vectorAnimals[i]->getX(), tabWorld[vectorAnimals[i]->getX());
      reproduceIfPossible(i);
    }
    tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = vectorAnimals[i]->getType();
    // if (vectorAnimals[i]->getEnergy()<=0) {
    //   death(i);
    //   // i--;
    // }
    // std::cout << "matrixMoved : " << vectorAnimals[i]->getType() << i << " to " << vectorAnimals[i]->getX() << ", "<< vectorAnimals[i]->getY() << '\n';
  }
  return nourri;
}

//==============================================================================
// Fonction : World::executeTurn()
// Rôle : Avance un tour dans le monde
// Entrée : const unsigned int i : Numéro de l'Animal à déplacer
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

bool World::executeTurn(){
  for (int i = 0; i < static_cast<int>(nbAnimals); i++) {
    if (move(i)) {
      victims++;
      i--;
      if (i<0) {
        i=0;
      }
    }
  }

  if (!nbAnimals) {
    return false;
  }
  return true;
}

void World::death(const unsigned int i){
  std::cout << vectorAnimals[i]->getType() << i << " died of old age" << '\n';
  animalsDying.push(i);
  tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = 'X';
  vectorAnimals.erase(vectorAnimals.begin()+i);
  // nbAnimals = static_cast<int>(vectorAnimals.size());
  nbAnimals--;
}

void World::eat(const unsigned int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (vectorAnimals[j]->getType() == 'G' && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
      vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()+vectorAnimals[j]->getEnergy());
      std::cout << vectorAnimals[i]->getType() << i <<" ate "<< vectorAnimals[j]->getType() << j << '\n';

      animalsDying.push(j);
      vectorAnimals.erase(vectorAnimals.begin()+j);

      // nbAnimals = static_cast<int>(vectorAnimals.size());
      nbAnimals--;
      return;
    }
  }
}

void World::getEaten(const unsigned int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (vectorAnimals[j]->getType() == 'L' && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
      vectorAnimals[j]->setEnergy(vectorAnimals[i]->getEnergy()+vectorAnimals[j]->getEnergy());
      std::cout << vectorAnimals[i]->getType() << i <<" got eaten by "<< vectorAnimals[j]->getType() << j << '\n';

      animalsDying.push(i);
      vectorAnimals.erase(vectorAnimals.begin()+i);

      // nbAnimals = static_cast<int>(vectorAnimals.size());
      nbAnimals--;
      return;
    }
  }
}

void World::reproduceIfPossible(const unsigned int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (i!=j) {
      // std::cout << "nbAnimals = " << nbAnimals << '\n';
      // std::cout << "checking if " << vectorAnimals[i]->getType() << i <<" is with "<< vectorAnimals[j]->getType() << j << '\n';
      if (vectorAnimals[j]->getType() == vectorAnimals[i]->getType() && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
        std::cout << vectorAnimals[i]->getType() << i <<" is with "<< vectorAnimals[j]->getType() << j << '\n';
        std::cout << vectorAnimals[i]->getType() << i << " HP : " << vectorAnimals[i]->getEnergy() << '\n';
        std::cout << vectorAnimals[j]->getType() << j << " HP : " << vectorAnimals[j]->getEnergy() << '\n';
        if (vectorAnimals[j]->getEnergy() > startingLife*healthThreshold && vectorAnimals[i]->getEnergy() > startingLife*healthThreshold) {
          std::cout << vectorAnimals[i]->getType() << i <<" and "<< vectorAnimals[j]->getType() << j << " mated" << '\n';

          if (vectorAnimals[i]->getType()=='L') {
            vectorAnimals.push_back(new Lion());
            std::cout << "is lion" << '\n';
          }else{
            vectorAnimals.push_back(new Gazelle());
          }
          vectorAnimals.back()->setX(vectorAnimals[j]->getX());
          vectorAnimals.back()->setY(vectorAnimals[j]->getY());
          vectorAnimals.back()->setEnergy(startingLife*birthHealth);

          vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()-startingLife*birthCost);
          vectorAnimals[j]->setEnergy(vectorAnimals[j]->getEnergy()-startingLife*birthCost);

          animalsBeingBorn.push(vectorAnimals.back());
          nbAnimals++;
          return;
        }
      }
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
  if (!animalsDying.empty()) {
    i = animalsDying.front();
    animalsDying.pop();
    return true;
  }
  return false;
}

bool World::isAnimalBorn(Animal* &newBorn){
  if (!animalsBeingBorn.empty()) {
    newBorn = animalsBeingBorn.front();
    animalsBeingBorn.pop();
    return true;
  }
  return false;
}
