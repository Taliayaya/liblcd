#pragma once

#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

namespace lcd
{

enum LcdType
{
	LCD_1INCH69_240x280
};

class LcdScreen
{
protected:
	const size_t width_;
	const size_t height_;
	const uint16_t backlight_ = 1023;

public:
	/* Properties*/

	size_t width() const { return width_; }
	size_t height() const { return height_; }
	size_t backlight() const { return height_; }
	virtual void backlight(uint16_t value) = 0;

	/* Methods */

	virtual cv::Vec3b pixel(size_t x, size_t y) const = 0;
	virtual void pixel(size_t x, size_t y, cv::Vec3b color) = 0;

	virtual void loadFromFile(const std::string &path) = 0;
	virtual void loadFromMat(const cv::Mat &frame, int cvtColorFlags = 0) = 0;

	/**
	 * Refresh the screen buffer and update the display
	 */
	virtual void refresh() = 0;

protected:
	LcdScreen(size_t width, size_t height) : width_(width), height_(height) {}
};

std::unique_ptr<LcdScreen> make_lcd(LcdType type);

} // namespace lcd