/*

Programme produit le  par Gabriel LEBIS
*/
#include <iostream>
using namespace std;
const int TABMAX = 4;

class Point {
private:
  int x, y;

public:

  void affiche();
  int getx();
  int gety();
  Point(int xinit=0, int yinit=0){
    x = xinit;
    y = yinit;
  }

  ~Point (){
    cout<<"done"<<endl;
  }
};

int Point::getx(){
  return x;
}
int Point::gety(){
  return y;
}
void Point::affiche(){
  cout<<"x="<<getx()<<endl;
  cout<<"y="<<gety()<<endl;
}

int main(){

  Point newpoint(3,4);
  newpoint.affiche();

  return 0;
}
