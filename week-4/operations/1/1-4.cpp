#include <iostream>
#include <sstream>
#include <numeric>
using namespace std;

class Rational {
public:
  Rational() {
    p = 0;
    q = 1;
  }

  Rational(int numerator, int denominator) {
    if (numerator == 0) {
      // 0/1
      p = numerator;
      q = 1;
    } else {
      // Правильность знаков
      if (numerator < 0 && denominator < 0) {
        numerator = abs(numerator);
        denominator = abs(denominator);
      } else if (denominator < 0) {
        denominator = abs(denominator);
        numerator = (-1) * numerator;
      }
      int gcd_num = gcd(abs(numerator), abs(denominator));
      if (gcd_num != 1) {
        numerator /= gcd_num;
        denominator /= gcd_num;
      }
      p = numerator;
      q = denominator;
    }
  }

  int Numerator() const {
    return p;
  }

  int Denominator() const {
    return q;
  }

private:
  int p;
  int q;
};

bool operator ==(Rational lhs, Rational rhs) {
  if (lhs.Numerator() != rhs.Numerator()) {
    return false;
  } else if (lhs.Denominator() != rhs.Denominator()) {
    return false;
  }
  return true;
}
Rational operator +(Rational lhs, Rational rhs) {
  int numerator = lhs.Numerator() * rhs.Denominator()
                  + rhs.Numerator() * lhs.Denominator();
  int denominator = lhs.Denominator() * rhs.Denominator();

  Rational res(numerator, denominator);
  return res;
}
Rational operator -(Rational lhs, Rational rhs) {
  int numerator = lhs.Numerator() * rhs.Denominator()
                  - rhs.Numerator() * lhs.Denominator();
  int denominator = lhs.Denominator() * rhs.Denominator();

  Rational res(numerator, denominator);
  return res;
}
Rational operator *(Rational lhs, Rational rhs) {
  Rational res(lhs.Numerator() * rhs.Numerator(),
               lhs.Denominator() * rhs.Denominator());
  return res;
}
Rational operator /(Rational lhs, Rational rhs) {
  Rational res(lhs.Numerator() * rhs.Denominator(),
               lhs.Denominator() * rhs.Numerator());
  return res;
}

istream& operator >>(istream& stream, Rational& r) {
  int numerator;
  int denominator;

  if (!(stream >> numerator)) {
    return stream;
  };

  char delim;
  if (!(stream >> delim) || delim != '/') {
    return stream;
  }

  stream >> denominator;

  if(denominator == 0) {
    return stream;
  }

  Rational res(numerator, denominator);
  r = res;

  return stream;
}
ostream& operator <<(ostream& stream, const Rational& r) {
  stream << r.Numerator() << "/" << r.Denominator();

  return stream;
}

int main() {
  {
    ostringstream output;
    output << Rational(-6, 8);
    if (output.str() != "-3/4") {
      cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
      return 1;
    }
  }

  {
    istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      cout << "5/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }

  {
    istringstream input("");
    Rational r;
    bool correct = !(input >> r);
    if (!correct) {
      cout << "Read from empty stream works incorrectly" << endl;
      return 3;
    }
  }

  {
    istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
      return 4;
    }

    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
      return 5;
    }
  }

  {
    istringstream input1("1*2"), input2("1/"), input3("/4");
    Rational r1, r2, r3;
    input1 >> r1;
    input2 >> r2;
    input3 >> r3;
    bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
    if (!correct) {
      cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
           << r1 << " " << r2 << " " << r3 << endl;

      return 6;
    }
  }

  cout << "OK" << endl;
  return 0;
}