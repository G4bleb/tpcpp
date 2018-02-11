#include "Animal.hpp"
using namespace std;
int Animal::nbAnimaux=0;

Animal::Animal(int initx, int inity, int initEnergie){
  x=initx;
  y=inity;
  energie=initEnergie;
  nbAnimaux++;
}

Animal::~Animal(){
  nbAnimaux--;
}

int Animal::getX() const{return x;}
int Animal::getY() const{return y;}
int Animal::getEnergie() const{return energie;}
char Animal::getType() const{return type;}

void Animal::setX(const int xset){x=xset;}
void Animal::setY(const int yset){y=yset;}
void Animal::setEnergie(const int enerset){energie=enerset;}

// void Animal::setType(const char typeset){type=typeset;}

void Animal::afficher(){
  cout << "Position : x = " << x << ", y = " << y << "; energie = " << energie << endl;
}

int Animal::getNbAnimaux(){
  return nbAnimaux;
}

void Lion::afficher(){
  cout << "Lion : x = " << x << ", y = " << y << "; energie = " << energie << endl;
}
char Lion::getType() const{return 'L';}
void Gazelle::afficher(){
  cout << "Gazelle : x = " << x << ", y = " << y << "; energie = " << energie << endl;
}
char Gazelle::getType() const{return 'G';}
