#include <lcd/lcd.hpp>
#include <memory>

#include "screens/lcd_1inch69.hpp"
#include "screens/lcd_dsi.hpp"

namespace lcd
{
std::unique_ptr<LcdScreen> make_lcd(LcdType type)
{
	switch (type)
	{
	case LcdType::LCD_1INCH69_240x280:
		return std::make_unique<Lcd1Inch69>();

    case LcdType::LCD_DSI:
        return std::make_unique<LcdDsi>();

	default:
		throw std::invalid_argument("This screen is not supported yet.");
	}
}

} // namespace lcd
