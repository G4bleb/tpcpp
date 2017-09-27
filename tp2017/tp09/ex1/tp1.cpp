#include <iostream>
using namespace std;

void affiche(int val){
  cout << val << endl;
}
void affiche(int* tabval, int taille){
  for (int i = 0; i < taille; i++) {
    affiche(tabval[i]);
  }
}

int *initTab(int &i){
  int *tabval = NULL;
  for (i = 0; i != 4; i++) {
    tabval = new int[i+1]; //Le new afface les valeurs précédentes :(
    cout << "allow" << endl;
    cin >> tabval[i];
  }
  return tabval;
}

int main(){
  int i;
  int *tabval = initTab(i);
  affiche(tabval, i);

  return 0;
}
