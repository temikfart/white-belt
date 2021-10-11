#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int q;
  cin >> q;

  string cmd;

  map<string, vector<string>> routes;
  map<string, vector<string>> buses;

  string bus, stop;
  int stop_count;

  for (int i = 0; i < q; i++) {
    cin >> cmd;

    if (cmd == "NEW_BUS") {
      cin >> bus >> stop_count;

      for (int k = 0; k < stop_count; k++) {
        cin >> stop;

        routes[bus].push_back(stop);
        buses[stop].push_back(bus);
      }
    }
    if (cmd == "BUSES_FOR_STOP") {
      cin >> stop;

      if (buses.count(stop) == 0) {
        cout << "No stop" << endl;
        continue;
      }

      for (const auto& x : buses[stop]) {
        cout << x << " ";
      }
      cout << endl;
    }
    if (cmd == "STOPS_FOR_BUS") {
      cin >> bus;

      if (routes.count(bus) == 0) {
        cout << "No bus" << endl;
        continue;
      }

      for (const auto& s : routes[bus]) {
        cout << "Stop " << s << ":";
        if (buses[s].size() == 1) {
          cout << " no interchange" << endl;
          continue;
        }
        for (const auto& b : buses[s]) {
          if (b != bus) {
            cout << " " << b;
          }
        }
        cout << endl;
      }
    }
    if (cmd == "ALL_BUSES") {
      if (routes.empty() == 1) {
        cout << "No buses" << endl;
      }
      for (const auto& [key, value] : routes) {
        cout << "Bus " << key << ":";
        for (const auto& s : value) {
          cout << " " << s;
        }
        cout << endl;
      }
    }
  }

  return 0;
}