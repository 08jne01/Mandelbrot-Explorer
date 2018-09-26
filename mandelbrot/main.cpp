#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
#include "MandelClass.h"
#include "Program.h"
#include "CallBack.h"

int main()

{
	std::cout << "Mandelbrot Explorer, by Joshua Nelson." << std::endl;
	std::cout << "Copyright Joshua Nelson 2018." << std::endl << std::endl;

	//Variables for config file or user input
	int width, height, greyScale, newConfig, fullScreen;
	double step, x, y, scale, phase;

	//Input
	std::cout << "Write New Config? (1 for yes 0 for no): ";
	std::cin >> newConfig;

	//Define program
	program p;

	//Checks if new config is required and writes new values to a file
	if (newConfig != 0)

	{
		std::cout << "\nWindow Width (500 - 2000 Pixels): ";
		std::cin >> width;
		std::cout << "\nWindow Height (500 - 2000 Pixels): ";
		std::cin >> height;
		std::cout << "\nFull Screen (0 for windowed, 1 for fullscreen): ";
		std::cin >> fullScreen;
		std::cout << "\nZoom Step (2-20): ";
		std::cin >> step;
		std::cout << "\nInit Position x: ";
		std::cin >> x;
		std::cout << "\nInit Position y: ";
		std::cin >> y;
		std::cout << "\nInit Zoom: ";
		std::cin >> scale;
		std::cout << "\nGreyScale? (1 for grey scale 0 for color): ";
		std::cin >> greyScale;

		if (greyScale == 0)

		{
			std::cout << "\nColor Index (-2 - 2): ";
			std::cin >> phase;
		}

		//Initialises the program with all variables from config/user input
		p.init(width, height, step, x, y, scale, greyScale, phase, fullScreen);
		p.writeConfig();

		if (step == 0 || scale == 0)

		{
			std::cout << "Divide by Zero Error please re-do the config more carefully!" << std::endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
	}
	
	else

	{
		p.readConfig();
	}

	//Check for GLFW initilisation
	if (!glfwInit())

	{
		std::cout << "GLFW did not initialise!" << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	//Setup window pointer
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window;

	//Choose fullscreen or not depending on the config and then set window pointer
	if (p.fullScreen == 1)

	{
		window = glfwCreateWindow(p.width, p.height, "MandleBrot", glfwGetPrimaryMonitor(), NULL);
	}

	else

	{
		window = glfwCreateWindow(p.width, p.height, "MandleBrot", NULL, NULL);
	}

	//Setup pointer associated with the window, this is important for accessing program variables when using callbacks
	glfwSetWindowUserPointer(window, &p);

	//Check if the window has initilised properly
	if (!window)

	{
		std::cout << "Window did not initialise!";
		glfwTerminate();
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	//Select window and set swap interval for buffers
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Initial render of the mandelbrot based on config settings
	p.update(1.0, 1);

	//Start of the program loop
	while (!glfwWindowShouldClose(window))

	{
		//Setup of frame
		glfwGetFramebufferSize(window, &p.width, &p.height);
		glViewport(0, 0, p.width, p.height);
		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Drawing
		p.draw();

		//Gets cursor positions and sets the callbacks for keys and mouse
		glfwGetCursorPos(window, &p.xCurs, &p.yCurs);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyCallback);

		//Check for callback events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Close everything properly
	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)

{
	//Casts the pointer from the window to a program* pointer
	void* ptr = glfwGetWindowUserPointer(window);
	program *kptr = static_cast<program*>(ptr);
	//Using the pointer calls the mouse callback
	kptr->mouseCallback(window, button, action, mods);
}

void keyCallback(GLFWwindow *window, int button, int scancode, int action, int mods)

{
	//Casts the pointer from the window to a program* pointer
	void* ptr = glfwGetWindowUserPointer(window);
	program *kptr = static_cast<program*>(ptr);
	//Using the pointer calls the key callback
	kptr->keyCallBack(button, action);
}