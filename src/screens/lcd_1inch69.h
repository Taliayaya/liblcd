#ifndef LCD_1INCH69_H
#define LCD_1INCH69_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LCD_1IN69_WIDTH  280
#define LCD_1IN69_HEIGHT 240


enum lcd_direction
{
    HORIZONTAL = 0,
    VERTICAL = 1
};

int  lcd_1inch69_init(enum lcd_direction direction);
void lcd_1inch69_deinit();

void lcd_1inch69_set_window(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void lcd_1inch69_write(uint8_t *buffer, uint32_t length);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !LCD_1INCH69_H