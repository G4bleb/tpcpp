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
  //Initialisation des variables
  victims=0;
  nbAnimals=setNbAnimals;
  worldX=setWorldX;
  worldY=setWorldY;
  healthThreshold = static_cast<float>(setHealthThreshold)/100; //Conversion des pourcentages en coefficients
  birthHealth = static_cast<float>(setBirthHealth)/100; //Conversion des pourcentages en coefficients
  birthCost =static_cast<float> (setBirthCost)/100; //Conversion des pourcentages en coefficients
  //Initialisation du monde
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

World::~World(){
  for (unsigned int i = 0; i < nbAnimals; i++) {
    delete vectorAnimals[i];
  }
  while (!animalsBeingBorn.empty()) {
    delete animalsBeingBorn.front();
    animalsBeingBorn.pop();
  }
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
    if (nbLions!=lionRate) {//Si je n'ai pas atteint le ratio de lion
      vectorAnimals.push_back(new Lion());
      nbLions++;
    }else if(nbGazelles!=gazelleRate){//Si je n'ai pas atteint le ratio de gazelles
      vectorAnimals.push_back(new Gazelle());
      nbGazelles++;
    }
    if (nbLions==lionRate && nbGazelles==gazelleRate){//Si j'ai atteint les ratios
    //Les remettre à 0
      nbLions=0;
      nbGazelles=0;
    }
  }
  for (unsigned int i = 0; i < nbAnimals; i++) {//Boucle de placement (aléatoire) des animaux
    vectorAnimals[i]->setX(rand()%worldX);
    vectorAnimals[i]->setY(rand()%worldY);
    // vectorAnimals[i]->setEnergy(rand()%startingLife);
    vectorAnimals[i]->setEnergy(startingLife);
    tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = vectorAnimals[i]->getType();//Ecriture des animaux dans le monde
  }
}

