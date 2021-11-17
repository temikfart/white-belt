#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
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
bool operator ==(Rational lhs, Rational rhs) {
  if (lhs.Numerator() != rhs.Numerator()) {
    return false;
  } else if (lhs.Denominator() != rhs.Denominator()) {
    return false;
  }
  return true;
}
bool operator <(Rational lhs, Rational rhs) {
  if (lhs == rhs) {
    return false;
  }

  bool lhs_is_neg = lhs.Numerator() < 0;
  bool rhs_is_neg = rhs.Numerator() < 0;

  bool both_neg = lhs_is_neg && rhs_is_neg;
  bool diff_sign = (lhs_is_neg + rhs_is_neg) == 1;
  bool both_pos = !both_neg && !diff_sign;

  Rational res;

  // Если оба положительны
  if (both_pos) {
    res = rhs - lhs;
    return (res.Numerator() > 0);
  }

  Rational abs_lhs(abs(lhs.Numerator()), lhs.Denominator());
  Rational abs_rhs(abs(rhs.Numerator()), rhs.Denominator());

  // Если оба отрицательны
  if (both_neg) {
    res = abs_lhs - abs_rhs;
    return (res.Numerator() > 0);
  }
  // Если разные знаки
  if (diff_sign) {
    if (lhs_is_neg) {
      return true;
    } else {
      return false;
    }
  }
}
bool operator >(Rational lhs, Rational rhs) {
  return !(lhs < rhs);
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
  
  if (!(stream >> denominator)) {
    return stream;
  };
  
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
    const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    if (rs.size() != 3) {
      cout << "Wrong amount of items in the set" << endl;
      return 1;
    }

    vector<Rational> v;
    for (auto x : rs) {
      v.push_back(x);
    }
    if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
      cout << "Rationals comparison works incorrectly" << endl;
      return 2;
    }
  }

  {
    map<Rational, int> count;
    ++count[{1, 2}];
    ++count[{1, 2}];

    ++count[{2, 3}];

    if (count.size() != 2) {
      cout << "Wrong amount of items in the map" << endl;
      return 3;
    }
  }

  cout << "OK" << endl;
  return 0;
}
