#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<string> bus_seq;

void BusesForStop(map<string, vector<string>>& m, string stop) {
  bool flag = false;
  for (const auto& [key, value] : m) {
    for (int i = 0; i < value.size(); i++) {
      if (m[key][i] == stop) {
        flag = true;
        cout << key << " ";
      }
    }
  }
  if (flag == false) {
    cout << "No stop";
  }
  cout << endl;
}
bool FindBuses(map<string, vector<string>>& m, string& bus, string& stop) {
  bool has_buses = false;
  for (const auto& next_bus : bus_seq) {
    if (next_bus == bus) {
      continue;
    }
    for (int k = 0; k < m[next_bus].size(); k++) {
      if (m[next_bus][k] == stop) {
        if (has_buses == false) {
          has_buses = true;
        }
        cout << " " << next_bus;
      }
    }
  }
  return has_buses;
}
void StopsForBus(map<string, vector<string>>& m, string& bus) {
  if (m.count(bus) == 0) {
    cout << "No bus" << endl;
    return;
  }
  bool has_buses = false;
  // Find buses going through stop m[bus][i]
  for (int i = 0; i < m[bus].size(); i++) {
    cout << "Stop " << m[bus][i] << ":";
    has_buses = FindBuses(m, bus, m[bus][i]);
    if(has_buses == false) {
      cout << " no interchange";
    }
    cout << endl;
  }
}
void PrintStops(map<string, vector<string>>& m) {
  if (m.empty() == 1) {
    cout << "No buses" << endl;
    return;
  }
  for (const auto& [key, value] : m) {
    cout << "Bus " << key << ":";
    for (int i = 0; i < value.size(); i++) {
      cout << " " << value[i];
    }
    cout << endl;
  }
}

int main() {
  int q;
  cin >> q;

  string cmd;
  map<string, vector<string>> routes;
  string bus, stop;
  int stop_count;
  for (int i = 0; i < q; i++) {
    cin >> cmd;

    if (cmd == "NEW_BUS") {
      cin >> bus >> stop_count;
      bus_seq.push_back(bus);
      for (int k = 0; k < stop_count; k++) {
        cin >> stop;
        routes[bus].push_back(stop);
      }
    }
    if (cmd == "BUSES_FOR_STOP") {
      cin >> stop;
      BusesForStop(routes, stop);
    }
    if (cmd == "STOPS_FOR_BUS") {
      cin >> bus;
      StopsForBus(routes, bus);
    }
    if (cmd == "ALL_BUSES") {
      PrintStops(routes);
    }
  }
  for (int i = 0; i < bus_seq.size(); i++) {
    cout << bus_seq[i] << " ";
  }
  cout << endl;

  return 0;
}