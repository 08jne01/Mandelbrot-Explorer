#pragma once
#include "Header.h"
//See Complex.cpp for comments
class Complex

{

public:
	double re;
	double im;

	void set(double a, double b);
	void complexSquare();
	void add(Complex r, Complex g);
	double mag();
	double arg();

};