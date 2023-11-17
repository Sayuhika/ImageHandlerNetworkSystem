#include <vector>
#include <opencv2\opencv.hpp>

void imageFilter(std::vector<uint8_t> &output_channel_r, std::vector<uint8_t> &output_channel_g, std::vector<uint8_t> &output_channel_b,
	const std::vector<uint8_t> &input_channel_r, const std::vector<uint8_t> &input_channel_g, const std::vector<uint8_t> &input_channel_b,
	unsigned width, unsigned height, bool contour = true, int f_size = 3, int colour_quantity = 5, int contour_intensity = 50);