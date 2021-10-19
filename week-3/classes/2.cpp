#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
    names[year].first_name = first_name;
    changes[year].first = true;
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
    names[year].last_name = last_name;
    changes[year].last = true;
  }
  string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year

    // has part of name
    int first_y, last_y;
    first_y = -1;
    last_y = -1;
    for (const auto& [key, value] : changes) {
      if (key <= year) {
        if (value.first) {
          first_y = key;
        }
        if (value.last) {
          last_y = key;
        }
      }
    }

    string part;
    if (first_y == -1 && last_y == -1) {
      return "Incognito";
    }
    if (first_y == -1) {
      part = names[last_y].last_name + " with unknown first name";
      return part;
    }
    if (last_y == -1) {
      part = names[first_y].first_name + " with unknown last name";
      return part;
    }


    // has fullname
    string fullname;
    fullname = names[first_y].first_name + " " + names[last_y].last_name;
    return fullname;
  }
private:
  // приватные поля
  struct name {
    string first_name;
    string last_name;
  };
  struct has_chng {
    bool first;
    bool last;
  };
  map<int, name> names;
  map<int, has_chng> changes;
};

int main() {
  Person Person;

  Person.ChangeFirstName(65, "p");
  Person.ChangeLastName(69, "s");
  Person.ChangeFirstName(70, "a");
  cout << Person.GetFullName(66) << endl;

  return 0;
}