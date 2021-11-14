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

int main() {
  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      cout << "Rational(3, 10) != 3/10" << endl;
      return 1;
    }
  }

  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(8, 12) != 2/3" << endl;
      return 2;
    }
  }

  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(-4, 6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(4, -6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      cout << "Rational(0, 15) != 0/1" << endl;
      return 4;
    }
  }

  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
      cout << "Rational() != 0/1" << endl;
      return 5;
    }
  }

  cout << "OK" << endl;
  return 0;
}
