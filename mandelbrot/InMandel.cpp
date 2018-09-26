#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
#include "MandelClass.h"

double inMandel(Complex c, int itterations)

{
	//Define complex numbers current and previous
	Complex zCur, zPrev;
	//Set zPrev to 0
	zPrev.set(0.0, 0.0);
	//Do z(n+1) = z(n)^2 + c where c is the value for each pixel on the screen.
	//Do this until the 
	for (int i = 0; i < itterations; i++)

	{
		zPrev.complexSquare();
		zCur.add(zPrev, c);
		zPrev = zCur;
		//Don't squareroot because it is slow
		if (zCur.re*zCur.re + zCur.im*zCur.im > 4.0)

		{
			//Return value between 0 and 1 for colour/greyscale
			return (i) / (double)(itterations - 1);
		}
	} 
	//Return 1 if it reaches the end of the itterations
	return 1.0;
}