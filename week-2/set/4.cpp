#include <iostream>
#include <set>
#include <map>

using namespace std;

int main() {
  int q, N;
  cin >> q;

  map<set<string>, int> routes;
  int routes_sz;
  for (int i = 0; i < q; i++) {
    cin >> N;

    set<string> stops;
    string stop;
    for(int k = 0; k < N; k++) {
      cin >> stop;
      stops.insert(stop);
    }

    if (routes.count(stops) == 0) {
      routes_sz = routes.size() + 1;
      routes[stops] = routes_sz;
      cout << "New bus " << routes_sz;
    } else {
      cout << "Already exists for " << routes[stops];
    }
    cout << endl;
  }
}