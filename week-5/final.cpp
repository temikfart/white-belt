#include <iostream>
#include <exception>
#include <map>

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
      throw invalid_argument("Month value is invalid: " + to_string(new_month));
    }
  }
  void ValidateDay(int new_day) {
    if (new_day < 1 || 31 < new_day) {
      throw invalid_argument("Day value is invalid: " + to_string(new_day));
    }
  }
  int year;
  int month;
  int day;
};

//bool operator<(const Date& lhs, const Date& rhs) {
//  if lhs
//}

//class Database {
//public:
//  void AddEvent(const Date& date, const string& event);
//  bool DeleteEvent(const Date& date, const string& event);
//  int  DeleteDate(const Date& date);
//
//  /* ??? */ Find(const Date& date) const;
//
//  void Print() const;
//};

void DateTest() {
  // Unit-tests for the class <Date>
  {
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
  }
}

int main() {
  DateTest();
//  Database db;
  
//  string command;
//  while (getline(cin, command)) {
//
//  }
  
  return 0;
}