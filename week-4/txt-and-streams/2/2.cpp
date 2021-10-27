#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#define FOR_SEND

int main() {
#ifndef FOR_SEND
  string rel_path = "../week-4/txt-and-streams/2/";
  ifstream input(rel_path + "input.txt");
#endif
#ifdef FOR_SEND
  ifstream input("input.txt");
#endif

  if (input.is_open()) {
    vector<double> nums;
    string line;

    while (getline(input, line)) {
      nums.push_back(stod(line));
    }

    cout << fixed << setprecision(3);
    for (const auto& x : nums) {
      cout << x << endl;
    }
  } else {
    cout << "error" << endl;
  }

  return 0;
}