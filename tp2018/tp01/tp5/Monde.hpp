
#include "Animal.hpp"
#ifndef MONDE_H
#define MONDE_H
class Monde{
private:
  static const int MAX_X = 70;
  static const int MAX_Y = 30;
  int nbAnimaux;
  char tabMonde[MAX_X][MAX_Y];
  std::vector<Animal*> vecteurAnimaux;
public:
  Monde(int nbAnim=0);
  int getMAX_X() const;
  int getMAX_Y() const;
  void peuplement();
  void afficher();
  void bouge(int i);
  int passeuntour();
  void mort(int i);
};
#endif
