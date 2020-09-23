/*
 * k40_i2c.h
 *
 *  Created on: Aug 11, 2016
 *      Author: APS3KOR
 */

#ifndef K40_I2C_H_
#define K40_I2C_H_

#define NO_ACK 0x00
#define ACK  0x01

typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef void VOID;

void i2c_init(void);
void i2c_start(void);
VOID i2c_repeat_start(VOID);
VOID i2c_wait(VOID);
VOID i2c_write(UCHAR data);
VOID i2c_disable_ack(VOID);
VOID i2c_enter_rx_mode(UCHAR ack);
UCHAR i2c_read(VOID);
VOID i2c_stop(VOID);
VOID time_delay_ms(UINT count_val);


#endif /* K40_I2C_H_ */

