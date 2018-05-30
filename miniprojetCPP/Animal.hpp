#include <iostream>
#include <vector>
#ifndef ANIMAL_H
#define ANIMAL_H
using namespace std;
class Animal {
public:
  Animal(const unsigned int initx = 0, const unsigned int inity=0, const unsigned int initEnergy=100);
  virtual ~Animal(){}
  unsigned int getX() const;
  unsigned int getY() const;
  unsigned int getEnergy() const;
  virtual char getType() const = 0;
  void setX(const unsigned int xset);
  void setY(const unsigned int yset);
  void setEnergy(const unsigned int enerset);
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
