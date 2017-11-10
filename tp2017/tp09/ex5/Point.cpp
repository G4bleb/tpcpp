#include "Point.h"
using namespace std;
int Point::nbpoints=0;
Point::Point():x(0),y(0){
  nbpoints++;
  cout << "Constructed w/o arguments" << '\n';
}
Point::Point(double initx, double inity){
  nbpoints++;
  x=initx;
  y=inity;
  cout << "Constructed w/ arguments" << '\n';
}
double Point::getx(){
  return x;
}
double Point::gety(){
  return y;
}
void Point::setx(double xset){
  x=xset;
}
void Point::sety(double yset) {
  y=yset;
}

void Point::afficher(){
  cout<<"x="<<x<<" y="<<y<<"\n";
}
