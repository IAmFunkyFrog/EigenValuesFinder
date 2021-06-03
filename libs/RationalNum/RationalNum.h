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
    RationalNum(long long int numerator_, long long int denominator_ = 1);

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
   
    void setNumerator(long long int numerator_);
    int getNumerator() const;
    void setDenominator(long long int denominator_);
    int getDenominator() const;

  private:
    long long int numerator;
    long long int denominator;
    void simplify();
};
#endif
