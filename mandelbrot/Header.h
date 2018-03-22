#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <thread>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>

#define pi 3.14159


class complex

{

public:
	double re;
	double im;

	void set(double a, double b)

	{
	
		re = a;
		im = b;

	}

	double mag()
	
	{

		return (sqrt(re*re + im * im));

	}

	double arg()

	{

		double atan(im / re);

	}

	void complexSquare()

	{
		double a = re;
		double b = im;

		re = (a * a) - (b * b);
		im = 2.0 * (a*b);

	}

	void add(complex r, complex g)

	{

		re = r.re + g.re;
		im = r.im + g.im;

	}

};

double inMandel(complex c)

{

	complex z_cur, z_prev;

	z_prev.re = 0.0;
	z_prev.im = 0.0;
	for (int i = 0; i < 1000; i++)

	{

		z_prev.complexSquare();
		z_cur.add(z_prev, c);

		z_prev = z_cur;

		//std::cout << z_prev.mag() << std::endl;

		if (z_cur.re >= 2.0 || z_cur.re <= -2.0 || z_cur.im >= 2.0 || z_cur.im <= -2.0)

		{

			return (i) / (double)999.0;

		}

	}

	return 1.0;

}

class mandel_class

{

public:
		
	std::vector<std::vector<complex>> cpx;
	std::vector<std::vector<double>> colorArr;
	double edgex;
	double edgey;
	double scale;
	int size;

	void calcMandel(int order, double ratio)

	{
		double progress;
		double k = 2.0 / (order*scale);
	
		for (int i = 0; i < order; i++)

		{
			
			std::thread mCalc

			{

				[&]()

					{

						threadCalc(i, order, ratio, k);

					}

			};

			if (i < 2000)

			{

				mCalc.detach();

			}

			else

			{

				mCalc.join();

			}

			progress = 100.0*(i*i) / (order*order);
			progress = round(progress);
			std::cout.precision(0);
			std::cout << "\rProgress:  " << progress << "% completed for res = " << order;
	
		}

	}

private:
	
	void threadCalc(int i, int order, double ratio, double k)

	{
		complex c;
		double color;
		std::vector<complex> buffer(order);
		std::vector<double> bufcol(order);

		double x0 = edgex + ((double)i * k);

		for (int j = 0; j < ceil(order*ratio); j++)

		{


			c.set(x0, edgey + (double)j * k);


			color = inMandel(c);

			bufcol[j] = color;
			buffer[j] = c;

		}

		cpx[i] = buffer;
		colorArr[i] = bufcol;

	}

};


