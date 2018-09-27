#pragma once
#include "Header.h"

class launcher

{
public:

	int width, height, fullScreen, greyScale, startUp;
	double phase, scale, step, x, y;
	
	HWND *hwndptr;
	HWND hwnd;

	int setup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, launcher* ptr_);
	int getTextInt(HWND fnc);
	double getTextDouble(HWND fnc);
	int readConfig();
	int writeConfig();
	int save();
	int load();
	void setTextInt(HWND fnc, int i);
	void setTextDouble(HWND fnc, double value);
	void toCharArrI(char *arr, int i);
	void toCharArrD(char *arr, int i);
	void printInt(int i);
	void printDouble(double d);
	void setMessage(HWND hwnd, int loadSave, int success1, int success2);
	void checkBox(int id);

private:
	static HWND fnc1, fnc2, fnc3, fnc4, fnc5, fnc6, fnc7, fnc8, fnc9, fnc10, fnc11;
	static HWND fnc[13];
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static launcher* ptr;
};

