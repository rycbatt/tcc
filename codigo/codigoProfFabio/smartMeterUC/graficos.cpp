#include "graficos.h"


#ifndef USA_DISPLAY
 U8X8_SSD1306_128X64_NONAME_SW_I2C::U8X8_SSD1306_128X64_NONAME_SW_I2C (int a, int b, int c)
{
}
void U8X8_SSD1306_128X64_NONAME_SW_I2C::clear (void)
{
}
void U8X8_SSD1306_128X64_NONAME_SW_I2C::begin (void)
{
}

void U8X8_SSD1306_128X64_NONAME_SW_I2C::setFont (int x)
{
}

void U8X8_SSD1306_128X64_NONAME_SW_I2C::drawString (int y, int x, char *s)
{
}

#endif



U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
