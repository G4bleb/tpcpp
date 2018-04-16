/*******
* Read input from cin
* Use cout to output your result.
* Use:
*  localPrint( string mystring)
* to display variable in a dedicated area.
* ***/
#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>
#include <math.h>

int main() {
  std::string line, token;
  float grades[3], aver;
  int i = 0, iMax, bestAver = 0;
  std::stringstream iss;

  std::getline(std::cin, line);
  iMax = std::atoi(line.c_str());
  while (i<iMax){
    std::getline(std::cin, line);
    aver = 0;
    iss.str(line);
    for (size_t j = 0; j < 3; j++) {
      getline(iss, token, ' ');
      grades[j] = std::atof(token.c_str());
      aver+=grades[j];
    }
    aver = ceil(aver/3);
    if (aver > bestAver) {
      bestAver = aver;
    }
    i++;
  }
  std::cout << bestAver;
  return 0;
}
