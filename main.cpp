#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

void getBoundaries(std::ifstream& i, double &XMin, double &XMax, double &YMin, double &YMax)
{
	double c1real, c2real, c1imag, c2imag;
	i >> c1real;
	i >> c1imag;
	i >> c2real;
	c2imag = c1imag + (c1real - c2real);
	
	XMin = c1real;
	XMax = c2real;
	YMin = c1imag;
	YMax = c2imag;
}

std::ifstream fin("mandelinput.txt");

namespace
{
	const auto COLOR_DEPTH = 225;
	const auto PIXEL_DIMENSIONS = 1000;
}

std::ofstream fout("mandeloutput.ppm");

void header(std::ofstream& o)
{
	o << "P3" << std::endl;
	o << PIXEL_DIMENSIONS << " " << PIXEL_DIMENSIONS << std::endl;
	o << COLOR_DEPTH << std::endl;
}

int paletteRed(int iter)
{
	if (iter > 999)
	{
		return 0; 
	}
	else return iter;
}

int paletteGreen(int iter)
{
	if (iter > 999)
	{
		return 0;
	}
	else return iter;
}

int paletteBlue(int iter)
{ 
	if (iter > 999)
	{
		return 0;
	}
	else return iter;
}


void pixelOut(std::ofstream& o, int iteration)
{
	int red = paletteRed(iteration);
	int green = paletteGreen(iteration);
	int blue = paletteBlue(iteration);
	o << red << " " << green << " " << blue << "\t";
}

double interpolate(int pixel, char xy, double XMin, double XMax, double YMin, double YMax)
{
	double interpolation;
	if (xy == 'x')
	{
		interpolation = ((pixel * ((XMax - XMin) / PIXEL_DIMENSIONS))) + XMin;
	}
	else
	{
		interpolation = ((pixel * ((YMax - YMin) / PIXEL_DIMENSIONS))) + YMin;
	}
	return interpolation;
}

int mandelbrot(int Px, int Py, double XMin, double XMax, double YMin, double YMax)
{
	double x0 = interpolate(Px, 'x', XMin, XMax, YMin, YMax);
	double y0 = interpolate(Py, 'y', XMin, XMax, YMin, YMax);
	double x = 0.0;
	double y = 0.0;
	int iteration = 0;
	int max_iteration = 5000;
	while (x*y < pow(4,2) && iteration < max_iteration) 
	{
		auto xtemp = pow(x,2) - pow(y,2) + x0;
		y = 2*x*y + y0;
		x = xtemp;
		iteration = iteration + 2;
	}
	return iteration;
}

int main() 
{
	double XMin, XMax, YMin, YMax;
	getBoundaries(fin, XMin, XMax, YMin, YMax);
	header(fout);
	for (int i = 0; i < PIXEL_DIMENSIONS; ++i)
	{
		for (int j = 0; j < PIXEL_DIMENSIONS; ++j)
		{
			int iteration = mandelbrot(j, i, XMin, XMax, YMin, YMax);
			pixelOut(fout, iteration);
		}
		fout << std::endl;
		std::cout << i << std::endl;
	}
	system("feh mandeloutput.ppm");
	return EXIT_SUCCESS;
}