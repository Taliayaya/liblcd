#pragma once

#include <lcd/lcd.hpp>

#include "screens/lcd_rgb565.hpp"

namespace lcd
{

/**
 * docs: https://www.waveshare.com/wiki/1.69inch_LCD_Module
 * 
 * Sum-up:
 * - Protocole: SPI
 * - Size: 240x280
 * - Color used: RGB565
 * - Controller: ST7789V2
 */

class Lcd1Inch69 : public LcdRgb565
{
public:
	Lcd1Inch69(/* args */);
	~Lcd1Inch69();

	void refresh() override;
	void backlight(uint16_t value) override;

	friend std::unique_ptr<LcdScreen> make_lcd(LcdType);
};

} // namespace lcd