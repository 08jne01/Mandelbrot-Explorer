#include "Header.h"

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
static void keyCallback(GLFWwindow *window, int button, int scancode, int action, int mods);

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



public:

	mandelClass mandel;
	std::vector <double>v;

	double xCurs;
	double yCurs;
	double pointSize;
	int width;
	int height;
	int fullScreen;

	void init(int width_, int height_, double step_, double x_, double y_, double scale_, double greyScale_, double phase_, int fullScreen_)

	{

		width = width_;
		height = height_;
		step = step_;
		x = x_;
		y = y_;
		scale = scale_;
		pointSize = 1;
		greyScale = greyScale_;
		phase = phase_;
		fullScreen = fullScreen_;
		calculated = 0;

		ratio = height / (double)width;
	
		if (width > height)

		{

			res = width;

		}

		else if (height > width)

		{


			res = height;

		}


	}

	void update(double local_step, int init)

	{

		ratio = height / (double)width;
		calculated = 0;

		if (ratio > 1.0)

		{

			res = height;
			xRatio = 1.0 / ratio;
			yRatio = 1;

		}

		else

		{

			res = width;
			xRatio = 1;
			yRatio = ratio;

		}

		int startS = clock();

		if (init != 1)

		{

			x += ((2.0 / (width*0.5))*xCurs - 2.0) / scale;
			y += ((-ratio * 2.0 / (height*0.5))*(yCurs) + ratio * 2.0) / scale;

		}


		scale *= local_step;
		mandel.scale = scale / 2.0;

		if (ratio > 1.0)

		{

			mandel.xEdge = -2.0 / ((double)scale) + x;
			mandel.yEdge = -2.0*ratio / ((double)scale) + y;

		}

		else

		{

			mandel.xEdge = -2.0 / ((double)scale) + x;
			mandel.yEdge = -2.0 / ((double)scale)*ratio + y;

		}

		


		std::cout.precision(20);
		std::cout << "\nx = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		std::cout.precision(1);
		std::cout << "Zoom Level = " << scale << std::endl;

		mandel.size = res;
		mandel.colorArr.resize(res*res);
		mandel.cpx.resize(res*res);
		mandel.calcMandel(res, xRatio, yRatio);

		int stopS = clock();

		std::cout << "\rRender Time: " << (stopS - startS) / double(CLOCKS_PER_SEC) * 1000 << "                           " << std::endl;

		calculated = 1;

	}

	void draw()

	{

		//std::cout << calculated << std::endl;
		if (calculated == 1)

		{

			complex c;
			double q, r, g, b;


			ratio = height / (double)width;

			if (ratio > 1.0)

			{

				xRatio = 1.0 / ratio;
				yRatio = 1;

			}

			else

			{

				xRatio = 1;
				yRatio = ratio;

			}

			//std::cout << xRatio << std::endl;
			//std::cout << ratio << std::endl;

			glBegin(GL_POINTS);


			for (int i = 0; i < ceil(mandel.size*xRatio); i++)

			{

				for (int j = 0; j < ceil(mandel.size*yRatio); j++)

				{

					c = mandel.cpx[i][j];
					q = 1 - mandel.colorArr[i][j];

					if (greyScale >= 1)

					{

						r = q;
						g = q;
						b = q;

					}

					else

					{

						r = sin(2 * PI *q)*sin(2 * PI *q);
						g = sin(phase* PI *q)*sin(2 * PI *q);
						b = q;

					}

					glColor3d(r, g, b);
					glVertex2d(((c.re) - x)*0.5*scale, ((c.im) - y)*0.5*scale / ratio);

				}

			}
			glEnd();
		}
	}

	void mouseCallback(GLFWwindow* window, int button, int action, int mods)

	{

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)

		{

			update(step, 0);

		}

		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

		{

			update(1.0 / step, 0);

		}

	}

	void readConfig()

	{

		std::ifstream file("config.ini");

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

			file.close();

		}

		else

		{

			std::cout << "File could not be opened. Please run again and create config!" << std::endl;
			system("PAUSE");
			exit(EXIT_FAILURE);

		}
		
		init(width, height, step, x, y, scale, greyScale, phase, fullScreen);


	}

	void writeConfig()

	{

		std::ofstream file("config.ini");

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

				file << phase << std::endl;

			}

			file.close();

		}

		else

		{

			std::cout << "File could not be opened." << std::endl;

		}

	}

	void writeCoords()

	{

		std::ofstream file;

		file.open("coords.txt", std::ios::app);

		if (file.is_open())

		{

			file.precision(20);
			file << "Re = " << x << " Im = " << y;
			file.precision(3);
			file << " Scale = " << scale << std::endl;
			file.close();

			std::cout << "\nCoords copied to file!" << std::endl;

		}

		else

		{

			std::cout << "File could not be opened." << std::endl;

		}

	}

};


int main()

{

	std::cout << "Mandelbrot Explorer, by Joshua Nelson." << std::endl;
	std::cout << "Copyright Joshua Nelson 2018." << std::endl << std::endl;

	program p;

	int width, height, greyScale, newConfig, fullScreen;
	double step, x, y, scale, phase;

	//Input
	std::cout << "Write New Config? (1 for yes 0 for no): ";
	std::cin >> newConfig;

	if (newConfig != 0)

	{

		std::cout << "\nWindow Width (500 - 2000 Pixels): ";
		std::cin >> width;
		std::cout << "\nWindow Height (500 - 2000 Pixels): ";
		std::cin >> height;
		//std::cout << "\nSuper Sample (experimental, 1 for off): ";
		//std::cin >> supersample;
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

	if (!glfwInit())

	{

		exit(EXIT_FAILURE);

	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window;

	if (p.fullScreen == 1)

	{

		window = glfwCreateWindow(p.width, p.height, "MandleBrot", glfwGetPrimaryMonitor(), NULL);

	}

	else

	{

		window = glfwCreateWindow(p.width, p.height, "MandleBrot", NULL, NULL);

	}
	

	//glEnable(GL_MULTISAMPLE);

	/*
	if (p.supersample != 1)

	{

		glfwWindowHint(GLFW_SAMPLES, p.supersample);

	}
	*/

	glfwSetWindowUserPointer(window, &p);

	if (!window)

	{

		std::cout << "Print";
		glfwTerminate();
		exit(EXIT_FAILURE);

	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//std::thread calc

	//{

		//[&]()

		//{

			p.update(1.0, 1);

		//}

	//};

	//calc.join();

	//Render Thread
	while (!glfwWindowShouldClose(window))

	{
		//Setup
		glfwGetFramebufferSize(window, &p.width, &p.height);
		glViewport(0, 0, p.width, p.height);
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(p.pointSize);

		//Drawing

		p.draw();

		glfwGetCursorPos(window, &p.xCurs, &p.yCurs);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyCallback);
		glReadPixels(); 

		//Swap Buffer and Check Events
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);

}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)

{

	void* ptr = glfwGetWindowUserPointer(window);
	program *kptr = static_cast<program*>(ptr);

	kptr->mouseCallback(window, button, action, mods);

}

void keyCallback(GLFWwindow *window, int button, int scancode, int action, int mods)

{
	
	void* ptr = glfwGetWindowUserPointer(window);
	program *kptr = static_cast<program*>(ptr);

	if (button == GLFW_KEY_SPACE && action == GLFW_PRESS)

	{

		kptr->writeCoords();

	}

}