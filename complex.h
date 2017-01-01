// --------------------------------------------------------
// COMPLEX NUMBER IMPL.
//
// Motivation: Portability
//
// Copyright 2016 Gautr Systems AB
// http://www.github.com/joastbg 
// --------------------------------------------------------

#ifndef COMPLEX_H
#define COMPLEX_H

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

template <typename T>
class Complex;

template <typename T>
std::ostream& operator<< (std::ostream&, Complex<T>&);

template <typename T>
class Complex {
public:
	Complex() : re(0), im(0) {}
    Complex(T real, T imag) : re(real), im(imag) { }
	
    union {
		struct {
		T re;
		T im;
		};
		T cr[2];
	};        
	
    friend std::ostream& operator<< <>(std::ostream&, Complex<T>&);
    
    const std::string str() { 
        std::stringstream ss;
        
        ss << re;
        ss << (im < 0 ? " - " : " + ");        
        ss << std::abs(im);
        ss << "i";
        
        return ss.str();
    }
    
    // arithmetic operators
	inline Complex operator+(const Complex& b) const { return Complex(re + b.re, im + b.im); }
	inline Complex operator-(const Complex& b) const { return Complex(re - b.re, im - b.im); }
    
    // conjugate
    inline Complex operator-() const { return Complex(re, -im); }
    
    // absolute value & argument
	inline double abs() const { return sqrt(re*re + im*im); }
    inline double arg() const { return std::atan2(im, re); }
    
private:
    
};

template <typename T>
std::ostream& operator<< (std::ostream& out, Complex<T>& c) {	
	out << "-- Complex :: " << c.str() << std::endl;	
	return out;
}

#endif