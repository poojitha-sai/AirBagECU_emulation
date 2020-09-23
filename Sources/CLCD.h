/*
 * clcd.h
 *
 *  Created on: Aug 19, 2016
 *      Author: rbv2kor
 */

#ifndef CLCD_H_
#define CLCD_H_

typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef void VOID;
typedef int INT;

#define STABILIZE_LCD			display_write(0x33,0)
#define CURSOR_HOME				display_write(0X02,0)
#define DISP_ON_AND_CURSOR_OFF	display_write(0X0C,0)
#define CLEAR_DISP_SCREEN		display_write(0X01,0)

VOID display_init(VOID);
VOID display_write (UCHAR data, UCHAR control_bit);
VOID display_put_char (UCHAR data, UCHAR address);
VOID display_print (const char *data, UCHAR address);


#endif /* CLCD_H_ */
