#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Student {
  string name;
  string surname;
  int day;
  int month;
  int year;
};

void GetData(map<int, Student>& students) {
  int n;
  cin >> n;

  Student st;

  for (int i = 1; i <= n; i++) {
    getline(cin, st.name, ' ');
    if (st.name[0] == '\n') {
      st.name.erase(0,1);
    }
    getline(cin, st.surname, ' ');

    cin >> st.day >> st.month >> st.year;

    students[i] = st;
  }
}

void BadRequest() {
  cout << "bad request" << endl;
}

void Request(map<int, Student>& students, string& req, int value) {
  if (value > students.size() || value < 1) {
    BadRequest();
    return;
  }
  if (req == "name") {
    cout << students[value].name << " " << students[value].surname << endl;
  } else if (req == "date") {
    cout << students[value].day << "."
          << students[value].month << "."
          << students[value].year << endl;
  } else {
    BadRequest();
    return;
  }
}

int main() {
  map<int, Student> students;

  GetData(students);

  int m;
  cin >> m;
  string request;
  int value;
  for (int i = 0; i < m; i++) {
    cin >> request >> value;
    Request(students, request, value);
  }

  return 0;
}