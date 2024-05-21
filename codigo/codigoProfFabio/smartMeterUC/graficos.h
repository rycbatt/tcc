#ifndef __GRAFICOS__
#define __GRAFICOS__
#include "definicoes.h"

#ifdef USA_DISPLAY

#include <U8x8lib.h>


#else

#define u8x8_font_8x13B_1x2_f 1
#define u8x8_font_amstrad_cpc_extended_r 2
class U8X8_SSD1306_128X64_NONAME_SW_I2C {
  public:
    U8X8_SSD1306_128X64_NONAME_SW_I2C (int a, int b, int c);
    void clear (void);
    void begin(void);
    void setFont(int x);
    void drawString (int y, int x, char *s);
  private:  
};



#endif

extern U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8;

#endif
