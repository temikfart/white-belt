#include <iostream>
#include <exception>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctype.h>

using namespace std;

class Date {
public:
  Date() {
    year = 0;
    month = 1;
    day = 1;
  }
  Date(int new_year, int new_month, int new_day) {
    bool flag = true;
    
    // Set year
    year = new_year;
    // Set month
    SetMonth(new_month);
    // Set day
    SetDay(new_day);
  }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
  void SetYear(int new_year) {
    year = new_year;
  }
  void SetMonth(int new_month) {
    try {
      ValidateMonth(new_month);
    } catch (const invalid_argument& ex) {
      cout << ex.what() << endl;
      exit(0);
    }
    month = new_month;
  }
  void SetDay(int new_day) {
    try {
      ValidateDay(new_day);
    } catch (const invalid_argument& ex) {
      cout << ex.what() << endl;
      exit(0);
    }
    day = new_day;
  }
  void Print() const {
    cout << setfill('0') << setw(4) << year;
    cout << "-";
    cout << setfill('0') << setw(2) << month;
    cout << "-";
    cout << setfill('0') << setw(2) << day;
  };
  
private:
  void ValidateMonth(int new_month) {
    if (new_month < 1 || 12 < new_month) {
      throw invalid_argument("Month value is invalid: "
                             + to_string(new_month));
    }
  }
  void ValidateDay(int new_day) {
    if (new_day < 1 || 31 < new_day) {
      throw invalid_argument("Day value is invalid: "
                             + to_string(new_day));
    }
  }
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    int lhs_days = 31 * lhs.GetMonth() + lhs.GetDay();
    int rhs_days = 31 * rhs.GetMonth() + rhs.GetDay();
    return lhs_days < rhs_days;
  }
  return lhs.GetYear() < rhs.GetYear();
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    if (db.count(date) > 0) {
      vector<string> v;
      try {
        v = db.at(date);
      } catch (...) {}
      if (find(begin(v), end(v), event) == end(v)) {
        db[date].push_back(event);
      }
    } else {
      db[date].push_back(event);
    }
  }
  bool DeleteEvent(const Date& date, const string& event) {
    if (db.count(date) > 0) {
      vector <string> v;
      try {
        v = db.at(date);
      } catch(...) {}
      if (find(begin(v), end(v), event) != end(v)) {
        vector<string> tmp;
        for (const auto& ev : v) {
          if (ev != event) {
            tmp.push_back(ev);
          }
        }
        db.erase(date);
        db[date] = tmp;
        cout << "Deleted successfully" << endl;
        return true;
      } else {
        cout << "Event not found" << endl;
        return false;
      }
    } else {
      cout << "Event not found" << endl;
      return false;
    }
  }
  int DeleteDate(const Date& date) {
    int N = 0;
    if (db.count(date) > 0) {
      N = (int)(db[date].size());
      db.erase(date);
    }
    cout << "Deleted " << N << " events" << endl;
    return N;
  }
  void Find(const Date& date) const {
    if (db.count(date) > 0) {
      vector<string> v = db.at(date);
      sort(begin(v), end(v));
      
      for (const auto& str : v) {
        cout << str << endl;
      }
    }
  }
  void Print() const {
    for (const auto& [key, value] : db) {
      // Print events
      vector<string> v = value;
      sort(begin(v), end(v));
      for (const auto& str : v) {
        // Print date:
        key.Print();
        cout << " ";
        // Print event
        cout << str << endl;
      }
    }
  }

private:
  map<Date, vector<string>> db;
};

