/*
 * nokia1661_Hw.h
 *
 *  Created on: Sep 11, 2019
 *      Author: zeus
 */

#ifndef NOKIA1661_HW_H_
#define NOKIA1661_HW_H_

#define LCD_AVR_HW		1
//#define LCD_STM_HW		1

#if defined(LCD_AVR_HW) && defined(LCD_STM_HW)
#error Only Select One Hardware AVR/STM
#endif
#if !defined(LCD_AVR_HW) && !defined(LCD_STM_HW)
#error You need to define Hardware Type for LCD usage
#endif

#ifdef LCD_AVR_HW

#define LCD_PORT		PORTB
#define LCD_PIN			PINB
#define LCD_DDR			DDRB

#define LCD_RST			PINB1
#define LCD_CS			PINB2
#define LCD_SDA			PINB3
#define LCD_CLK			PINB5

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define SBI(port,bit) 	asm("sbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit))
#define CBI(port,bit) 	asm("cbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit))
#define LCD_RSDA()		(LCD_PIN&(1 << LCD_SDA))
#define LCD_GPIO_Enable()
#define _sda_In()		LCD_DDR &=~(1<<LCD_SDA)
#define _sda_Out()		LCD_DDR |= (1<<LCD_SDA)

#define _rst_set()	SBI(LCD_PORT,LCD_RST)
#define _rst_clr()	CBI(LCD_PORT,LCD_RST)
#define _cs_set()	SBI(LCD_PORT,LCD_CS)
#define _cs_clr()	CBI(LCD_PORT,LCD_CS)
#define _sda_set()	SBI(LCD_PORT,LCD_SDA)
#define _sda_clr()	CBI(LCD_PORT,LCD_SDA)
#define _clk_set()	SBI(LCD_PORT,LCD_CLK)
#define _clk_clr()	CBI(LCD_PORT,LCD_CLK)
#define _Init_GPIO()	LCD_DDR |= (1 << LCD_RST) | (1 << LCD_CS) | (1 << LCD_SDA) | (1 << LCD_CLK)

#elif defined(LCD_STM_HW)
#include <stm32f10x.h>
#include <string.h>

#define LCD_PORT			GPIOA
#define LCD_GPIO_Enable()	RCC->APB2ENR |= (1<<2)

#define LCD_RST				7
#define LCD_CS				6
#define LCD_SDA				5
#define LCD_CLK				4

#define LCD_RSDA()			(LCD_PORT->IDR&(1<<LCD_SDA))
#define SBI(port,bit) 		port->BSRR = (1<<bit)
#define CBI(port,bit) 		port->BRR  = (1<<bit)

#define memcpy_P			memcpy
#define PROGMEM
#define PSTR(x)				(x)
#define pgm_read_byte(x)	*(x)
#define _delay_ms(x)		delay_ms(x) /*Define this Function in External Source*/

#define _rst_set()	SBI(LCD_PORT,LCD_RST)
#define _rst_clr()	CBI(LCD_PORT,LCD_RST)
#define _cs_set()	SBI(LCD_PORT,LCD_CS)
#define _cs_clr()	CBI(LCD_PORT,LCD_CS)
#define _sda_set()	SBI(LCD_PORT,LCD_SDA)
#define _sda_clr()	CBI(LCD_PORT,LCD_SDA)
#define _clk_set()	SBI(LCD_PORT,LCD_CLK)
#define _clk_clr()	CBI(LCD_PORT,LCD_CLK)

#if(LCD_RST<8)
#define _rst_Out()	LCD_PORT->CRL &=~(0xF<<(4*LCD_RST));\
					LCD_PORT->CRL |= (0x3<<(4*LCD_RST));
#else
#define _rst_Out()	LCD_PORT->CRH &=~(0xF<<(4*LCD_RST));\
					LCD_PORT->CRH |= (0x3<<(4*LCD_RST));
#endif
#if(LCD_CS<8)
#define _cs_Out()	LCD_PORT->CRL &=~(0xF<<(4*LCD_CS));\
					LCD_PORT->CRL |= (0x3<<(4*LCD_CS));
#else
#define _cs_Out()	LCD_PORT->CRH &=~(0xF<<(4*LCD_CS));\
					LCD_PORT->CRH |= (0x3<<(4*LCD_CS));
#endif
#if(LCD_SDA<8)
#define _sda_Out()	LCD_PORT->CRL &=~(0xF<<(4*LCD_SDA));\
					LCD_PORT->CRL |= (0x3<<(4*LCD_SDA));
#define _sda_In()	LCD_PORT->CRL &=~(0xF<<(4*LCD_SDA));\
					LCD_PORT->CRL |= (0x8<<(4*LCD_SDA));
#else
#define _sda_Out()	LCD_PORT->CRH &=~(0xF<<(4*LCD_SDA));\
					LCD_PORT->CRH |= (0x3<<(4*LCD_SDA));
#define _sda_In()	LCD_PORT->CRH &=~(0xF<<(4*LCD_SDA));\
					LCD_PORT->CRH |= (0x8<<(4*LCD_SDA));
#endif
#if(LCD_CLK<8)
#define _clk_Out()	LCD_PORT->CRL &=~(0xF<<(4*LCD_CLK));\
					LCD_PORT->CRL |= (0x3<<(4*LCD_CLK));
#else
#define _clk_Out()	LCD_PORT->CRH &=~(0xF<<(4*LCD_CLK));\
					LCD_PORT->CRH |= (0x3<<(4*LCD_CLK));
#endif

#define _Init_GPIO() { _rst_Out(); _cs_Out(); _sda_Out(); _clk_Out();}

#endif


#endif /* NOKIA1661_HW_H_ */
