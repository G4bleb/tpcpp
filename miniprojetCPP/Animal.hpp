#include <iostream>
#include <vector>
#ifndef ANIMAL_H
#define ANIMAL_H
using namespace std;
class Animal {
public:
  // Animal();
  Animal(int initx = 0, int inity=0, int initEnergy=100);
  ~Animal();
  int getX() const;
  int getY() const;
  int getEnergy() const;
  virtual char getType() const = 0;
  void setX(const int xset);
  void setY(const int yset);
  void setEnergy(const int enerset);
  void setType(const char typeset);
  void display();
private:
protected:
  int x,y, energy;
  char type;
};

class Lion : public Animal{
private:
public:
  Lion(){type='L';}
  ~Lion(){}
  char getType()const;
  void display();
};

class Gazelle : public Animal{
private:
public:
  Gazelle(){type='G';}
  ~Gazelle(){}
  char getType()const;
  void display();
};

#endif
