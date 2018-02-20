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

unsigned int Monde::getVictimes(){
  return victimes;
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
  // std::cout << "moving " <<i<< '\n';
  bool nourri = false;
  vecteurAnimaux[i]->setEnergie(vecteurAnimaux[i]->getEnergie()-1);
  switch (rand()%4) {
    case 0: //Z
    if (vecteurAnimaux[i]->getY()!=0) {
      if (checkForObstacle(0, vecteurAnimaux[i])==' ' || isPredator(0, vecteurAnimaux[i]) || isPrey(0, vecteurAnimaux[i])) {
        tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
        vecteurAnimaux[i]->setY(vecteurAnimaux[i]->getY()-1);
      }
    }
    break;
    case 1: //Q
    if (vecteurAnimaux[i]->getX()!=0) {
      if (checkForObstacle(1, vecteurAnimaux[i])==' ' || isPredator(1, vecteurAnimaux[i]) || isPrey(1, vecteurAnimaux[i])) {
        tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
        vecteurAnimaux[i]->setX(vecteurAnimaux[i]->getX()-1);
      }
    }

    break;
    case 2: //S
    if (vecteurAnimaux[i]->getY()!=MAX_Y-1) {
      if (checkForObstacle(2, vecteurAnimaux[i])==' ' || isPredator(2, vecteurAnimaux[i]) || isPrey(2, vecteurAnimaux[i])) {
        tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
        vecteurAnimaux[i]->setY(vecteurAnimaux[i]->getY()+1);
      }
    }
    break;
    case 3: //D
    if (vecteurAnimaux[i]->getX()!=MAX_X-1) {
      if (checkForObstacle(3, vecteurAnimaux[i])==' ' || isPredator(3, vecteurAnimaux[i]) || isPrey(3, vecteurAnimaux[i])) {
        tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = ' ';
        vecteurAnimaux[i]->setX(vecteurAnimaux[i]->getX()+1);
      }
    }
    break;
  }
  if (vecteurAnimaux[i]->getType() == 'L' && tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] == 'G') {
    mange(i);
    nourri = true;
  }else{
    if (vecteurAnimaux[i]->getType() == 'G' && tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] == 'L') {
      getEaten(i);
      nourri = true;
    }
  }
  tabMonde[vecteurAnimaux[i]->getX()][vecteurAnimaux[i]->getY()] = vecteurAnimaux[i]->getType();
  return nourri;
}

bool Monde::passeuntour(){
  for (int i = 0; i < nbAnimaux; i++) {
    if (bouge(i)) {
      victimes++;
      i--;
      if (i<0) {
        i=0;
      }
    }
    if (vecteurAnimaux[i]->getEnergie()<=0) {
      mort(i);
      i--;
    }
  }

  if (!nbAnimaux) {
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
  bool over = false;
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimaux) && !over; j++) {
    if (vecteurAnimaux[j]->getType() == 'G' && vecteurAnimaux[j]->getX() == vecteurAnimaux[i]->getX() && vecteurAnimaux[j]->getY() == vecteurAnimaux[i]->getY()) {
      vecteurAnimaux[i]->setEnergie(vecteurAnimaux[i]->getEnergie()+vecteurAnimaux[j]->getEnergie());
      vecteurAnimaux.erase(vecteurAnimaux.begin()+j);
      nbAnimaux = static_cast<int>(vecteurAnimaux.size());
      over=true;
      // std::cout << i <<" ate "<<j<< '\n';
    }
  }
}

void Monde::getEaten(const int i){
  bool over = false;
  for (unsigned int j = 0; j < static_cast<unsigned int>(nbAnimaux) && !over; j++) {
    if (vecteurAnimaux[j]->getType() == 'L' && vecteurAnimaux[j]->getX() == vecteurAnimaux[i]->getX() && vecteurAnimaux[j]->getY() == vecteurAnimaux[i]->getY()) {
      vecteurAnimaux[j]->setEnergie(vecteurAnimaux[i]->getEnergie()+vecteurAnimaux[j]->getEnergie());
      vecteurAnimaux.erase(vecteurAnimaux.begin()+i);
      nbAnimaux = static_cast<int>(vecteurAnimaux.size());
      over=true;
      // std::cout << i <<" got eaten by "<<j<< '\n';
    }
  }
}

char Monde::checkForObstacle(short dir, Animal *anim){
  switch (dir) {
    case 0: //Z
    if (anim->getY()!=0 || (anim->getType() == 'L' && tabMonde[anim->getX()][anim->getY()-1] == 'G')) {
      return tabMonde[anim->getX()][anim->getY()-1];
    }
    break;
    case 1: //Q
    if (anim->getX()!=0 || (anim->getType() == 'L' && tabMonde[anim->getX()-1][anim->getY()] == 'G')) {
      return tabMonde[anim->getX()-1][anim->getY()];
    }
    break;
    case 2: //S
    if (anim->getY()!=MAX_Y-1 || (anim->getType() == 'L' && tabMonde[anim->getX()][anim->getY()+1] == 'G')) {
      return tabMonde[anim->getX()][anim->getY()+1];
    }
    break;
    case 3: //D
    if (anim->getX()!=MAX_X-1  || (anim->getType() == 'L' && tabMonde[anim->getX()+1][anim->getY()] == 'G')) {
      return tabMonde[anim->getX()+1][anim->getY()];
    }
    break;
  }
  return false;
}

bool Monde::isPredator(short dir, Animal *anim){
  switch (dir) {
    case 0: //Z
    if (anim->getType() == 'L' && tabMonde[anim->getX()][anim->getY()-1] == 'G') {
      return true;
    }
    break;
    case 1: //Q
    if (anim->getType() == 'L' && tabMonde[anim->getX()-1][anim->getY()] == 'G') {
      return true;
    }
    break;
    case 2: //S
    if (anim->getType() == 'L' && tabMonde[anim->getX()][anim->getY()+1] == 'G') {
      return true;
    }
    break;
    case 3: //D
    if (anim->getType() == 'L' && tabMonde[anim->getX()+1][anim->getY()] == 'G') {
      return true;
    }
    break;
  }
  return false;
}

bool Monde::isPrey(short dir, Animal *anim){
  switch (dir) {
    case 0: //Z
    if (anim->getType() == 'G' && tabMonde[anim->getX()][anim->getY()-1] == 'L') {
      return true;
    }
    break;
    case 1: //Q
    if (anim->getType() == 'G' && tabMonde[anim->getX()-1][anim->getY()] == 'L') {
      return true;
    }
    break;
    case 2: //S
    if (anim->getType() == 'G' && tabMonde[anim->getX()][anim->getY()+1] == 'L') {
      return true;
    }
    break;
    case 3: //D
    if (anim->getType() == 'G' && tabMonde[anim->getX()+1][anim->getY()] == 'L') {
      return true;
    }
    break;
  }
  return false;
}
