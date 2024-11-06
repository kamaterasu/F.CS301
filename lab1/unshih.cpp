#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
  string line;
  ifstream file("../test.txt");

  if (file.is_open()) {
    while (getline(file, line)) {
      cout << line << endl;
    }
    file.close();
  } else {
    cerr << "Error" << endl;
  }

  return 0;
}
