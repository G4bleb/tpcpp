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
  char getType() const;
  void setX(const int xset);
  void setY(const int yset);
  void setEnergie(const int enerset);
  // void setType(const char typeset);
  void afficher();
  static int getNbAnimaux();
private:
  static int nbAnimaux;
protected:
  int x,y, energie;
  char type;
};

class Lion : public Animal{
private:
public:
  Lion(){type='L';}
  ~Lion(){}
  void afficher();
};

class Gazelle : public Animal{
private:
public:
  Gazelle(){type='G';}
  ~Gazelle(){}
  void afficher();
};

#endif
