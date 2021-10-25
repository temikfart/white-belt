#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//#define PART_ONE
#ifdef PART_ONE
int main() {
//  string rel_path = "../week-4/txt-and-streams/1/";
//  ifstream input(rel_path + "input.txt");
  ifstream input("input.txt");

  string line;
  if (input.is_open()) {
    while (getline(input, line)) {
      cout << line << endl;
    }
  } else {
    cout << "error" << endl;
  }

  return 0;
}
#endif

#define PART_TWO
#ifdef PART_TWO

int main() {
//  string rel_path = "../week-4/txt-and-streams/1/";
//  ofstream output(rel_path + "output.txt");
//  ifstream input(rel_path + "input.txt");
  ofstream output("output.txt");
  ifstream input("input.txt");

  if (input.is_open() && output.is_open()) {
    string line;
    while (getline(input, line)) {
      output << line << endl;
    }
  } else {
    cout << "error" << endl;
  }

  return 0;
}

#endif
