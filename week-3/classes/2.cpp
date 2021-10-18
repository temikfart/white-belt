#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        FirstName[year] = first_name;
        chng_first[true] = year;
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        LastName[year] = last_name;
        chng_last[true] = year;
    }
    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
        string fullname;
        bool has_first = false;
        int year_f = 0;
        if (chng_first.count(true) != 0) {
            has_first = chng_first[true] >= year;
            year_f = chng_first[true];
        }

        bool has_last = false;
        int year_l = 0;
        if (chng_last.count(true) != 0) {
            has_last = chng_last[true] >= year;
            year_l = chng_last[true];
        }

        switch (has_first + has_last) {
            case 0:
                fullname = "Incognito";
            case 1:
                if (has_first) {
                    fullname = FirstName[year_f] + " with unknown first name";
                } else {
                    fullname = LastName[year_l] + " with unknown last name";
                }
            case 2:
                fullname = FirstName[year_f] + LastName[year_l];
        }

        return fullname;
    }
private:
    // приватные поля
    map<int, string> FirstName;
    map<int, string> LastName;
    map<bool, int> chng_first;
    map<bool, int> chng_last;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}