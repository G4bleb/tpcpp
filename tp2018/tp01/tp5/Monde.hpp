
#include "Animal.hpp"
#ifndef MONDE_H
#define MONDE_H
class Monde{
private:
  static const int MAX_X = 80;
  static const int MAX_Y = 40;
  int nbAnimaux;
  unsigned int victimes;
  char tabMonde[MAX_X][MAX_Y];
  std::vector<Animal*> vecteurAnimaux;
public:
  Monde(int nbAnim=0);
  int getMAX_X() const;
  int getMAX_Y() const;
  unsigned int getVictimes();
  void peuplement();
  void afficher();
  bool bouge(int i);
  bool passeuntour();
  void mort(int i);
  void mange(const int i);
  void getEaten(const int i);
  char checkForObstacle(short dir, Animal *anim);
};
#endif
