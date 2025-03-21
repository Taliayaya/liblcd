#pragma once

#include <lcd/lcd.hpp>

namespace lcd
{

class LcdRgb565 : public LcdScreen
{
protected:
	std::vector<uint16_t> buffer_;
	cv::Mat matBuffer_;

public:
	LcdRgb565(size_t width, size_t height);
	~LcdRgb565() = default;

	cv::Vec3b pixel(size_t x, size_t y) const override;
	void pixel(size_t x, size_t y, cv::Vec3b color) override;

	void loadFromFile(const std::string &path) override;
	void loadFromMat(const cv::Mat &frame, int cvtColorFlags = 0) override;
};

} // namespace lcd