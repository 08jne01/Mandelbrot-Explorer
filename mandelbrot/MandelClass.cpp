#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
#include "MandelClass.h"


void mandelClass::calcMandel(int order, double xRatio, double yRatio, int itters)

{
	//Set some values for the mandelbrot
	size = order;
	colorArr.resize(order*order);
	cpx.resize(order*order);
	//Experimentation showed that dividing the width by 70 gives best speed ~20 threads for 
	int threadVal = 70;
	//Some calculation that can be done outside of the loop
	double k = 2.0 / (order*scale*xRatio);
	int maxThreads = ceil(order*xRatio / (double)threadVal);
	//Create vector of threads
	std::vector<std::thread> threads;
	double progress;

	for (int i = 0; i < maxThreads; i++)

	{
		//Push a thread for the number of threads calculated (changes based on resolution)
		threads.push_back(std::thread([&]() { threadCalc(i, order, xRatio, yRatio, k, threadVal, itters); }));
		//Calculate progress and display on the console
		progress = 100.0*(i*i*threadVal*threadVal) / (order*order*xRatio*xRatio);
		progress = round(progress);
		std::cout.precision(0);
		std::cout << "\rProgress:  " << progress << "% completed for res = " << order;
	}

	for (int i = 0; i < maxThreads; i++)

	{
		//Join the threads back
		threads[i].join();
	}
}

void mandelClass::threadCalc(int i, int order, double xRatio, double yRatio, double k, int threads, int itters)

{

	for (int n = 0; n < threads; n++)

	{
		//Itterate through a block size determained by the number of threads
		if (i * threads + n < order*xRatio)

		{
			Complex c;
			double color;
			//Start index at certain point to do screen in chunks
			int index = i * threads + n;
			//Create buffer so that there isn't an access violation
			std::vector<Complex> buffer(order);
			std::vector<double> bufferColor(order);

			double x = xEdge + ((double)index * k);
			//Calculate the vertical and load into buffer
			for (int j = 0; j < ceil(order*yRatio); j++)

			{
				c.set(x, yEdge + (double)j * k);
				color = inMandel(c, itters);
				bufferColor[j] = color;
				buffer[j] = c;
			}
			//Set the buffer to the appropriate index on the
			//Since cpx and colorArr are vectors and the data is carefully split there will not be an access violation even with ~20 threads writing to cpx and colorArr
			cpx[index] = buffer;
			colorArr[index] = bufferColor;
		}
	}
}
