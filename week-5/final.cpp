#include <iostream>
#include <exception>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Date {
public:
  Date() {
    year = 0;
    month = 1;
    day = 1;
  }
  Date(int new_year, int new_month, int new_day) {
    // Set year
    year = new_year;
    // Set month
    try {
      ValidateMonth(new_month);
    } catch (const invalid_argument& ex) {
      cout << ex.what() << endl;
    }
    month = new_month;
    // Set day
    try {
      ValidateDay(new_day);
    } catch (const invalid_argument& ex) {
      cout << ex.what() << endl;
    }
    day = new_day;
  }
//  string DateToStr() const {
//    string res = to_string(year) + "-"
//      + to_string(month) + "-"
//      + to_string(day);
//    return res;
//  }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
  
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
      vector<string>& v = db.at(date);
      if (find(begin(v), end(v), event) == end(v)) {
        db[date].push_back(event);
      }
    } else {
      db[date].push_back(event);
    }
  }
  bool DeleteEvent(const Date& date, const string& event) {
    if (db.count(date) > 0) {
      vector <string>& v = db.at(date);
      if (find(begin(v), end(v), event) != end(v)) {
        vector<string> tmp;
        for (const auto& ev : db.at(date)) {
          if (ev != event) {
            tmp.push_back(ev);
          }
        }
        db.erase(date);
        db[date] = tmp;
        cout << "Deleted successfully" << endl;
      } else {
        cout << "Event not found" << endl;
      }
    } else {
      cout << "Event not found" << endl;
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
        cout << setfill('0') << setw(4) << key.GetYear();
        cout << '-' << key.GetMonth()
             << '-' << key.GetDay() << ' ';
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

int main() {
  DateTest();
  DatabaseTest();
  
//  Database db;
//  map<string, int> cmds = {{"Add", 1},
//                           {"Del", 2},
//                           {"Find", 3},
//                           {"Print", 4}};
//
//  string command;
//  while (getline(cin, command)) {
//
//  }
  
  return 0;
}
