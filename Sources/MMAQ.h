/*
 * mma8451q.h
 *
 *  Created on: Aug 11, 2016
 *      Author: APS3KOR
 */

#ifndef MMA8451Q_H_
#define MMA8451Q_H_

typedef unsigned int UINT;
typedef int INT;
typedef unsigned char UCHAR;
typedef void VOID;
typedef unsigned long ULNG;

#define CTRL_REG1 			0x2A
#define CTRL_REG2			0x2B
#define CTRL_REG4			0x2D
#define CTRL_REG5			0x2E
#define WHO_AM_I 			0x0D
#define XYZ_DATA_CFG    	0X0E
#define STATUS_F_STATUS		0X00
#define OFF_X				0x2F
#define OFF_Y				0x30
#define OFF_Z				0x31
#define TRANSIENT_CFG		0x1D
#define TRANSIENT_THS		0x1F
#define TRANSIENT_COUNT		0X20
#define TRANSIENT_SRC		0x1E

VOID init_config(VOID);
VOID pause(VOID);
UCHAR mma8451q_read(UCHAR register_address);
VOID mma8451q_write(UCHAR register_address, UCHAR data);
VOID mma8451q_read_default(VOID);
VOID mma8451q_get(short* cordinate);
VOID mma8451q_calibrate(VOID);
VOID mma8451q_threshold(VOID);
VOID mma8451q_init(VOID);
VOID isr_acc(VOID);
int main_accelerometer(VOID);

#endif /* MMA8451Q_H_ */
