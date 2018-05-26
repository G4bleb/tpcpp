#include "Animal.hpp"
using namespace std;

Animal::Animal(const unsigned int initx, const unsigned int inity, const unsigned int initEnergy){
  x=initx;
  y=inity;
  energy=initEnergy;
}

Animal::~Animal(){
}

unsigned int Animal::getX() const{return x;}
unsigned int Animal::getY() const{return y;}
unsigned int Animal::getEnergy() const{return energy;}
char Animal::getType() const{return type;}

void Animal::setX(const unsigned int xset){x=xset;}
void Animal::setY(const unsigned int yset){y=yset;}
void Animal::setEnergy(const unsigned int enerset){energy=enerset;}

void Animal::setType(const char typeset){type=typeset;}

void Animal::display(){
  cout << "Position : x = " << x << ", y = " << y << "; energy = " << energy << endl;
}

void Lion::display(){
  cout << "Lion : x = " << x << ", y = " << y << "; energy = " << energy << endl;
}
char Lion::getType() const{return 'L';}
void Gazelle::display(){
  cout << "Gazelle : x = " << x << ", y = " << y << "; energy = " << energy << endl;
}
char Gazelle::getType() const{return 'G';}
