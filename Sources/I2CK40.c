/*
 * k40_i2c.c
 *
 *  Created on: Aug 11, 2016
 *      Author: APS3KOR
 */

#include "common.h"
#include "I2CK40.h"


/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_init                                                                      */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : Initialising I2C                                                              */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_init(VOID)
{
	//Turn on clock to I2C1 module
	SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;   
	// Configure GPIO for I2C1 function    								 
	PORTC_PCR11 = PORT_PCR_MUX(2);
	PORTC_PCR10 = PORT_PCR_MUX(2);
	//Set MULT and ICR , PG 1311
	I2C1_F  = 0x14;  
	//Enable IIC , PG 1312
	I2C1_C1 = I2C_C1_IICEN_MASK;        
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_start                                                                     */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : Setting the start bit/Transmit mode for i2c protocol                          */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_start(VOID)
{
	//TRANSMITTER MODE IS SET, Pg 1312
	I2C1_C1 |= 0x10; 
	//Master Mode select 
	I2C1_C1 |= I2C_C1_MST_MASK; 
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_repeat_start                                                              */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : Setting the repeat start bit for i2c protocol                                 */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/
VOID i2c_repeat_start(VOID)
{
	//Repeat start provided by master, page 1313
	I2C1_C1 |= I2C_C1_RSTA_MASK; 
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_wait                                                                      */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : Wait for data                                                                 */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_wait(VOID)
{
	//Status register, page 1315
	while((I2C1_S & I2C_S_IICIF_MASK)==0); 
	I2C1_S |= I2C_S_IICIF_MASK;
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_write                                                                     */
/*                                                                                               */
/* Input(s) : Data                                                                               */
/* Output : None                                                                                 */
/* Functionality : Writing data                                                                  */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_write(UCHAR data)
{
	I2C1_D = data;
	i2c_wait();
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_disable_ack                                                               */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : NAK set		                                                                 */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_disable_ack(VOID)
{
	//page 1313; NAK 
	I2C1_C1 |= I2C_C1_TXAK_MASK; 
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_enter_rx_mode                                                             */
/*                                                                                               */
/* Input(s) : Acknowledgement                                                                    */
/* Output : None                                                                                 */
/* Functionality : Enable receive mode                                                           */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_enter_rx_mode(UCHAR ack)
{
	//Enter RX mode if in TX mode
	I2C1_C1   &= ~I2C_C1_TX_MASK;	
	if(ack)
	{
		//If ACK required, Enable ACK
		I2C1_C1   &= ~I2C_C1_TXAK_MASK;

	}
	else
	{
		//Disable ACK
		I2C1_C1 |= I2C_C1_TXAK_MASK;
	}
		
	
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_read                                                                      */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : data                                                                                 */
/* Functionality : Reads data and turns the same                                                 */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

UCHAR i2c_read(VOID)
{
	UCHAR result;

	//Ack received in RXAK
	
	i2c_enter_rx_mode(0); 
	/* dummy read */
	result = I2C1_D ;
	i2c_wait();

	result = I2C1_D ;
	i2c_wait();

	return result;
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : i2c_stop                                                                      */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : Stop bit/ stop transmission set                                               */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID i2c_stop(VOID)
{
	I2C1_C1  &= ~I2C_C1_MST_MASK;
	I2C1_C1  &= ~I2C_C1_TX_MASK;
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : time_delay_ms                                                                 */
/*                                                                                               */
/* Input(s) :Count Value                                                                         */
/* Output : None                                                                                 */
/* Functionality :Generation of delay as required                                                */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 19th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID time_delay_ms(UINT count_val)
{
	//Turn on clock to LPTMR module
	SIM_SCGC5|=SIM_SCGC5_LPTIMER_MASK; 
	//Set compare value
	LPTMR0_CMR = count_val; 
	//Use 1Khz LPO clock and bypass prescaler
	LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK; 
	//Start counting
	LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; 
	//Wait for counter to reach compare value
	while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK)) {}
	//Clear Timer Compare Flag
	LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK; 
	return;
}
