
#include "Animal.hpp"
#include <queue>
#ifndef MONDE_H
#define MONDE_H
class World{
private:
  unsigned int worldX;
  unsigned int worldY;
  unsigned int nbAnimals;
  unsigned int victims;
  unsigned int startingLife;
  char** tabWorld;
  std::vector<Animal*> vectorAnimals;
  std::queue<unsigned int> animalsDying;
  std::queue<Animal*> animalsBeingBorn;
public:
  World(unsigned int setNbAnimals, unsigned int setWorldX, unsigned int setWorldY);
  unsigned int getWorldX() const;
  unsigned int getWorldY() const;
  unsigned int getVictims() const;
  unsigned int getNbAnimals() const;
  char getAnimalType(unsigned int i) const;
  unsigned int getAnimalX(unsigned int i) const;
  unsigned int getAnimalY(unsigned int i) const;
  void spawning(unsigned int lionRate = 1, unsigned int gazelleRate = 1, unsigned int initStartingLife = 100);
  void display();
  bool move(unsigned int i);
  bool passeuntour();
  void death(const unsigned int i);
  void reproduceIfPossible(const unsigned int i);
  bool hasAnimalDied(int &i);
  bool isAnimalBorn(Animal* &newBorn);
  void eat(const unsigned int i);
  void getEaten(const unsigned int i);
  char checkForObstacle(short dir, Animal *anim);
};
#endif
