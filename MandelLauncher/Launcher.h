#pragma once
#include "Header.h"

class launcher

{
public:

	int width, height, fullScreen, greyScale, startUp;
	double phase, scale, step, x, y;
	
	HWND *hwndptr;

	int setup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, launcher* ptr_);
	int getTextInt(HWND fnc);
	double getTextDouble(HWND fnc);
	void readConfig();
	void writeConfig();
	void save();
	void load();
	void setTextInt(HWND fnc, int i);
	void setTextDouble(HWND fnc, double value);
	void toCharArrI(char *arr, int i);
	void toCharArrD(char *arr, int i);

private:
	static HWND fnc1, fnc2, fnc3, fnc4, fnc5, fnc6, fnc7, fnc8, fnc9, fnc10, fnc11;
	static HWND fnc[11];
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static launcher* ptr;
};

