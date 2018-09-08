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

#include <avr/io.h>
#include <util/delay.h>
#include <nokia1661_lcd_driver.h>
#include <lcd_font5x7.h>

int main(void)
{
	nlcdInit();

	nlcdSetBackgroundColor(LCD_VGA_RED);
	nlcdClear();

	nlcdSetBackgroundColor(LCD_VGA_BLUE);
	nlcdClear();

	nlcdSetBackgroundColor(LCD_VGA_GREEN);
	nlcdClear();

	nlcdSetBackgroundColor(LCD_VGA_WHITE);
	nlcdSetFont(font5x7latcyr);
	nlcdClear();

	nlcdGotoCharXY(1,1);
	nlcdStringP(LCD_VGA_RED, PSTR("Sisoog.Com"));
	_delay_ms(250);

	nlcdSetOrientation(LCD_ORIENTATION_90);
	nlcdGotoCharXY(1,1);
	nlcdStringP(LCD_VGA_GREEN, PSTR("Sisoog.Com"));
	_delay_ms(250);

	nlcdSetOrientation(LCD_ORIENTATION_180);
	nlcdGotoCharXY(1,1);
	nlcdStringP(LCD_VGA_BLUE, PSTR("Sisoog.Com"));
	_delay_ms(250);

	nlcdSetOrientation(LCD_ORIENTATION_270);
	nlcdGotoCharXY(1,1);
	nlcdStringP(LCD_VGA_PURPLE, PSTR("Sisoog.Com"));
	_delay_ms(250);

	nlcdSetOrientation(LCD_ORIENTATION_NORMAL);

	for(int i=0;i<32;i++)
		nlcdPixel(64+i,64,LCD_VGA_RED);

	for(int i=0;i<32;i++)
		nlcdPixel(64,64+i,LCD_VGA_PURPLE);

	for(int i=0;i<32;i++)
		nlcdPixel(64+i,64+31,LCD_VGA_BLUE);

	for(int i=0;i<32;i++)
		nlcdPixel(64+31,64+i,LCD_VGA_GREEN);

	while(1)
	{

	}
	return 0;
}
