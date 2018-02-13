#include "Monde.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
Monde::Monde(int nbAnim){
  victimes=0;
  nbAnimaux=nbAnim;
  for (size_t j = 0; j < MAX_Y; j++) {
    for (size_t i = 0; i < MAX_X; i++) {
      tabMonde[i][j] = ' ';
    }
  }
}

int Monde::getMAX_X()const{
  return MAX_X;
}

int Monde::getMAX_Y()const{
  return MAX_Y;
}

void Monde::peuplement(){
  bool j=true;
  for (int i = 0; i < nbAnimaux; i++) {
    if (j) {
      vecteurAnimaux.push_back(new Gazelle());
    }else{
      vecteurAnimaux.push_back(new Lion());
    }
    j = !j;
  }
  for (int i = 0; i < nbAnimaux; i++) {
    vecteurAnimaux[i]->setX(rand()%MAX_X);
    vecteurAnimaux[i]->setY(rand()%MAX_Y);
    vecteurAnimaux[i]->setEnergie(rand()%100);
    tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = vecteurAnimaux[i]->getType();
  }
}

void Monde::afficher(){
  system("clear");
  system("clear");

  for (size_t j = 0; j < MAX_Y; j++) {
    for (size_t i = 0; i < MAX_X; i++){
      std::cout << tabMonde[i][j];
    }
    std::cout << '\n';
  }
  usleep(80000);
  // getchar();
}

bool Monde::bouge(int i){
  bool nourri = false;
  vecteurAnimaux[i]->setEnergie(vecteurAnimaux[i]->getEnergie()-1);
  switch (rand()%4) {
    case 0: //Z
    if (vecteurAnimaux[i]->getY()!=0 && (tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()-1]==' ' || (vecteurAnimaux[i]->getType() == 'L' && tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()-1] == 'G'))) {
      tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
      vecteurAnimaux[i]->setY(vecteurAnimaux[i]->getY()-1);
    }
    break;
    case 1: //Q
    if (vecteurAnimaux[i]->getX()!=0 && (tabMonde[vecteurAnimaux[i]->getX()-1][vecteurAnimaux[i]->getY()]==' '  || (vecteurAnimaux[i]->getType() == 'L' && tabMonde[vecteurAnimaux[i]->getX()-1][vecteurAnimaux[i]->getY()] == 'G'))) {
      tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
      vecteurAnimaux[i]->setX(vecteurAnimaux[i]->getX()-1);
    }
    break;
    case 2: //S
    if (vecteurAnimaux[i]->getY()!=MAX_Y-1 && (tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()+1]==' '  || (vecteurAnimaux[i]->getType() == 'L' && tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()+1] == 'G'))) {
      tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
      vecteurAnimaux[i]->setY(vecteurAnimaux[i]->getY()+1);
    }
    break;
    case 3: //D
    if (vecteurAnimaux[i]->getX()!=MAX_X-1 && (tabMonde[vecteurAnimaux[i]->getX()+1][vecteurAnimaux[i]->getY()]==' '  || (vecteurAnimaux[i]->getType() == 'L' && tabMonde[vecteurAnimaux[i]->getX()+1][vecteurAnimaux[i]->getY()] == 'G'))) {
      tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
      vecteurAnimaux[i]->setX(vecteurAnimaux[i]->getX()+1);
    }
    break;
  }
  if (vecteurAnimaux[i]->getType() == 'L' && tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] == 'G') {
    mange(i);
    nourri = true;
  }
  tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = vecteurAnimaux[i]->getType();
  return nourri;
}

bool Monde::passeuntour(){
  for (int i = 0; i < nbAnimaux; i++) {
    if (bouge(i)) {
      victimes++;
      i--;
    }
    if (vecteurAnimaux[i]->getEnergie()<=0) {
      mort(i);
      i--;
    }
  }

  if (!nbAnimaux) {
    std::cout << "Victimes : "<< victimes << std::endl;
    return false;
  }
  return true;
}

void Monde::mort(int i){
  tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = 'X';
  vecteurAnimaux.erase(vecteurAnimaux.begin()+i);
  nbAnimaux = static_cast<int>(vecteurAnimaux.size());
}

void Monde::mange(const int i){
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimaux); j++) {
    if (vecteurAnimaux[i]->getType() == 'L' && vecteurAnimaux[j]->getType() == 'G' && vecteurAnimaux[j]->getX() == vecteurAnimaux[i]->getX() && vecteurAnimaux[j]->getY() == vecteurAnimaux[i]->getY()) {
      vecteurAnimaux[i]->setEnergie(vecteurAnimaux[i]->getEnergie()+vecteurAnimaux[j]->getEnergie());
      vecteurAnimaux.erase(vecteurAnimaux.begin()+j);
      nbAnimaux = static_cast<int>(vecteurAnimaux.size());
    }
  }
}
