#include <iostream>
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

int main() {
  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a * b;
    bool equal = c == Rational(8, 9);
    if (!equal) {
      cout << "2/3 * 4/3 != 8/9" << endl;
      return 1;
    }
  }

  {
    Rational a(5, 4);
    Rational b(15, 8);
    Rational c = a / b;
    bool equal = c == Rational(2, 3);
    if (!equal) {
      cout << "5/4 / 15/8 != 2/3" << endl;
      return 2;
    }
  }

  cout << "OK" << endl;
  return 0;
}