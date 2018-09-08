#ifndef SPFD54124B_H
#define SPFD54124B_H

#define SPFD54124B_SEND_CMD		0
#define SPFD54124B_SEND_DATA	0x100

#define SPFD54124B_CMD_NOP		0x00
#define SPFD54124B_CMD_SLPOUT	0x11
#define SPFD54124B_CMD_NORON	0x13

#define SPFD54124B_CMD_INVOFF	0x20
#define SPFD54124B_CMD_DISPON	0x29
#define SPFD54124B_CMD_CASET	0x2A
#define SPFD54124B_CMD_RASET	0x2B
#define SPFD54124B_CMD_RAMWR	0x2C
#define SPFD54124B_CMD_RGBSET	0x2D

#define SPFD54124B_CMD_MADCTR	0x36
#define SPFD54124B_CMD_VSCSAD	0x37
#define SPFD54124B_CMD_COLMOD	0x3A

#define SPFD54124B_CMD_COLMOD_MCU12bit	3			// MCU interface 12bit
#define SPFD54124B_CMD_COLMOD_MCU16bit	5			// MCU interface 16bit
#define SPFD54124B_CMD_COLMOD_MCU18bit	6			// MCU interface 18bit
#define SPFD54124B_CMD_COLMOD_RGB16bit	50			// RGB interface 16bit
#define SPFD54124B_CMD_COLMOD_RGB18bit	60			// RGB interface 18bit

#define SPFD54124B_CMD_MADCTR_MY	(1 << 7)		// Row Address Order
#define SPFD54124B_CMD_MADCTR_MX	(1 << 6)		// Column Address Order
#define SPFD54124B_CMD_MADCTR_MV	(1 << 5)		// Row/Column Exchange
#define SPFD54124B_CMD_MADCTR_ML	(1 << 4)		// Vertical Refresh Order
#define SPFD54124B_CMD_MADCTR_RGB	(1 << 3)		// RGB-BGR ORDER

#endif