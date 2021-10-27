#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#define FOR_SEND

int main() {
#ifndef FOR_SEND
  string rel_path = "../week-4/txt-and-streams/3/";
  ifstream input(rel_path + "input.txt");
#endif
#ifdef FOR_SEND
  ifstream input("input.txt");
#endif

  if (input.is_open()) {
    string N, M;
    getline(input, N, ' ');
    getline(input, M);

    int n, m;
    n = stoi(N);
    m = stoi(M);

    vector<string> words;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        // IN
        string word;

        if ((j + 1) != m) {
          getline(input, word, ',');
        } else {
          getline(input, word);
        }

        words.push_back(word);
      }
      // OUT
      bool flag = true;
      for (const auto& x : words) {
        if (flag) {
          cout << setw(10) << x;
          flag = false;
          continue;
        }
        cout << ' ' << setw(10) << x;
      }
      if ((i + 1) != n) {
        cout << endl;
      }

      words.resize(0);
    }
  } else {
    cout << "error" << endl;
  }

  return 0;
}