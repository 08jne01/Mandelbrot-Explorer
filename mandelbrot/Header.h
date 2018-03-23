#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <thread>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>

#define PI 3.14159


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

class mandelClass

{

public:
		
	std::vector<std::vector<complex>> cpx;
	std::vector<std::vector<double>> colorArr;
	double xEdge;
	double yEdge;
	double scale;
	int size;

	void calcMandel(int order, double xRatio, double yRatio)

	{
		double progress;
		double k = 2.0 / (order*scale*xRatio);
	
		for (int i = 0; i < ceil(order*xRatio); i++)

		{
			
			std::thread mCalc

			{

				[&]()

					{

						threadCalc(i, order, xRatio, yRatio, k);

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

			progress = 100.0*(i*i) / (order*order*xRatio);
			progress = round(progress);
			std::cout.precision(0);
			std::cout << "\rProgress:  " << progress << "% completed for res = " << order*xRatio;
	
		}

	}

private:
	
	void threadCalc(int i, int order, double xRatio, double yRatio, double k)

	{
		complex c;
		double color;
		std::vector<complex> buffer(order);
		std::vector<double> bufferColor(order);

		double x = xEdge + ((double)i * k);

		for (int j = 0; j < ceil(order*yRatio); j++)

		{


			c.set(x, yEdge + (double)j * k);


			color = inMandel(c);

			bufferColor[j] = color;
			buffer[j] = c;

		}

		cpx[i] = buffer;
		colorArr[i] = bufferColor;

	}

};


