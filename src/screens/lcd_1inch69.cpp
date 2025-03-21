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
	LCD_1IN69_Init(VERTICAL);
	LCD_SetBacklight(backlight_);
}

Lcd1Inch69::~Lcd1Inch69()
{
	DEV_ModuleExit();
}

void Lcd1Inch69::refresh()
{
	LCD_1IN69_Display(buffer_.data());
}
void Lcd1Inch69::backlight(uint16_t value)
{
	LCD_1IN69_SetBacklight(value);
}

} // namespace lcd
