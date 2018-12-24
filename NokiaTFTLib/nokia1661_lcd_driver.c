/*
 * nokia1616/1661 TFT lcd Driver for AVR microcontroller
 * Copyright (C) 2018 mohammad mazarei (mohammad.mazarei [at] gmail.com)
 * web site: https://sisoog.com
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "spfd54124b.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "nokia1661_lcd_driver.h"


struct N1616Data	_lcd_data;

#define SBI(port,bit) 	asm("sbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit))
#define CBI(port,bit) 	asm("cbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit))

/*---------------------------------------------------------------------------------------------------------------
* lcd pin functions
*/
#define LCD_PIN_FUNC(a, b) \
	void _ ## a ## _set() { SBI(LCD_PORT,(LCD_ ## b)); } \
	void _ ## a ## _clr() { CBI(LCD_PORT,(LCD_ ## b)); }

LCD_PIN_FUNC(rst, RST)
LCD_PIN_FUNC(cs, CS)
LCD_PIN_FUNC(sda, SDA)
LCD_PIN_FUNC(clk, CLK)

/*----------------------------------------------------------------------------------------------------------------
* hardware functions
*/
static uint16_t ShiftBit[] = {0x100,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

void _nlcdSend(uint16_t data)
{
    _cs_clr();

        if(data & ShiftBit[0]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[1]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[2]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[3]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[4]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[5]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[6]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[7]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
        if(data & ShiftBit[8]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();

    _cs_set();
}

uint8_t __nlcdRead(void)
{
	uint8_t data = 0;
	/*Read Bits*/
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;
	_clk_set();	_clk_clr(); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0;

//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();
//	_clk_clr();_delay_us(100); data<<=1; data|=((LCD_PIN&(1 << LCD_SDA))) ? 1:0; _clk_set();

	return data;
}

void _nlcdRead(uint8_t Reg,uint8_t *Readbuffer,uint8_t NRead)
{
	uint16_t data = SPFD54124B_SEND_CMD | Reg;
	_cs_clr();

	/*Send Command*/
	if(data & ShiftBit[0]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[1]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[2]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[3]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[4]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[5]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[6]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[7]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();
	if(data & ShiftBit[8]) _sda_set(); else _sda_clr();_clk_set();_clk_clr();

	/*Now Input Data Line And PullUp It*/
	LCD_DDR &= ~(1 << LCD_SDA);
	_sda_set();

	if(NRead==1)
	{
		*Readbuffer = __nlcdRead();
	}
	else
	{
		_clk_set();_clk_clr();	/*send Dummy Clock Cycle*/
		while(NRead--)
		{
			*Readbuffer++ = __nlcdRead();
		}
	}


	_cs_set();

	/*Make Data Line As Output Again*/
	LCD_DDR |= (1 << LCD_SDA);
}
/*----------------------------------------------------------------------------------------------------------------
* private functions
*/

void _nlcdSendCmd(uint8_t data)  { _nlcdSend(SPFD54124B_SEND_CMD | data); }
void _nlcdSendData(uint8_t data) { _nlcdSend(SPFD54124B_SEND_DATA | data); }

void _nlcdCmd1616(uint8_t cmd, uint16_t a, uint16_t b)
{
	_nlcdSendCmd(cmd);
	_nlcdSendData(a>>8);
	_nlcdSendData(a);
	_nlcdSendData(b>>8);
	_nlcdSendData(b);
}

void _nlcdSetWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
//	x += LCD_X_OFFSET;
//	y += LCD_Y_OFFSET;
/*#ifdef LCD_ROTATE90
	_nlcdCmd1616(SPFD54124B_CMD_CASET, y, y+h-1);	// column start/end
	_nlcdCmd1616(SPFD54124B_CMD_RASET, LCD_MAX_X-x-w, LCD_MAX_X-x-1);	// page start/end
#else*/
	_nlcdCmd1616(SPFD54124B_CMD_CASET, x, x+w-1);	// column start/end
	_nlcdCmd1616(SPFD54124B_CMD_RASET, y, y+h-1);	// page start/end
//#endif
	_nlcdSendCmd(SPFD54124B_CMD_RAMWR);				// RAMWR
}

void _nlcdSendPixel(rgb_color16bit color)
{
	_nlcdSendData(color >> 8);
	_nlcdSendData(color & 0xFF);
}

void _nlcdSenPixels(rgb_color16bit color, uint16_t n)
{
	while(n--) _nlcdSendPixel(color);
}

/*----------------------------------------------------------------------------------------------------------------
* public functions
*/
const uint16_t _lcd_init_list[] =
{
	SPFD54124B_CMD_SLPOUT,
	SPFD54124B_CMD_COLMOD, SPFD54124B_SEND_DATA | SPFD54124B_CMD_COLMOD_MCU16bit,
	SPFD54124B_CMD_DISPON,
	SPFD54124B_CMD_INVOFF,
	SPFD54124B_CMD_NORON
};

void nlcdInit()
{
	// write 1 to rst and cs
	LCD_PORT |= (1 << LCD_RST) | (1 << LCD_CS) | (1 << LCD_SDA);
	// init lcd pins
	LCD_DDR |= (1 << LCD_RST) | (1 << LCD_CS) | (1 << LCD_SDA) | (1 << LCD_CLK);

	_rst_clr();
	_delay_ms(500);
	_rst_set();
	_delay_ms(500);

    const uint16_t *list = &_lcd_init_list[0];
    uint8_t size = sizeof(_lcd_init_list)/sizeof(_lcd_init_list[0]);
    while(size--) _nlcdSend(*list++);
}

void nlcdClear()
{
	_nlcdSetWindow(0, 0, nlcdGetWidth(), nlcdGetHeight());
	_nlcdSenPixels(_lcd_data.bg_color, nlcdGetWidth() * nlcdGetHeight());
	_nlcdSendCmd(SPFD54124B_CMD_NOP);
	_lcd_data.charx = 0;
	_lcd_data.chary = 0;
}

void nlcdPixel(uint8_t x, uint8_t y,rgb_color16bit color)
{
	_nlcdCmd1616(SPFD54124B_CMD_CASET, x, x+1);	// column start/end
	_nlcdCmd1616(SPFD54124B_CMD_RASET, y, y+1);	// page start/end
	_nlcdSendCmd(SPFD54124B_CMD_RAMWR);			// RAMWR
	_nlcdSendData(color >> 8);
	_nlcdSendData(color & 0xFF);
}
void nlcdSetBackgroundColor(rgb_color16bit color)
{
	_lcd_data.bg_color = color;
}

void nlcdGotoCharXY(uint8_t x, uint8_t y)
{
	_lcd_data.charx = (_lcd_data.font_desc.width + _lcd_data.font_desc.h_spacing) * x;
	_lcd_data.chary = (_lcd_data.font_desc.height + _lcd_data.font_desc.v_spacing) * y;
}

void nlcdCharXY(uint8_t x, uint8_t y, rgb_color16bit color, char c)
{
	nlcdGotoCharXY(x, y);
	nlcdChar(color, c);
}

void nlcdChar(rgb_color16bit color, char c)
{
	if(c > nlcdFontLastChar()) return;


	_nlcdSetWindow(_lcd_data.charx, _lcd_data.chary, _lcd_data.charw, _lcd_data.charh);

	// shift char x
	_lcd_data.charx += _lcd_data.charw;
	if(_lcd_data.charx + _lcd_data.charw >= nlcdGetWidth()) {
		// zero char x
		_lcd_data.charx = 0;
		// shift char y
		_lcd_data.chary += _lcd_data.charh;
		if(_lcd_data.chary + _lcd_data.charh >= nlcdGetHeight()) {
			_lcd_data.charx = 0;
			_lcd_data.chary = 0;
		}
	}

/*#ifdef LCD_ROTATE90
	_nlcdSenPixels(_lcd_data.bg_color, (_lcd_data.font_desc.height+_lcd_data.font_desc.v_spacing)*_lcd_data.font_desc.h_spacing);
	for(uint8_t i=_lcd_data.font_desc.width; i--;) {
		uint8_t data = pgm_read_byte(&(_lcd_data.font_data[((uint8_t)c - 32)*_lcd_data.font_desc.width + i]));
		for(uint8_t j=0; j<8; j++) {
			if( data & (1 << j) )
				_nlcdSendPixel(color);
			else
				_nlcdSendPixel(_lcd_data.bg_color);
		}
	}
#else*/
	for(uint8_t j=0; j<_lcd_data.font_desc.height+_lcd_data.font_desc.v_spacing; j++)
	{
		for(uint8_t i=0; i<_lcd_data.font_desc.width; i++)
		{
			uint8_t data = pgm_read_byte(&(_lcd_data.font_data[((uint8_t)c - 32)*_lcd_data.font_desc.width + i]));
			if( data & (1 << j) )
				_nlcdSendPixel(color);
			else
				_nlcdSendPixel(_lcd_data.bg_color);
		}
		_nlcdSendPixel(_lcd_data.bg_color);
	}
}

void nlcdSetFont(const uint8_t* font)
{
	memcpy_P(&_lcd_data.font_desc, font, sizeof(_lcd_data.font_desc));
	_lcd_data.font_data = font + _lcd_data.font_desc.header_offset;
	_lcd_data.charw = _lcd_data.font_desc.width + _lcd_data.font_desc.h_spacing;
	_lcd_data.charh = _lcd_data.font_desc.height + _lcd_data.font_desc.v_spacing;
}

char nlcdFontLastChar()
{
	return _lcd_data.font_desc.char_offset + _lcd_data.font_desc.number;
}

char nlcdFontFirstChar()
{
	return _lcd_data.font_desc.char_offset;
}

void nlcdString(rgb_color16bit color, const char* str)
{
	while(*str) nlcdChar(color, *str++);
}

void nlcdStringXY(char x, char y, rgb_color16bit color, const char* str)
{
	nlcdGotoCharXY(x, y);
	nlcdString(color, str);
}

void nlcdStringP(rgb_color16bit color, const char* str)
{
	char c = pgm_read_byte(str);
	while(c) {
		nlcdChar(color, c);
		c = pgm_read_byte(++str);
	}
}

void nlcdStringXYP(char x, char y, rgb_color16bit color, const char* str)
{
	nlcdGotoCharXY(x, y);
	nlcdStringP(color, str);
}

void nlcdSetOrientation(uint8_t or)
{
	uint8_t data = 0;
	_lcd_data.orientation = or;

	switch(or)
	{
		case LCD_ORIENTATION_90:
			data = SPFD54124B_CMD_MADCTR_MV | SPFD54124B_CMD_MADCTR_MX;
			break;
		case LCD_ORIENTATION_180:
			data = SPFD54124B_CMD_MADCTR_MY | SPFD54124B_CMD_MADCTR_MX;
			break;
		case LCD_ORIENTATION_270:
			data = SPFD54124B_CMD_MADCTR_MV | SPFD54124B_CMD_MADCTR_MY;
			break;
	}
	_nlcdSendCmd(SPFD54124B_CMD_MADCTR);
	_nlcdSendData(data);
}

uint8_t nlcdGetWidth()
{
	switch(_lcd_data.orientation)
	{
		case LCD_ORIENTATION_NORMAL:
		case LCD_ORIENTATION_180:
			return LCD_CTRL_WIDTH;
	}
	return LCD_CTRL_HEIGHT;
}

uint8_t nlcdGetHeight()
{
	switch(_lcd_data.orientation)
	{
		case LCD_ORIENTATION_NORMAL:
		case LCD_ORIENTATION_180:
		return LCD_CTRL_HEIGHT;
	}
	return LCD_CTRL_WIDTH;
}
