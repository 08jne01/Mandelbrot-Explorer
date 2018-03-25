#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <thread>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <condition_variable>
#include <mutex>

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

	complex zCur, zPrev;

	zPrev.re = 0.0;
	zPrev.im = 0.0;
	for (int i = 0; i < 1000; i++)

	{

		zPrev.complexSquare();
		zCur.add(zPrev, c);

		zPrev = zCur;

		//std::cout << z_prev.mag() << std::endl;

		if (zCur.re*zCur.re + zCur.im*zCur.im > 4.0)
			//z_cur.re >= 2.0 || z_cur.re <= -2.0 || z_cur.im >= 2.0 || z_cur.im <= -2.0

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
		std::condition_variable cv;
		std::vector<std::thread> threads;
		int numThreads = 70;
		double k = 2.0 / (order*scale*xRatio);
		int isDone = 0;
		int itterations = ceil(order*xRatio / (double)numThreads);
		int *ptr = &isDone;
	
		for (int i = 0; i < itterations; i++)

		{

			threads.push_back(std::thread([&]() { threadCalc(i, order, xRatio, yRatio, k, numThreads); }));

			progress = 100.0*(i*i*numThreads*numThreads) / (order*order*xRatio*xRatio);
			progress = round(progress);
			std::cout.precision(0);
			std::cout << "\rProgress:  " << progress << "% completed for res = " << order;
	
		}
		//std::cout << isDone << std::endl;

		//while (*ptr < order * xRatio / (double)threads)

		//{

			//std::cout << isDone << std::endl;

		//}

		for (int i = 0; i < itterations; i++)

		{

			threads[i].join();

		}
	

	}

private:
	
	void threadCalc(int i, int order, double xRatio, double yRatio, double k, int threads)

	{

		for (int n = 0; n < threads; n++)

		{

			if (i * threads + n < order*xRatio)

			{
				complex c;
				double color;
				int index = i * threads + n;
				std::vector<complex> buffer(order);
				std::vector<double> bufferColor(order);

				double x = xEdge + ((double)index * k);

				for (int j = 0; j < ceil(order*yRatio); j++)

				{


					c.set(x, yEdge + (double)j * k);


					color = inMandel(c);

					bufferColor[j] = color;
					buffer[j] = c;

				}

				cpx[index] = buffer;
				colorArr[index] = bufferColor;

			}

		}

	}

};