void World::display(){
  for (size_t j = 0; j < worldY; j++) {
    for (size_t i = 0; i < worldX; i++){
      std::cout << tabWorld[i][j];
    }
    std::cout << '\n' << '\n';
  }
  // usleep(20000);
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
  if (vectorAnimals[i]->getEnergy()==0) {//Si l'Animal qui a bougé n'a plus d'énergie
    death(i);//Le faire mourir
    return false;
  }
  vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()-1);//L'Animal se déplace : il perd 1 point d'énergie
  switch (rand()%4) {//
    case 0: //Haut
    if ((moved = checkForObstacle(0, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setY(vectorAnimals[i]->getY()-1);
    }
    break;
    case 1: //Gauche
    if ((moved = checkForObstacle(1, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setX(vectorAnimals[i]->getX()-1);
    }

    break;
    case 2: //Bas
    if ((moved = checkForObstacle(2, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setY(vectorAnimals[i]->getY()+1);
    }
    break;
    case 3: //Droite
    if ((moved = checkForObstacle(3, vectorAnimals[i]))) {
      tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = ' ';
      vectorAnimals[i]->setX(vectorAnimals[i]->getX()+1);
    }
    break;
  }
  if (moved) {//Si l'Animal s'est déplacé avec succès
    if (vectorAnimals[i]->getType() == 'L' && tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] == 'G') {
      //Si l'Animal est un Lion, et est tombé sur une Gazelle
      eat(i);//Il la mange
      nourri = true;
    }else if (vectorAnimals[i]->getType() == 'G' && tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] == 'L') {
      //Si l'animal est une Gazelle, et est tombée sur un Lion
      getEaten(i);//Elle se fait manger
      nourri = true;
    }else if (vectorAnimals[i]->getType() == tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()]){
      //Si l'animal est tombé sur un Animal de son espèce
      reproduceIfPossible(i);//Il essaie de se reproduire
    }
    tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = vectorAnimals[i]->getType();//Ecriture de l'Animal sur sa nouvelle position
  }
  return nourri;
}

//==============================================================================
// Fonction : World::executeTurn()
// Rôle : Avance un tour dans le monde
// Entrée : non
// Entrée/sortie : non
// Sortie : non
// Return : false si tous les animaux du monde sont morts
//==============================================================================

bool World::executeTurn(){
  for (int i = 0; i < static_cast<int>(nbAnimals); i++) {
    if (move(i)) { //Déplacer l'animal, et, si un animal a été mangé lors de ce déplacement
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

//==============================================================================
// Fonction : World::death()
// Rôle : tue l'animal indiqué
// Entrée : index de l'animal
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

void World::death(const unsigned int i){//L'Animal i meurt
  animalsDying.push(i);//L'ajouter aux animaux mourants
  tabWorld[vectorAnimals[i]->getX()][vectorAnimals[i]->getY()] = 'X';
  delete vectorAnimals[i];
  vectorAnimals.erase(vectorAnimals.begin()+i);//L'effacer du vecteur d'Animaux
  nbAnimals--;
}

//==============================================================================
// Fonction : World::eat()
// Rôle : fait manger le lion indiqué
// Entrée : index de l'animal
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

void World::eat(const unsigned int i){
  //On cherche quelle Animal (il sera j) va se faire manger par i
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (vectorAnimals[j]->getType() == 'G' && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
      vectorAnimals[i]->setEnergy(vectorAnimals[i]->getEnergy()+vectorAnimals[j]->getEnergy());//Le Lion gagne l'énergie de la Gazelle

      animalsDying.push(j);
      vectorAnimals.erase(vectorAnimals.begin()+j);

      // nbAnimals = static_cast<int>(vectorAnimals.size());
      nbAnimals--;
      return;
    }
  }
}

//==============================================================================
// Fonction : World::getEaten()
// Rôle : fait se faire manger la gazelle indiquée
// Entrée : index de l'animal
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

void World::getEaten(const unsigned int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (vectorAnimals[j]->getType() == 'L' && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
      vectorAnimals[j]->setEnergy(vectorAnimals[i]->getEnergy()+vectorAnimals[j]->getEnergy());

      animalsDying.push(i);
      vectorAnimals.erase(vectorAnimals.begin()+i);

      nbAnimals--;
      return;
    }
  }
}

//==============================================================================
// Fonction : World::reproduceIfPossible()
// Rôle : fait se faire reproduire, si c'est possible, l'animal indiqué
// Entrée : index de l'animal
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

void World::reproduceIfPossible(const unsigned int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimals); j++) {
    if (i!=j) {
      if (vectorAnimals[j]->getType() == vectorAnimals[i]->getType() && vectorAnimals[j]->getX() == vectorAnimals[i]->getX() && vectorAnimals[j]->getY() == vectorAnimals[i]->getY()) {
        if (vectorAnimals[j]->getEnergy() > startingLife*healthThreshold && vectorAnimals[i]->getEnergy() > startingLife*healthThreshold) {
          //Construction du nouvel Animal
          if (vectorAnimals[i]->getType()=='L') {
            vectorAnimals.push_back(new Lion());
          }else{
            vectorAnimals.push_back(new Gazelle());
          }
          vectorAnimals.back()->setX(vectorAnimals[j]->getX());
          vectorAnimals.back()->setY(vectorAnimals[j]->getY());
          vectorAnimals.back()->setEnergy(startingLife*birthHealth);
          //Application des coûts en énergie des animaux géniteurs
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

//==============================================================================
// Fonction : World::checkForObstacle()
// Rôle : vérifie si un obstacle est devant un animal
// Entrée : direction, pointeur sur l'animal
// Entrée/sortie : non
// Sortie : non
// Return : l'obstacle si il y en a un, false sinon
//==============================================================================

char World::checkForObstacle(short dir, Animal *anim){
  switch (dir) {
    case 0: //Haut
    if (anim->getY()==0) {
      break;
    }else{
      return tabWorld[anim->getX()][anim->getY()-1];
    }
    case 1: //Gauche
    if (anim->getX()==0) {
      break;
    }else{
      return tabWorld[anim->getX()-1][anim->getY()];
    }
    case 2: //Bas
    if (anim->getY()==worldY-1) {
      break;
    }else{
      return tabWorld[anim->getX()][anim->getY()+1];
    }
    case 3: //Droite
    if (anim->getX()==worldX-1) {
      break;
    }else{
      return tabWorld[anim->getX()+1][anim->getY()];
    }
    break;
  }
  return false;
}

//==============================================================================
// Fonction : World::hasAnimalDied()
// Rôle : récupère l'index d'un animal s'il est mort
// Entrée : non
// Entrée/sortie : l'index de l'animal mort s'il y en a un
// Sortie : non
// Return : true si un index d'animal est passé en entrée sortie, false sinon
//==============================================================================

bool World::hasAnimalDied(int &i){
  if (!animalsDying.empty()) {
    i = animalsDying.front();
    animalsDying.pop();
    return true;
  }
  return false;
}

//==============================================================================
// Fonction : World::isAnimalBorn()
// Rôle : récupère un animal s'il est né
// Entrée : non
// Entrée/sortie : un pointeur sur l'animal potentiellement né
// Sortie : non
// Return : true si un pointeur sur animal est passé en entrée sortie, false sinon
//==============================================================================

bool World::isAnimalBorn(Animal* &newBorn){
  if (!animalsBeingBorn.empty()) {
    newBorn = animalsBeingBorn.front();
    animalsBeingBorn.pop();
    return true;
  }
  return false;
}