void DateTest() {
  // Unit-tests for the class <Date>
  { // Default ctor test
    try {
      Date d1;
      if (d1.GetYear() != 0) {
        cout << "Default ctor create date with incorrect year." << endl;
        exit(1);
      }
      if (d1.GetMonth() != 1) {
        cout << "Default ctor create date with incorrect month." << endl;
        exit(1);
      }
      if (d1.GetDay() != 1) {
        cout << "Default ctor create date with incorrect day." << endl;
        exit(1);
      }
    } catch (exception & ex) {
      cout << "An exception is thrown on correct input" << endl;
      exit(1);
    }
  }
  
  { // Ctor test
    try { // Correct year
      Date d1(-1, 1, 1);
      Date d2(0, 1, 1);
      Date d3(1, 1, 1);
    } catch (exception & ex) {
      cout << "An exception is thrown on correct input (year)." << endl;
      exit(1);
    }
    
    // Incorrect month
    {
      cout << endl << "Expecting: Invalid month exception." << endl;
      Date d1(0, -1, 1);
    }
    
    {
      cout << endl << "Expecting: Invalid month exception." << endl;
      Date d2(0, 55, 1);
    }
    
    // Incorrect day
    {
      cout << endl << "Expecting: Invalid day exception." << endl;
      Date d1(0, 1, -10);
    }
    
    {
      cout << endl << "Expecting: Invalid day exception." << endl;
      Date d2(0, 1, 32);
    }
  }
  // Operator < for the Date class tests
  {
    // Different years, same months and days
    if ( !(Date(1, 1, 1) < Date(2, 1, 1)) ) {
      cout << "Expected, that 1.1.1 < 2.1.1" << endl;
    }
    // Different years, months and days
    if ( !(Date(1, 12, 5) < Date(2, 10, 4)) ) {
      cout << "Expected, that 1.12.5 < 2.10.5" << endl;
    }
    // Comparing with negative year
    if ( !(Date(-1, 1, 1) < Date(0, 1, 1)) ) {
      cout << "Expected, that -1.1.1 < 0.1.1" << endl;
    }
    // Same years, different months and days
    if ( !(Date(1, 7, 5) < Date(1, 9, 13)) ) {
      cout << "Expected, that 1.7.5 < 1.9.13" << endl;
    }
    if ( !(Date(1, 1, 12) < Date(1, 1, 15)) ) {
      cout << "Expected, that 1.1.12 < 1.1.15" << endl;
    }
  }
}
void DatabaseTest() {
  // Unit-tests for the class <Database>
  {
    cout << endl << "Expecting: only two strings <Merry christmas>." << endl;
  
    Database db;
    db.Find(Date(0, 1, 1));
    db.AddEvent(Date(0, 1, 1), "Merry Christmas");
    db.Find(Date(0, 1, 1));
    db.Find(Date(0, 1, 1));
  }
  
  {
    Database db;
    
    cout << endl << "Expecting: 5 strings with some events as sort list." << endl;
    db.AddEvent(Date(0, 1, 1), "Session");
    db.AddEvent(Date(0, 1, 1), "Merry Christmas");
    db.AddEvent(Date(0, 5, 1), "Peace. Work. May.");
    db.AddEvent(Date(2021, 9, 1), "Day of knowledge");
    db.AddEvent(Date(2020, 3, 16), "Coronavirus");
    db.Print();
    
    cout << endl << "Expecting: message about 3 deleted events. "
                    "And print of event <Coronavirus> and <Peace. Work. May.>." << endl;
    db.DeleteDate(Date(2021, 9, 1));
    db.DeleteDate(Date(0, 1, 1));
    db.Print();
    
    cout << endl << "Expecting: 2 messages about 0 deleted events. "
                    "And print of event <Coronavirus>"
                    "and <Peace. Work. May.>." << endl;
    db.DeleteDate(Date(100500, 1, 2));
    db.DeleteDate(Date(100500, 1, 4));
    db.Print();
    
    cout << endl << "Expecting: 6 events." << endl;
    db.AddEvent(Date(0, 5, 5), "Maxim's birthday");
    db.AddEvent(Date(0, 5, 5), "Anton's birthday");
    db.AddEvent(Date(0, 5, 5), "Elena's birthday");
    db.AddEvent(Date(0, 5, 5), "Adil's birthday");
    db.Print();
    
    cout << endl << "Expecting: 2 messages <Event not found>, "
                    "then 1 message <Deleted successfully>" << endl;
    db.DeleteEvent(Date(0, 5, 6), "Anton's birthday");
    db.DeleteEvent(Date(0, 5, 5), "Artyom's birthday");
    db.DeleteEvent(Date(0, 5, 5), "Anton's birthday");
    
    cout << endl << "Expecting: print 5 events." << endl;
    db.Print();
  }
}

