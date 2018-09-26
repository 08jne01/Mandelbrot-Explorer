#include "Header.h"
#include "Complex.h"
#include "InMandel.h"
#include "MandelClass.h"
#include "Program.h"



void program::init(int width_, int height_, double step_, double x_, double y_, double scale_, double greyScale_, double phase_, int fullScreen_)

{
	//Set all starting parameters
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
	itters = 1000;

	if (width > height)

	{
		res = width;
	}

	else if (height > width)

	{
		res = height;
	}

}

void program::checkRatio()

{
	//Checks ratio and defines depending whether width > height or not
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

}

void program::update(double local_step, int init)

{
	//Define ratio of window based on window size
	ratio = height / (double)width;
	//Set calculated to 0 so that the renderer knows not to render otherwise there will be access violation
	calculated = 0;

	//Check and set Ratio
	checkRatio();
	
	//Start clock to time render process
	int startS = clock();
	//Choose next x, y based on cursor position
	if (init != 1)

	{
		x += ((2.0 / (width*0.5))*xCurs - 2.0) / scale;
		y += ((-ratio * 2.0 / (height*0.5))*(yCurs)+ratio * 2.0) / scale;
	}
	//Change scale based on settings
	scale *= local_step;
	mandel.scale = scale / 2.0;
	//Set the edge of the screen for rendering
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
	//Print some info
	std::cout.precision(20);
	std::cout << "\nx = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout.precision(1);
	std::cout << "Zoom Level = " << scale << std::endl;
	std::cout << "Itterations = " << itters << std::endl;

	//Calculate the mandelbrot
	mandel.calcMandel(res, xRatio, yRatio, itters);

	//Stop the clock and calculate render time
	int stopS = clock();
	std::cout << "\rRender Time: " << (stopS - startS) / double(CLOCKS_PER_SEC) * 1000 << " ms" << "                           " << std::endl;

	//Set calculated to 1 so that the render knows it can reach the variables without causing an access violation
	calculated = 1;
}

void program::draw()

{
	//Check that the mandelbrot is not calculating so as to not cause an access violation
	if (calculated == 1)

	{
		double q, r, g, b;
		ratio = height / (double)width;

		//Check and set ratio
		checkRatio();
		//Set phase increase or decrease for colour scheme
		phase += phaseincrease * 0.1;
		//Set pointsize and begin drawing points
		glPointSize(pointSize);
		glBegin(GL_POINTS);
		//Loop through each pixel and draw a point based on colour array
		for (int i = 0; i < ceil(mandel.size*xRatio); i++)

		{

			for (int j = 0; j < ceil(mandel.size*yRatio); j++)

			{
				//Invert values
				q = 1 - mandel.colorArr[i][j];
				//Choose colour scheme based on config
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
				//glVertex2d(c.re*0.5*scale - x*0.5*scale, (c.im*0.5*scale - y*0.5*scale) / ratio);
				glVertex2d(coordTransform(i, width), coordTransform(j, height));
			}
		}
		glEnd();
	}
}

void program::mouseCallback(GLFWwindow* window, int button, int action, int mods)

{
	//Update to zoom in
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)

	{
		update(step, 0);
	}
	//Update to zoom out
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

	{
		update(1.0 / step, 0);
	}

}

void program::keyCallBack(int key, int pressed)

{

	if (pressed == GLFW_PRESS)

	{

		switch (key)

		{
			//Save coordinates and screenshot
			case GLFW_KEY_SPACE:

			{
				std::string s = "Screenshot ";
				s += currentTime();
				s += ".bmp";
				writeCoords(s);
				saveBMP(s);
				break;
			}
			//Change phase for colour scheme to on in either direction depending on keys
			case GLFW_KEY_LEFT:

			{
				phaseincrease = -1;
				break;
			}

			case GLFW_KEY_RIGHT:

			{
				phaseincrease = 1;
				break;
			}
			//Increase or decrease number of itterations for calculation
			case GLFW_KEY_UP:

			{
				itters *= 1.5;
				update(1.0, 1);
				break;
			}

			case GLFW_KEY_DOWN:

			{
				itters /= 1.5;
				update(1.0, 1);
				break;
			}
		}
	}

	else if (pressed == GLFW_RELEASE)

	{

		switch (key)

			{
			//Reset phase change when user releases the key
			case GLFW_KEY_LEFT:

			{
				phaseincrease = 0;
				break;
			}

			case GLFW_KEY_RIGHT:

			{
				phaseincrease = 0;
				break;
			}
		}
	}
}

void program::readConfig()

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
		std::cout << "File could not be opened. Please run again and create config!" << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	//Set variables from file
	init(width, height, step, x, y, scale, greyScale, phase, fullScreen);
}

void program::writeConfig()

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
		std::cout << "File could not be opened." << std::endl;
	}

}

void program::saveBMP(std::string filename)

{
	//Allocate memory for filename and convert filename to char array so that string can be used
	char *filenameCharArray = (char*)malloc(sizeof(char) * (filename.size() + 1));
	strcpy_s(filenameCharArray, filename.size() + 1, filename.c_str());
	//Open file and create write buffer
	FILE *out;
	fopen_s(&out, filenameCharArray, "wb");
	byte* buff = new byte[width*height * 3];
	//Round down to nearest multiple of 4 otherwise bmp will not work
	int tempWidth = roundDownNearest(width, 4);
	int tempHeight = height;
	//Read back buffer
	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, tempWidth, tempHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, buff);
	//Check buffer was allocated and the file was opened
	if (!out || !buff)

	{
		std::cout << "Error Writing to File!" << std::endl;
		return;
	}
	//Create file and info header variables
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	//Setup file header
	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + tempWidth * tempHeight * 3;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//Setup info header
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = tempWidth - 1;
	bitmapInfoHeader.biHeight = tempHeight - 1;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	//Write to file
	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, out);
	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, out);
	fwrite(buff, tempWidth*tempHeight * 3, 1, out);
	//Free memory and close files
	free(filenameCharArray);
	fclose(out);
	delete[] buff;

	std::cout << filename << " saved!" << std::endl;
}

void program::writeCoords(std::string s)

{
	//Open file and appened to end of file
	std::ofstream file;
	file.open("coords.txt", std::ios::app);
	//Check file is open and then append the below values
	if (file.is_open())

	{
		file.precision(20);
		file << "Re = " << x << " Im = " << y;
		file.precision(3);
		file << " Scale = " << scale;
		file << "Screenshot timestamp: " << s;
		file.close();

		std::cout << "\nCoords copied to file!" << std::endl;
	}

	else

	{
		std::cout << "File could not be opened." << std::endl;
	}
}

double program::coordTransform(double pixel, int dimension)

{
	//Transforms pixel coordinates to screen coordinates (1 dimensional function)
	double screenpos;
	screenpos = ((2 * pixel) / (float)dimension) - 1;
	return screenpos;
}

int program::roundDownNearest(int val, int multiple)

{
	//Rounds down to the nearest multiple (used with bitmap output)
	if (val % multiple == 0)

	{
		return val;
	}

	else

	{
		return (val - (val % multiple));
	}
}

std::string program::currentTime()

{
	//Gets current time and formats to string to be appended to filename and coordinate file
	time_t rawTime;
	struct tm time_info;
	time(&rawTime);
	localtime_s(&time_info, &rawTime);
	std::ostringstream os;

	os << " " << time_info.tm_mday << "-" << time_info.tm_mon + 1 << "-" << time_info.tm_year + 1900 << "_" << time_info.tm_hour << time_info.tm_min << time_info.tm_sec;

	return os.str();
}