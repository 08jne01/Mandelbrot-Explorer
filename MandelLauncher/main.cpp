#include "Header.h"
#include "Launcher.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)

{
	int setupComplete;
	launcher l;
	setupComplete = l.setup(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &l);
	if (setupComplete != 0)

	{
		MessageBox(NULL, "Failure to start program!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
	
}