void EnsureNextSymbolAndSkip(stringstream& stream) {
  if (stream.peek() != '-') {
    throw invalid_argument("Wrong date format: ");
  }
  stream.ignore(1);
}
void EnsureEmptyStream(stringstream& stream) {
  if (stream.peek() != EOF) {
    throw invalid_argument("Wrong date format: ");
  }
}
int EnsureDigit(string& s) {
//  cout << s[0];
  if (isdigit(s[0]) != 0) {           // Если число, тогда считываем
    int day;
    stringstream input(s);
    input >> day;
    EnsureEmptyStream(input);
    return day;
  } else {
    throw invalid_argument("Wrong date format: ");
  }
}
int EnsureCorrectDay(stringstream& stream) {
  string s;
  stream >> s;
  
  int day;
  
  if (s[0] != '-' && s[0] != '+') {     // Если не - или +, тогда число?
    day = EnsureDigit(s);
  } else {                              // Если - или +, тогда проверяем дальше
    stringstream input(s);
    if (isdigit(s[1]) == 0) {
      throw invalid_argument("Wrong date format: ");
    } else {
      input >> day;
      EnsureEmptyStream(input);
    }
  }
  return day;
}

Date StrToDate(string& s) {
  int year, month, day;
  
  stringstream stream(s);
  try {
    stream >> year;
    EnsureNextSymbolAndSkip(stream);
    stream >> month;
//    cout << month << " " << stream.peek() << endl;          // Debug
    EnsureNextSymbolAndSkip(stream);
    day = EnsureCorrectDay(stream);
    EnsureEmptyStream(stream);
//    cout << day << " " << (stream.peek() == EOF) << endl;   // Debug
    Date date(year, month, day);
    return date;
  } catch(const invalid_argument& ex) {
    cout << ex.what() << s << endl;
    exit(1);
  }
}

int main() {
//  DateTest();
//  DatabaseTest();
  
  Database db;
  map<string, int> cmds = {{"Add", 1},
                           {"Del", 2},
                           {"Find", 3},
                           {"Print", 4}};

  string command;
  while (getline(cin, command)) {
    string cmd, event, date_str;
    int i = 0;
    
    for (const auto& x : command) {
//      cout << "(" << i << ")-" << x << ".";
      if (x == ' ' || x == '\n') {
        i++;
        continue;
      }
      switch(i) {
        case 0:
          cmd += x;
          break;
        case 1:
          date_str += x;
          break;
        case 2:
          event += x;
          break;
        default:
          cout << "Something went wrong with scan" << endl;
      }
    }
//    cout << endl;
    if (cmd.empty() == 1) {
      continue;
    } else if(cmds.count(cmd) < 1) {
      cout << "Unknown command: " << cmd << endl;
      exit(1);
    }
    
    
    Date date;
    if (date_str.empty() == 0) {
      date = StrToDate(date_str);
    }
    
//    bool empty = cmd.empty();
//    cout << cmd << empty << cmd[cmd.size()-1] << cmd.size() << " ";
//    date.Print();
//    cout << " " << event << endl;
  
    switch(cmds[cmd]) {
      case 1:
        db.AddEvent(date, event);
        break;
      case 2:
        if (event.empty() == 0) {
          db.DeleteEvent(date, event);
        } else {
          db.DeleteDate(date);
        }
        break;
      case 3:
        db.Find(date);
        break;
      case 4:
        db.Print();
        break;
      default:
        cout << "Something went wrong with db" << endl;
        break;
    }
  }
  
  return 0;
}
