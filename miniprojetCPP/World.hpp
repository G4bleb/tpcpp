
#include "Animal.hpp"
#include <stack>
#ifndef MONDE_H
#define MONDE_H
class World{
private:
  static const int MAX_X = 30;
  static const int MAX_Y = 20;
  unsigned int nbAnimals;
  unsigned int victims;
  char tabWorld[MAX_X][MAX_Y];
  std::vector<Animal*> vectorAnimals;
  std::stack<int> animalsDying;
public:
  World(int nbAnim=0);
  int getMAX_X() const;
  int getMAX_Y() const;
  unsigned int getVictims();
  unsigned int getNbAnimals();
  char getAnimalType(unsigned int i);
  int getAnimalX(unsigned int i);
  int getAnimalY(unsigned int i);
  void spawning();
  void display();
  bool move(int i);
  bool passeuntour();
  void death(const int i);
  bool hasAnimalDied(int &i);
  void eat(const int i);
  void getEaten(const int i);
  char checkForObstacle(short dir, Animal *anim);
};
#endif
