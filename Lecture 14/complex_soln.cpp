#include <cmath>
#include "complex.h"

/*
(a + b) + c;

a = (b = c);

a = a + b;
a += b;   ===>   a.operator+=(b);

c = (a += b);
or... (not equivalent)
c += (a += b);
*/



// Assignment operator
Complex& Complex::operator= (Complex const& rhs) {
  real_ = rhs.real_;
  imag_ = rhs.imag_;
  return *this;
}




// Addition operator as a member function.
Complex Complex::operator+ (const Complex& rhs) const {
  double re = this->real_ + rhs.real_;
  double im = this->imag_ + rhs.imag_;
  return Complex(re, im);
}

//Complex& Complex::operator+= (Complex const& rhs) {
Complex& Complex::operator+= (const Complex& rhs) {
  //return *this=(*this+rhs);
  //return *this = (*this.operator+(rhs))
  //return *this.operator=(*this.operator+(rhs))
  this->real_ += rhs.real_;
  //this->real_ = this->real_ + rhs.real_;
  this->imag_ += rhs.imag_;
  return *this;
}




// Subtraction operator as a non-member function.
Complex operator- (Complex const& lhs, Complex const& rhs) {
  return Complex(lhs.Real()-rhs.Real(), lhs.Imaginary()-rhs.Imaginary());
}

// Unary negation operator.  Note that there are no arguments.
Complex Complex::operator- () const {
  return Complex(-real_, -imag_);
}

// Input stream operator as a friend function
istream& operator>> (istream & istr, Complex & c) {
  istr >> c.real_ >> c.imag_;
  return istr;
}

// Output stream operator as an ordinary non-member function
ostream& operator<< (ostream & ostr, Complex const& c) {
  if (c.Imaginary() < 0)  ostr << c.Real() << " - " << -c.Imaginary() << " i ";
  else                    ostr << c.Real() << " + " << c.Imaginary() << " i ";
  return ostr;
}
