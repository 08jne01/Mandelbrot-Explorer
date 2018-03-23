# Mandelbrot-Explorer
Mandelbrot Explorer for exploring the mandelbrot fractal easily.

Gif of this in action:
https://gfycat.com/ShowyAngelicHart

Some Screenshots:
https://imgur.com/a/RmLJK

**What is a mandelbrot?**  


[Mandelbrot](https://en.wikipedia.org/wiki/Mandelbrot_set) is a set of complex numbers which when displayed creates a [fractal](https://en.wikipedia.org/wiki/Fractal). What is a complex number? It is basically a 2 dimensional number that consists of two parts the real part (normal numbers) and the imaginary part (multiples of i = squareroot(-1)). The Mandelbrot set follows the recursive formula:  


z(n+1) = z(n)^2 + c, where c is the complex number being tested, z(n) is the previous term and z(n+1) is the current term. If this formula diverges to infinity then the complex number c is not in the Mandelbrot set. 

The program works by testing this for 1000 iterations for each pixel on the display and assigns a colour depending on at what point the real/imaginary diverges past +/- 2 is how it is assigned a colour. If the program does all 1000 iterations without diverging past +/- 2 for real/imaginary it is assigned black and is considered to most probably be in the Mandelbrot set.

**How does the program work?**

At the moment the program has three controls, left/right click and spacebar.

Left Click -> Zooms in by the step determined in the config file and centres the view on the position of the cursor.  
Right Click -> Zooms out by the step determined in the config file and centres the view on the position of the cursor.  
Spacebar -> Saves current coordinates and zoom level to a coordinate file named coords.txt which will be placed in the same folder the executable is in.  

Run the program if you haven't set up the config see below, otherwise type 0 to skip config creation. While the application is running the console will display useful information such as loading percentage, position, zoom and render time (in milliseconds).

Once loaded the image will render, then simply click where you wish to zoom and the program will calculate. Calculation time will vary dependent on resolution and computer processing power but for 1920x1080 it will take ~1 - 2 seconds.

**Installation:**

Drop mandelbrot_(version).exe into a folder. If you run the program in program files (or any protected folders) you have to run it as administrator. Otherwise it will not be able to write the configuration file and coordinates file. Run the program for the first time and type 1 for new config.

**Configuration:**

On a first time run select 1 for a new config file and fill in the values asked by the console.

Window Width: this is the width of the window resolution you require (if fullscreen then put in your monitor resolution).

Window Height: same as above except for the height.

Full Screen: 0 for windowed and 1 for fullscreen (note this takes effect on the primary monitor).

Zoom Step: this is how much the program will zoom in/out each time you left/right click typically this is set to 10.

Init Position x: this is the x (real) position that the program will start at typically 0 if you are just exploring.

Init Position y: same as above but for y (imaginary).

Init Zoom: this is the initial zoom, typically 1 for exploring (setting this to zero will close the application due to divide by zero error).

GreyScale?: 1 will give you grey scale, 0 will give a color scale.

Color Index: this allows you to change the colour scale, this is just an arbitrary number for the functions calculating the colour gradient, set between -2 and 2.

