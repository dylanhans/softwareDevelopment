
#include <iostream>
using namespace std;

#include "fraction.h"

FractionException::FractionException(const string& m) : message(m) {}

string& FractionException::what() {
	return message;
}

Fraction::Fraction(int t, int b) : top(t), bottom(b) {
	if (bottom == 0)
		throw FractionException("Denominator cannot be zero!");
    normalize();
}

Fraction::Fraction() : top(0), bottom(1) { }

Fraction::Fraction(int t) : top(t), bottom(1) { }

int Fraction::numerator() const {
    return top;
}

int Fraction::denominator() const {
    return bottom;
}

int Fraction::gcd(int n, int m) {
	if (m <= n && n % m == 0)
		return m;
	else if (n < m)
		return gcd(m, n);
	else
		return gcd(m, n % m);
}

void Fraction::normalize() {
   // Normalize fraction by
   // (a) moving sign to numerator
   // (b) ensuring numerator and denominator have no common divisors
   int sign = 1;
   if (top < 0) {
      sign = -1;
      top = -top;
   }
   if (bottom < 0) {
      sign = -sign;
      bottom = -bottom;
   }
   int d = 1;
   if (top > 0)
	   d = gcd(top, bottom);
   top = sign * (top / d);
   bottom = bottom / d;
}

Fraction operator+(const Fraction& left, const Fraction& right) {
   Fraction result(left.numerator() * right.denominator()
      + right.numerator() * left.denominator(),
      left.denominator() * right.denominator());
   return result;
}

Fraction operator-(const Fraction& left, const Fraction& right) {
   Fraction result(left.numerator() * right.denominator()
      - right.numerator() * left.denominator(),
      left.denominator() * right.denominator());
   return result;
}

Fraction operator*(const Fraction& left, const Fraction& right) {
   Fraction result(left.numerator() * right.numerator(),
      left.denominator() * right.denominator());
   return result;
}

Fraction operator/(const Fraction& left, const Fraction& right) {
   Fraction result(left.numerator() * right.denominator(),
      left.denominator() * right.numerator());
   return result;
}

Fraction operator-(const Fraction& value) {
   Fraction result(-value.numerator(), value.denominator());
   return result;
}

int Fraction::compare(const Fraction& right) const {
	// Return the numerator of the difference
   return top * right.denominator()
      - bottom * right.numerator();
}

bool operator<(const Fraction& left, const Fraction& right) {
   return left.compare(right) < 0;
}

bool operator<=(const Fraction& left, const Fraction& right) {
   return left.compare(right) <= 0;
}

bool operator==(const Fraction& left, const Fraction& right) {
   return left.compare(right) == 0;
}

bool operator!=(const Fraction& left, const Fraction& right) {
   return left.compare(right) != 0;
}

bool operator>=(const Fraction& left, const Fraction& right) {
   return left.compare(right) >= 0;
}

bool operator>(const Fraction& left, const Fraction& right) {
   return left.compare(right) > 0;
}

ostream& operator<<(ostream& out, const Fraction& value) {
   out << value.numerator() << "/" << value.denominator();
   return out;
}

istream& operator>>(istream& in, Fraction& retFrac) {
   int top, bottom;
   // Read the top
   in >> top;
   // If there is more than just an enter key, read the next number
   // after skipping the / sign.
   if (in.peek() != 10) {
	   char nextChar;
	   in >> nextChar;
	   if (nextChar == '/')
		  in >> bottom;
	   else
		   bottom = 1;
	   retFrac = Fraction(top, bottom);
   } else
	   retFrac = Fraction(top);
   return in;
}

Fraction& Fraction::operator++() {
   top += bottom;
   return *this;
}

Fraction Fraction::operator++(int unused) {
   Fraction clone(top, bottom);
   top += bottom;
   return clone;
}

Fraction& Fraction::operator+=(const Fraction& right) {
   top = top * right.denominator() + bottom * right.numerator();
   bottom *= right.denominator();
   normalize();
   return *this;
}
