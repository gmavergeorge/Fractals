#include <fstream>
#include <iostream>
#include <complex>
#include <cstdlib>
#include <cmath>

std::ifstream fin("mandelinput.txt");

namespace
{
	const auto COLOR_DEPTH = 255;
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

int main() 
{
	header(fout);

	std::complex<float> z_old(0.0f, 0.0f);
	std::complex<float> z_new(0.0f, 0.0f);
	std::complex<float> c(0.660, 0.3339);

	for (int y = 0; y < PIXEL_DIMENSIONS; ++y)
	{
		for (int x = 0; x < PIXEL_DIMENSIONS; ++x)
		{
			z_new.real(3.0f * x / (PIXEL_DIMENSIONS) - 1.5f);
			z_new.imag(3.0f * y / (PIXEL_DIMENSIONS) - 1.5f);
			int iteration = 0;
			int max_iteration = 1000;
			while (iteration < max_iteration) 
			{
				z_new = pow(z_new,2);
				z_old.real(z_new.real());
				z_old.imag(z_new.imag());
				z_new -= c;
				if(norm(z_new) > 2.0) break;
				iteration = iteration + 1.0;
			}
			pixelOut(fout, iteration);
		}
		fout << std::endl;
		std::cout << y << std::endl;
	}
	system("feh mandeloutput.ppm");
	return EXIT_SUCCESS;
}