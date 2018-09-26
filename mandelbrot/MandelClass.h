#pragma once
#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
//See MandelClass.cpp for comments

class mandelClass

{

public:

	std::vector<std::vector<Complex>> cpx;
	std::vector<std::vector<double>> colorArr;
	double xEdge;
	double yEdge;
	double scale;
	int size;

	void calcMandel(int order, double xRatio, double yRatio, int itters);

private:

	void threadCalc(int i, int order, double xRatio, double yRatio, double k, int threads, int itters);

};
