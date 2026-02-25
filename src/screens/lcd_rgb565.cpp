#include "lcd_rgb565.hpp"

#include "lib/LCD_1in69.h"

namespace lcd
{

cv::Vec3b rgb565ToBgr(uint16_t rgb565)
{
	// swap endianess
	rgb565 = (rgb565 >> 8) | (rgb565 << 8);

	uint8_t r = (rgb565 >> 11) << 3;
	uint8_t g = ((rgb565 >> 5) & 0x3F) << 2;
	uint8_t b = (rgb565 & 0x1F) << 3;

	return cv::Vec3b(r, g, b);
}

uint16_t bgrToRgb565(cv::Vec3b bgr)
{
	uint8_t r = bgr[0];
	uint8_t g = bgr[1];
	uint8_t b = bgr[2];

	uint16_t rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
	// swap endianess
	rgb565 = (rgb565 >> 8) | (rgb565 << 8);
	//std::clog << std::hex << "0x" << rgb565 << ' ';
	return rgb565;
}

LcdRgb565::LcdRgb565(size_t width, size_t height) : LcdScreen(width, height)
{
	buffer_.resize(width * height);
}

cv::Vec3b LcdRgb565::pixel(size_t x, size_t y) const
{
	// error checking?
	uint16_t rgb565 = buffer_[y * width_ + x];
	return rgb565ToBgr(rgb565);
}

void LcdRgb565::pixel(size_t x, size_t y, cv::Vec3b color)
{
	uint16_t rgb565 = bgrToRgb565(color);
	buffer_[y * width_ + x] = rgb565;
}

void LcdRgb565::loadFromFile(const std::string &path)
{
	auto img = cv::imread(path);
	loadFromMat(img);
}

void LcdRgb565::loadFromMat(const cv::Mat &frame, int cvtColorFlags)
{
	if (frame.empty())
	{
		std::clog << "Error: Input Mat is empty\n";
		return;
	}

	if (cvtColorFlags != 0)
	{
		cv::Mat cvTmp;
		cv::cvtColor(frame, cvTmp, cvtColorFlags);
		cv::resize(cvTmp, matBuffer_, cv::Size(width_, height_));
	}
	else
		cv::resize(frame, matBuffer_, cv::Size(width_, height_));

	for (size_t y = 0; y < height_; ++y)
		for (size_t x = 0; x < width_; ++x)
		{
			cv::Vec3b bgr = matBuffer_.at<cv::Vec3b>(y, x);
			pixel(x, y, bgr);
		}
}

} // namespace lcd
