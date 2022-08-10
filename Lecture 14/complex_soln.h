#include <iostream>
using std::istream;
using std::ostream;

class Complex {
public:
  Complex(double x=0, double y=0) : real_(x), imag_(y) {}  // default constructor
  Complex(Complex const& old) : real_(old.real_), imag_(old.imag_) {}  // copy constructor
  Complex& operator= (Complex const& rhs); // Assignment operator
  double Real() const { return real_; }
  void SetReal(double x) { real_ = x; }
  double Imaginary() const { return imag_; }
  void SetImaginary(double y) { imag_ = y; }
  double Magnitude() const { return sqrt(real_*real_ + imag_*imag_); }
  Complex operator+ (Complex const& rhs) const;  
  Complex operator- () const; // unary operator- negates a complex number

  Complex& operator+= (const Complex& rhs);
  
  // Input and output stream operators can not be member functions.  They can be friends, 
  // or they can be non-member functions if their work can be accomplished through the 
  // public interface to the class.  Note that the complex object passed to the istream 
  // (>>) operator MUST be passed as a non-const reference.
  friend istream& operator>> (istream& istr, Complex& c);
private:
  double real_, imag_;
};

Complex operator- (Complex const& left, Complex const& right); // non-member function
ostream& operator<< (ostream& ostr, const Complex& c);  // non-member function

////

Complex z,w;

std::cout << -z << std::endl;
std::cout << z.operator-() << std::endl;

std::cout << z-w << std::endl;
//std::cout << z.operator-(w) << std::endl;
std::cout << operator-(z,w) << std::endl;

std::cout << z+w << std::endl;
std::cout << z.operator+(w) << std::endl;
//std::cout << operator+(z,w) << std::endl;

std::cin >> z;
std::cin.operator>>(z);

std::cin >> z >> w;
std::cin.operator>>(z).operator>>(w);
std::cin >> z;
std::cin >> w;
std::cin.operator>>(z);
std::cin.operator>>(w);

Complex x;
// (z+w)+x   <---
// z + (w+x)
std::cout << z+w+x << std::endl;
std::cout << z.operator+(w).operator+(x) << std::endl;
std::cout << Complex(z.real_ + w.real_, z.imag_ + w.imag_).operator+(x) << std::endl;

z = w = x;
z.operator=(w.operator=(x))

Complex Complex::operator+ (const Complex& rhs) const; <----
z.operator+(w); //Example call
// ^^^^ Can this access w's private members/functions? ^^^

z = Complex(3,5); // 3 + 5i;
z++; // What would be the right result?    4 + 5i?  3 + 6i?    5.41 + 6.41i

