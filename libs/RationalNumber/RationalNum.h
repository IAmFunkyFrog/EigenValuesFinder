#ifndef RATIONAL_NUM
#define RATIONAL_NUM

#include <iostream>
using namespace std;

class RationalNum {
  friend RationalNum operator+(const RationalNum& left, const RationalNum& right);
  friend RationalNum operator-(const RationalNum& left, const RationalNum& right);
  friend RationalNum operator*(const RationalNum& left, const RationalNum& right);
  friend RationalNum operator/(const RationalNum& left, const RationalNum& right);
  friend bool operator==(const RationalNum& left, const RationalNum& right);
  friend bool operator!=(const RationalNum& left, const RationalNum& right);
  friend bool operator<(const RationalNum& left, const RationalNum& right);
  friend bool operator>(const RationalNum& left, const RationalNum& right);
  friend bool operator<=(const RationalNum& left, const RationalNum& right);
  friend bool operator>=(const RationalNum& left, const RationalNum& right);
  friend ostream& operator<<(ostream& out, const RationalNum& obj);
  friend istream& operator>>(istream& in, RationalNum& obj);
  
  public:
    RationalNum();
    RationalNum(double x);
    RationalNum(int numerator_, int denominator_ = 1);

    RationalNum& operator=(const RationalNum& obj);
    RationalNum& operator+=(const RationalNum& obj);
    RationalNum& operator-=(const RationalNum& obj);
    RationalNum& operator*=(const RationalNum& obj);
    RationalNum& operator/=(const RationalNum& obj);
    RationalNum& operator++();
    RationalNum operator++(int);
    RationalNum& operator--();
    RationalNum operator--(int);
    RationalNum operator+() const;
    RationalNum operator-() const;
   
    void setNumerator(int numerator_);
    int getNumerator() const;
    void setDenominator(int denominator_);
    int getDenominator() const;

  private:
    int numerator;
    int denominator;
    void simplify();
};
#endif
