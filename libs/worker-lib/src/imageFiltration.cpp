#include "imageFiltration.h"

using namespace cv;
using namespace std;

uint8_t colourAnalysis(uint8_t pixel, int colour_quantity)
{
	uint8_t output_pixel = 0;
	int step = 255 / colour_quantity;

	for (int i = 0; i < colour_quantity; i++)
		if (pixel >= i*step && pixel <= (i + 1) * step)
		{
			output_pixel = i*step + step / 2;
			break;
		}

	return output_pixel;
}

void colourRewriting(vector<uint8_t> &output_channel_r, vector<uint8_t> &output_channel_g, vector<uint8_t> &output_channel_b,
	const vector<uint8_t> &input_channel_r, const vector<uint8_t> &input_channel_g, const vector<uint8_t> &input_channel_b,
	const vector<uint8_t> &input_contour_r, const vector<uint8_t> &input_contour_g, const vector<uint8_t> &input_contour_b, int im_size_x, int im_size_y, int colour_quantity, int contour_intensity)
{
	output_channel_r.resize(im_size_x*im_size_y);
	output_channel_g.resize(im_size_x*im_size_y);
	output_channel_b.resize(im_size_x*im_size_y);

	for (int i = 0; i < im_size_y; i++)
	{
		for (int j = 0; j < im_size_x; j++)
		{
			output_channel_r[i*im_size_x + j] = (input_contour_r[i*im_size_x + j] < 127 ? colourAnalysis(input_channel_r[i*im_size_x + j], colour_quantity) : contour_intensity);
			output_channel_g[i*im_size_x + j] = (input_contour_g[i*im_size_x + j] < 127 ? colourAnalysis(input_channel_g[i*im_size_x + j], colour_quantity) : contour_intensity);
			output_channel_b[i*im_size_x + j] = (input_contour_b[i*im_size_x + j] < 127 ? colourAnalysis(input_channel_b[i*im_size_x + j], colour_quantity) : contour_intensity);
		}
	}
}

void contourFilter(vector<uint8_t> &output_channel_r, vector<uint8_t> &output_channel_g, vector<uint8_t> &output_channel_b,
	const vector<uint8_t> &input_channel_r, const vector<uint8_t> &input_channel_g, const vector<uint8_t> &input_channel_b, int im_size_x, int im_size_y)
{
	output_channel_r.resize(im_size_x*im_size_y);
	output_channel_g.resize(im_size_x*im_size_y);
	output_channel_b.resize(im_size_x*im_size_y);

	int f_size = 3;
	int matrix_filter[3][3] = { { 0, -1, 0 }, { -1, 4, -1 }, { 0, -1, 0 } };

	for (int i = 0; i < im_size_y; i++)
	{
		for (int j = 0; j < im_size_x; j++)
		{
			double r = 0;
			double g = 0;
			double b = 0;

			for (int k = 0; k < f_size; k++)
			{
				for (int l = 0; l < f_size; l++)
				{
					int index_str = i - f_size / 2 + k;
					if (index_str < 0) index_str = 0;
					else if (index_str >= im_size_y) index_str = im_size_y - 1;

					int index_stl = j - f_size / 2 + l;
					if (index_stl < 0) index_stl = 0;
					else if (index_stl >= im_size_x) index_stl = im_size_x - 1;

					r += input_channel_r[index_str*im_size_x + index_stl] * matrix_filter[k][l];
					g += input_channel_g[index_str*im_size_x + index_stl] * matrix_filter[k][l];
					b += input_channel_b[index_str*im_size_x + index_stl] * matrix_filter[k][l];
				}
			}
			output_channel_r[i*im_size_x + j] = (uint8_t)r;
			output_channel_g[i*im_size_x + j] = (uint8_t)g;
			output_channel_b[i*im_size_x + j] = (uint8_t)b;
		}
	}
}

void averageFilter(vector<uint8_t> &output_channel_r, vector<uint8_t> &output_channel_g, vector<uint8_t> &output_channel_b,
	const vector<uint8_t> &input_channel_r, const vector<uint8_t> &input_channel_g, const vector<uint8_t> &input_channel_b, int im_size_x, int im_size_y, int f_size)
{
	output_channel_r.resize(im_size_x*im_size_y);
	output_channel_g.resize(im_size_x*im_size_y);
	output_channel_b.resize(im_size_x*im_size_y);

	for (int i = 0; i < im_size_y; i++)
	{
		for (int j = 0; j < im_size_x; j++)
		{
			double r = 0;
			double g = 0;
			double b = 0;

			for (int k = 0; k < f_size; k++)
			{
				for (int l = 0; l < f_size; l++)
				{
					int index_str = i - f_size / 2 + k;
					if (index_str < 0) index_str = 0;
					else if (index_str >= im_size_y) index_str = im_size_y - 1;

					int index_stl = j - f_size / 2 + l;
					if (index_stl < 0) index_stl = 0;
					else if (index_stl >= im_size_x) index_stl = im_size_x - 1;

					r += input_channel_r[index_str*im_size_x + index_stl];
					g += input_channel_g[index_str*im_size_x + index_stl];
					b += input_channel_b[index_str*im_size_x + index_stl];
				}
			}
			r /= (f_size * f_size);
			g /= (f_size * f_size);
			b /= (f_size * f_size);
			output_channel_r[i*im_size_x + j] = (uint8_t)r;
			output_channel_g[i*im_size_x + j] = (uint8_t)g;
			output_channel_b[i*im_size_x + j] = (uint8_t)b;
		}
	}
}

void imageFilter(vector<uint8_t> &output_channel_r, vector<uint8_t> &output_channel_g, vector<uint8_t> &output_channel_b,
	const vector<uint8_t> &input_channel_r, const vector<uint8_t> &input_channel_g, const vector<uint8_t> &input_channel_b,
	unsigned width, unsigned height, bool contour, int f_size, int colour_quantity, int contour_intensity)
{
	if (contour)
	{
		vector<uint8_t> r;
		vector<uint8_t> g;
		vector<uint8_t> b;
		vector<uint8_t> contour_r;
		vector<uint8_t> contour_g;
		vector<uint8_t> contour_b;


		averageFilter(r, g, b, input_channel_r, input_channel_g, input_channel_b, width, height, f_size);
		contourFilter(contour_r, contour_g, contour_b, r, g, b, width, height);
		colourRewriting(output_channel_r, output_channel_g, output_channel_b, input_channel_r, input_channel_g, input_channel_b, contour_r, contour_g, contour_b, width, height, colour_quantity, contour_intensity);
	}
	else
	{
		vector<uint8_t> contour_r(width*height);
		vector<uint8_t> contour_g(width*height);;
		vector<uint8_t> contour_b(width*height);;
		colourRewriting(output_channel_r, output_channel_g, output_channel_b, input_channel_r, input_channel_g, input_channel_b, contour_r, contour_g, contour_b, width, height, colour_quantity, contour_intensity);
	}
}