#include <iostream>
#include <set>
#include <map>

using namespace std;

int main() {
  int q;
  cin >> q;

  string cmd;
  map<string, set<string>> syn;
  for (int i = 0; i < q; i++) {
    cin >> cmd;

    string w1, w2;
    if (cmd == "ADD") {
      cin >> w1 >> w2;

      syn[w1].insert(w2);
      syn[w2].insert(w1);
    }
    if (cmd == "COUNT") {
      cin >> w1;

      cout << syn[w1].size() << endl;
    }
    if (cmd == "CHECK") {
      cin >> w1 >> w2;

      bool b1 = syn[w1].count(w2) == 1;
      bool b2 = syn[w2].count(w1) == 1;
      if (b1 || b2) {
        cout << "YES";
      } else {
        cout << "NO";
      }
      cout << endl;
    }
  }

  return 0;
}
