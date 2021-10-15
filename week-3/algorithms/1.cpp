#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int N;
  vector<int> num;
  cin >> N;

  int n;
  for(int i = 0; i < N; i++) {
    cin >> n;
    num.push_back(n);
  }

  sort(num.begin(), num.end(), [](int x, int y) {return abs(x) < abs(y);});

  for(const auto& i : num) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}