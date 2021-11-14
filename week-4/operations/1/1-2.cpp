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

int main() {
  {
    Rational r1(4, 6);
    Rational r2(2, 3);
    bool equal = r1 == r2;
    if (!equal) {
      cout << "4/6 != 2/3" << endl;
      return 1;
    }
  }

  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a + b;
    bool equal = c == Rational(2, 1);
    if (!equal) {
      cout << "2/3 + 4/3 != 2" << endl;
      return 2;
    }
  }

  {
    Rational a(5, 7);
    Rational b(2, 9);
    Rational c = a - b;
    bool equal = c == Rational(31, 63);
    if (!equal) {
      cout << "5/7 - 2/9 != 31/63" << endl;
      return 3;
    }
  }

  cout << "OK" << endl;
  return 0;
}
