#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}
string MakeFullName(const string& name, vector<string>& history, const string& msg) {
  string fullname = name;

  // History
  string hist = " (";
  bool is_first = true;
  for (const auto& x : history) {
    if (is_first == true) {
      hist += x;
      is_first = false;
    } else {
      hist += ", " + x;
    }
  }

  // Fullname
  if (history.empty() == true) {
    fullname += msg;
  } else {
    fullname += hist + ")" + msg;
  }

  return fullname;
}
vector<string> GetHistory(map<int, string>& names, int year) {
  vector<string> h;
  string last;

  // x double
  // x >= year
  // x if h.last == names[year] ==> pop_back
  bool is_first = true;
  for (const auto& [key, value] : names) {
    if (key <= year) {
      if (is_first == true) {
        is_first = false;
        h.push_back(value);
        last = value;
      } else {
        if (value == last) {
          continue;
        }
        h.push_back(value);
        last = value;
      }
    } else {
      break;
    }
  }

  bool cond_1 = (h.size() > 1) && (names.count(year) != 0);
  bool cond_2 = (h.empty() == false);
  if (cond_1) {
    h.pop_back();
  } else if (cond_2) {
    bool cond_3 = (FindNameByYear(names, year) == h[h.size()-1]);
    if (cond_3) {
      h.pop_back();
    }
  }
  reverse(h.begin(), h.end());

  return h;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

      // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

      // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

      // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }
  string GetFullNameWithHistory(int year) {
    // получить все имена и фамилии по состоянию на конец года year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    vector<string> hist_first = GetHistory(first_names, year);
    vector<string> hist_last = GetHistory(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

      // если неизвестно только имя
    } else if (first_name.empty()) {
      return MakeFullName(last_name,
                          hist_last,
                          " with unknown first name");

      // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return MakeFullName(first_name,
                          hist_first,
                          " with unknown last name");

      // если известны и имя, и фамилия
    } else {
      return MakeFullName(first_name, hist_first, " ")
        + MakeFullName(last_name, hist_last, "");
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

int main(){
  return 0;
}

