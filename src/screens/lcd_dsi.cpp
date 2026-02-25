#include "lcd_dsi.hpp"

#include <fcntl.h>
#include <stdexcept>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <sys/ioctl.h>
#include <iostream>

namespace lcd
{
    static cv::Vec3b rgb565_to_rgb888(uint16_t val)
    {
        int r = val >> 11;
        int g = (val & 0x03c0) >> 5;
        int b = (val & 0x0001f);
        return cv::Vec3b(r, g, b);
    }

    static uint16_t rgb888_to_rgb565(cv::Vec3b val)
    {
        uint8_t r = val[2];
        uint8_t g = val[1];
        uint8_t b = val[0];

	    uint16_t rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        return rgb565;
    }

    LcdDsi::LcdDsi() : LcdScreen(0, 0)
    {
        const char *fb_path = "/dev/fb0";
        fb_fd_ = open(fb_path, O_RDWR);
        if (fb_fd_ < 0)
        {
            perror("liblcd: lcddsi: open");
            throw std::runtime_error("open");
        }

        if (ioctl(fb_fd_, FBIOGET_VSCREENINFO, &vinfo_) < 0)
        {
            perror("liblcd: lcddsi: ioctl");
            close(fb_fd_);
            throw std::runtime_error("ioctl");
        }

        width_ = vinfo_.xres;
        height_ = vinfo_.yres;

        screen_size_ = width_ * height_ * 4; // assuming 32 bits

        void *fb_ptr = mmap(0, screen_size_, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd_, 0);
        if (fb_ptr == MAP_FAILED)
        {
            perror("liblcd: lcddsi: mmap");
            close(fb_fd_);
            throw std::runtime_error("mmap");
        }

        buffer_ = static_cast<uint16_t *>(fb_ptr);
        mat_ = cv::Mat(height_, width_, CV_16UC1, fb_ptr);
    }

    LcdDsi::~LcdDsi()
    {
        munmap(buffer_, width_ * screen_size_);
        close(fb_fd_);
    }

    cv::Vec3b LcdDsi::pixel(size_t x, size_t y) const
    {
        uint32_t val = buffer_[y * width_ + x];
        return rgb565_to_rgb888(val);
    }

	void LcdDsi::pixel(size_t x, size_t y, cv::Vec3b color)
    {
        uint32_t val = rgb888_to_rgb565(color);
        buffer_[y * width_ + x] = val;
    }

	void LcdDsi::loadFromFile(const std::string &path)
    {
        auto img = cv::imread(path);
        loadFromMat(img);
    }
	void LcdDsi::loadFromMat(const cv::Mat &frame, int cvtColorFlags)
    {
        if (cvtColorFlags != 0)
        {
            cv::Mat cvTmp;
            cv::cvtColor(frame, cvTmp, cvtColorFlags);
            cv::resize(cvTmp, mat_, cv::Size(height_, width_));
        }
        else
            cv::resize(frame, mat_, cv::Size(height_, width_));

        for (size_t y = 0; y < height_; ++y)
            for (size_t x = 0; x < width_; ++x)
            {
                cv::Vec3b bgr = mat_.at<cv::Vec3b>(x, y);
                pixel(x, y, bgr);
            }
    }

    void LcdDsi::refresh()
    {
    }

    void LcdDsi::backlight(uint16_t value)
    {
    }
} // namespace lcd
