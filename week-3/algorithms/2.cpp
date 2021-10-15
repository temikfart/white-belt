#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int N;
  vector<string> str;
  cin >> N;

  string n;
  for(int i = 0; i < N; i++) {
    cin >> n;
    str.push_back(n);
  }

  sort(str.begin(), str.end(),
    [](string a, string b) {
      for(int i = 0; i < a.size(); i++) {
        a[i] = tolower(a[i]);
      }
      for(int i = 0; i < b.size(); i++) {
        b[i] = tolower(b[i]);
      }
      return a < b;
  });

  for(const auto& i : str) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}

