#include <iostream>
#include <set>

using namespace std;

int main() {
  int N;
  cin >> N;
  set<string> s;
  string str;
  for (int i = 0; i < N; i++) {
    cin >> str;
    s.insert(str);
  }
  cout << s.size() << endl;

  return 0;
}