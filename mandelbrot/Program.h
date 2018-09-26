#pragma once
#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
#include "MandelClass.h"
#include "CallBack.h"
//See Program.cpp for comments
class program

{

private:

	double step;
	double ratio;
	double phase;
	double xRatio;
	double yRatio;
	double x;
	double y;
	double scale;
	int greyScale;
	int res;
	int calculated;
	int itters;
	float phaseincrease;

public:

	mandelClass mandel;

	double xCurs;
	double yCurs;
	double pointSize;
	int width;
	int height;
	int fullScreen;

	void init(int width_, int height_, double step_, double x_, double y_, double scale_, double greyScale_, double phase_, int fullScreen_);
	void checkRatio();
	void update(double local_step, int init);
	void draw();
	void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	void keyCallBack(int key, int pressed);
	void readConfig();
	void writeConfig();
	void saveBMP(std::string filename);
	void writeCoords(std::string s);
	double coordTransform(double pixel, int dimension);
	int roundDownNearest(int val, int multiple);
	std::string currentTime();

};