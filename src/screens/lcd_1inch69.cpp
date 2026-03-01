#include "lcd_1inch69.hpp"

#include "lib/LCD_1in69.h"

#include <signal.h>

namespace lcd
{

Lcd1Inch69::Lcd1Inch69() : LcdRgb565(LCD_1IN69_WIDTH, LCD_1IN69_HEIGHT)
{
	//signal(SIGINT, Handler_1IN69_LCD);
	if (DEV_ModuleInit() != 0)
	{
		DEV_ModuleExit();
		std::clog << "Init failed\n";
		// throw
		return;
	}
	LCD_1IN69_Init(HORIZONTAL);
	LCD_SetBacklight(backlight_);
}

Lcd1Inch69::~Lcd1Inch69()
{
	DEV_ModuleExit();
}

void Lcd1Inch69::refresh()
{
	UWORD j;

	LCD_1IN69_SetWindows(0, 0, LCD_1IN69_WIDTH, LCD_1IN69_HEIGHT);
	LCD_1IN69_DC_1;
    // One would like to write the whole buffer in one go but its not possible
    // however the limit is 8 rows at a time. Default was 1 so its roughly a
    // x8 boost and a syscall count / 8.
    // If no image is displayed, the error could be related to this number.
    // Try speed = 1 in this case.
    const int speed = 1;
	for (j = 0; j < LCD_1IN69.HEIGHT; j+=speed)
	{
		DEV_SPI_Write_nByte((uint8_t *)&buffer_.data()[j * LCD_1IN69.WIDTH], LCD_1IN69.WIDTH * 2 * speed);
	}

	// LCD_1IN69_Display(buffer_.data());
}
void Lcd1Inch69::backlight(uint16_t value)
{
	LCD_1IN69_SetBacklight(value);
}

} // namespace lcd
