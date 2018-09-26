#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
#include "MandelClass.h"



void Complex::set(double a, double b)

{
	//Set real and imaginary
	re = a;
	im = b;
}

double Complex::mag()

{
	//Returns the magnitude
	return (sqrt(re*re + im * im));
}

double Complex::arg()

{
	//Returns argument
	double atan(im / re);
}

void Complex::complexSquare()

{
	//Sets this complex number square of this number
	double a = re;
	double b = im;

	re = (a * a) - (b * b);
	im = 2.0 * (a*b);
}

void Complex::add(Complex r, Complex g)

{
	//Sets this complex number to the addition of r and g
	re = r.re + g.re;
	im = r.im + g.im;
}