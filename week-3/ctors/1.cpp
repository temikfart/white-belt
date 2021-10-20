#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ReversibleString {
public:
  ReversibleString() = default;
  explicit ReversibleString(const string& s) {
    data = s;
  }
  void Reverse() {
    reverse(data.begin(), data.end());
  }
  string ToString() const {
    return data;
  }
private:
  string data;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  return 0;
}