#pragma once

#include <lcd/lcd.hpp>

#include <linux/fb.h>

namespace lcd
{
class LcdDsi : public LcdScreen
{
private:
    int fb_fd_;
    fb_var_screeninfo vinfo_;
    size_t screen_size_;

    uint16_t *buffer_;
    cv::Mat mat_;
public:
    LcdDsi();
    ~LcdDsi();

    cv::Vec3b pixel(size_t x, size_t y) const override;
	void pixel(size_t x, size_t y, cv::Vec3b color) override;

	void loadFromFile(const std::string &path) override;
	void loadFromMat(const cv::Mat &frame, int cvtColorFlags = 0) override;

    void refresh() override;
    void backlight(uint16_t value) override;

    friend std::unique_ptr<LcdScreen> make_lcd(LcdType);
};
} // namespace lcd
