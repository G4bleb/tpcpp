/*

Programme produit le  par Gabriel LEBIS
*/
#include <iostream>
using namespace std;
const int TABMAX = 4;

void afficheEntier(int a=1){
  cout<<"entier affiché : "<<a<<endl;
}

void setIntTo(int &valtoset, const int valsetting){
  valtoset = valsetting;
}

int main(){
  int *tab = new int[TABMAX];
  for (int i=0; i<TABMAX; i++){
    cout<<"valeur "<<i<<"?"<<endl;
    // cin >> tab[i];
    setIntTo(tab[i], i);
  }

  bool laboule;
  cout << "laboule ? (1/0)"<<endl;
  cin >> laboule;

  if (laboule) {
    for (int i=0; i<TABMAX; i++){
      afficheEntier(tab[i]);
    }
  }

  delete[] tab;
  return 0;
}
