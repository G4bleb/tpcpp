#include <iostream>
#include <vector>
#ifndef ANIMAL_H
#define ANIMAL_H
using namespace std;
class Animal {
public:
  // Animal();
  Animal(int initx = 0, int inity=0, int initEnergie=100);
  ~Animal();
  int getX() const;
  int getY() const;
  int getEnergie() const;
  void setX(const int xset);
  void setY(const int yset);
  void setEnergie(const int enerset);
  void afficher();
  static int getNbAnimaux();
private:
  static int nbAnimaux;
  int x,y, energie;
};
#endif
