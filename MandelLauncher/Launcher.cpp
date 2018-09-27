#include "Launcher.h"
const char g_szClassName[] = "myWindowClass";
#define ID_BTNSTART 1
#define ID_CHECKBOX 23

HWND launcher::fnc1, launcher::fnc2, launcher::fnc3, launcher::fnc4, launcher::fnc5, launcher::fnc6, launcher::fnc7, launcher::fnc8, launcher::fnc9, launcher::fnc10, launcher::fnc11;
HWND launcher::fnc[11];
launcher *launcher::ptr;

LRESULT CALLBACK launcher::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	//Event callback
	
	switch (msg)
	{
		case WM_CLOSE:

		{
			DestroyWindow(hwnd);
			break;
		}

		case WM_DESTROY:

		{
			PostQuitMessage(0);
			break;
		}

		case WM_CREATE:

		{

			fnc[0] = CreateWindowExA(NULL, "button", "Start", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 300, 280, 50, 30, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			fnc[1] = CreateWindowExA(NULL, "button", "Save", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 230, 280, 50, 30, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Fullscreen:", WS_CHILD | WS_VISIBLE, 240, 30, 70, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[2] = CreateWindowExA(NULL, "button", "", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 320, 30, 20, 20, hwnd, (HMENU)3, GetModuleHandle(NULL), NULL);

			CheckDlgButton(hwnd, 3, BST_CHECKED);

			CreateWindowExA(NULL, "static", "Save will store to config", WS_CHILD | WS_VISIBLE, 10, 290, 200, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			CreateWindowExA(NULL, "static", "Start will run the program", WS_CHILD | WS_VISIBLE, 10, 310, 200, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Width:", WS_CHILD | WS_VISIBLE, 10, 30, 45, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[3] = CreateWindowExA(NULL, "edit", "1920", WS_BORDER | WS_CHILD | WS_VISIBLE, 60, 30, 50, 20, hwnd, (HMENU)4, GetModuleHandle(NULL), NULL);
			
			CreateWindowExA(NULL, "static", "Height:", WS_CHILD | WS_VISIBLE, 130, 30, 45, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[4] = CreateWindowExA(NULL, "edit", "1080", WS_BORDER | WS_CHILD | WS_VISIBLE, 180, 30, 50, 20, hwnd, (HMENU)5, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Zoom Step:", WS_CHILD | WS_VISIBLE, 10, 80, 120, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[5] = CreateWindowExA(NULL, "edit", "5", WS_BORDER | WS_CHILD | WS_VISIBLE, 95, 80, 50, 20, hwnd, (HMENU)6, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Initial Zoom:", WS_CHILD | WS_VISIBLE, 200, 80, 120, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[6] = CreateWindowExA(NULL, "edit", "1", WS_BORDER | WS_CHILD | WS_VISIBLE, 290, 80, 50, 20, hwnd, (HMENU)7, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Greyscale:", WS_CHILD | WS_VISIBLE, 10, 130, 70, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[7] = CreateWindowExA(NULL, "button", "", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 90, 130, 20, 20, hwnd, (HMENU)8, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Colour Index:", WS_CHILD | WS_VISIBLE, 200, 130, 120, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[8] = CreateWindowExA(NULL, "edit", "1.5", WS_BORDER | WS_CHILD | WS_VISIBLE, 290, 130, 50, 20, hwnd, (HMENU)9, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Re Position: ", WS_CHILD | WS_VISIBLE, 10, 180, 120, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[9] = CreateWindowExA(NULL, "edit", "0.0", WS_BORDER | WS_CHILD | WS_VISIBLE, 100, 180, 270, 20, hwnd, (HMENU)10, GetModuleHandle(NULL), NULL);

			CreateWindowExA(NULL, "static", "Im Position: ", WS_CHILD | WS_VISIBLE, 10, 230, 120, 20, hwnd, NULL, GetModuleHandle(NULL), NULL);
			fnc[10] = CreateWindowExA(NULL, "edit", "0.0", WS_BORDER | WS_CHILD | WS_VISIBLE, 100, 230, 270, 20, hwnd, (HMENU)11, GetModuleHandle(NULL), NULL);

			break;
		}

		case WM_COMMAND:

		{
			switch (LOWORD(wParam))

			{

				case 1:

				{
					MessageBox(hwnd, "Starting Mandelbrot", "Mandelbrot Launcher", MB_OK | MB_ICONINFORMATION);
					ShellExecute(hwnd, "runas", "mandelbrot_0.2.2.exe", NULL, NULL, SW_SHOWDEFAULT);
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				}

				case 2:

				{

					ptr->save();
					ptr->writeConfig();
					break;
				}

				case 3:

				{
					if (IsDlgButtonChecked(hwnd, 3) == 1)

					{
						CheckDlgButton(hwnd, 3, BST_UNCHECKED);
					}

					else

					{
						CheckDlgButton(hwnd, 3, BST_CHECKED);
					}
					break;
				}

				case 8:

				{
					if (IsDlgButtonChecked(hwnd, 8) == 1)

					{
						CheckDlgButton(hwnd, 8, BST_UNCHECKED);
					}

					else

					{
						CheckDlgButton(hwnd, 8, BST_CHECKED);
					}
					break;
				}
			}
		}

		default:

		{
			if (ptr->startUp == 1)

			{
				SetWindowText(fnc[2], "123");
				ptr->startUp = 0;
			}

			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return 0;
}

int launcher::setup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, launcher* ptr_)

{
	//Register Window
	WNDCLASSEX wc = { 0 };
	HWND hwnd;
	MSG msg;
	//Setup
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = &WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	startUp = 1;
	ptr = static_cast<launcher*>(ptr_);

	//Check it has registered
	if (!RegisterClassEx(&wc))

	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}

	//Create Window
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "Mandelbrot Launcher", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 380, NULL, NULL, NULL, NULL);
	hwndptr = &hwnd;
	//Check it created
	if (hwnd == NULL)

	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	readConfig();
	//load();

	while (GetMessage(&msg, NULL, 0, 0) > 0)

	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return EXIT_SUCCESS;

}

void launcher::readConfig()

{
	//Open the config
	std::ifstream file("config.ini");
	//Check open and then read the config to variables
	if (file.is_open())

	{
		file >> width;
		file >> height;
		file >> fullScreen;
		file >> step;
		file >> x;
		file >> y;
		file >> scale;
		file >> greyScale;

		if (greyScale != 1)

		{
			file >> phase;
		}
		//Close file
		file.close();
	}

	else

	{
		MessageBox(NULL, "File could not be opened. Please run again and create config!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(EXIT_FAILURE);
	}
}

void launcher::writeConfig()

{
	//Open config file
	std::ofstream file("config.ini");
	//Check if it is open and write to config
	if (file.is_open())

	{
		file << width << std::endl;
		file << height << std::endl;
		file << fullScreen << std::endl;
		file << step << std::endl;
		file << x << std::endl;
		file << y << std::endl;
		file << scale << std::endl;
		file << greyScale << std::endl;

		if (greyScale != 1)

		{
			file.precision(20);
			file << phase << std::endl;
		}

		file.close();
	}

	else

	{
		MessageBox(NULL, "File could not be opened!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(EXIT_FAILURE);
	}

}

int launcher::getTextInt(HWND fnc)

{
	int i;
	char arr[20];
	GetWindowText(fnc, arr, 20);
	i = std::stoi(arr);
	return i;
}

double launcher::getTextDouble(HWND fnc)

{
	double value;
	char arr[20];
	GetWindowText(fnc, arr, 20);
	value = std::stoi(arr);
	return value;
}

void launcher::setTextInt(HWND fnc, int i)

{
	std::string s = std::to_string(i);
	char *f = (char*)malloc(sizeof(char) * (s.size() + 1));
	strcpy_s(f, s.size() + 1, s.c_str());
	SetWindowText(fnc, f);
	free(f);
}

void launcher::setTextDouble(HWND fnc, double value)

{
	std::string s = std::to_string(value);
	char *f = (char*)malloc(sizeof(char) * (s.size() + 1));
	strcpy_s(f, s.size() + 1, s.c_str());
	SetWindowText(fnc, f);
	free(f);
}

void launcher::toCharArrI(char *arr, int i)

{
	std::string s = std::to_string(i);
	char *f = (char*)malloc(sizeof(char) * (s.size() + 1));
	strcpy_s(f, s.size() + 1, s.c_str());
	arr = f;
	free(f);
}

void launcher::toCharArrD(char *arr, int i)

{
	std::string s = std::to_string(i);
	char *f = (char*)malloc(sizeof(char) * (s.size() + 1));
	strcpy_s(f, s.size() + 1, s.c_str());
	arr = f;
	free(f);
}

void launcher::save()

{
	width = getTextInt(fnc[3]);
	height = getTextInt(fnc[4]);
	step = getTextInt(fnc[5]);
	scale = getTextInt(fnc[6]);

	greyScale = IsDlgButtonChecked(*hwndptr, 8);
	fullScreen = IsDlgButtonChecked(*hwndptr, 3);

	phase = getTextDouble(fnc[8]);
	x = getTextDouble(fnc[9]);
	y = getTextDouble(fnc[10]);
}

void launcher::load()

{
	width = getTextInt(fnc[3]);
	height = getTextInt(fnc[4]);
	step = getTextInt(fnc[5]);
	scale = getTextInt(fnc[6]);

	greyScale = IsDlgButtonChecked(*hwndptr, 8);
	fullScreen = IsDlgButtonChecked(*hwndptr, 3);

	phase = getTextDouble(fnc[8]);
	x = getTextDouble(fnc[9]);
	y = getTextDouble(fnc[10]);

	setTextInt(fnc[3], width);
	setTextInt(fnc[4], height);
	setTextInt(fnc[5], step);
	setTextInt(fnc[6], scale);

	if (greyScale == 0)

	{
		CheckDlgButton(*hwndptr, 8, BST_UNCHECKED);
	}

	else

	{
		CheckDlgButton(*hwndptr, 8, BST_CHECKED);
	}

	if (fullScreen == 0)

	{
		CheckDlgButton(*hwndptr, 8, BST_UNCHECKED);
	}

	else

	{
		CheckDlgButton(*hwndptr, 8, BST_CHECKED);
	}

	setTextDouble(fnc[8], phase);
	setTextDouble(fnc[9], x);
	setTextDouble(fnc[10], y);
}
