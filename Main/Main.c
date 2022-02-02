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

#/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <nokia1661_lcd_driver.h>
#include <lcd_font5x7.h>
// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#if defined(LCD_STM_HW)
void delay_ms(uint32_t __IO delay)
{
	delay *=((SystemCoreClock/1000000)/5)*643;
	while(delay--);
}
#endif

int
main(int argc, char* argv[])
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

	uint8_t ReadID[3] = {0};
	uint8_t RDDST[4];
	_nlcdRead(0x04,ReadID,3);	/* Read Display ID */
	_nlcdRead(0x09,RDDST,4);	/* Read Display Status */

	char temp[20];
	sprintf(temp,"RDDID:%X %X %X",ReadID[0],ReadID[1],ReadID[2]);
	nlcdGotoCharXY(1,1);
	nlcdString(LCD_VGA_RED,temp);

	sprintf(temp,"RDDST:%X %X %X %X",RDDST[0],RDDST[1],RDDST[2],RDDST[3]);
	nlcdGotoCharXY(1,2);
	nlcdString(LCD_VGA_RED,temp);

//	nlcdGotoCharXY(1,1);
//	nlcdStringP(LCD_VGA_RED, PSTR("Sisoog.Com"));
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
	
	
	
	// Display image stored on image.h
	
	nlcdSetBackgroundColor(LCD_VGA_WHITE);
	nlcdClear();
	
	nlcdPixel(0,0,LCD_VGA_GREEN); 
	// there is a bug: in Nokia C1 the nlcdPixel not work in first call! and we call nlcdPixel one time before display image to resolve this bug
	// note that if dont call nlcdPixel, the first pixel of image not shown!
	
	
	//display image: (give h and w of image manualy from image.h)
	for(int y=0; y<25; y++){ //h
		for(int x=0; x<25; x++){ //w
			nlcdPixel( 10+x,10+y, pgm_read_word(&(image1[y][x])) );		
		}
	}
	
	
	
	
	
	
  // Infinite loop
  while (1)
  {

  }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
