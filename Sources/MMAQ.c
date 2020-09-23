/*
 * mma8451q.c
 *
 *  Created on: Aug 11, 2016
 *      Author: APS3KOR
 */

#include "common.h"
#include "I2CK40.h"
#include "MMAQ.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  init_config                                                       	 	     */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Checking the status of accelerometer	   									     */
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


VOID init_config(VOID)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	PORTC_PCR7 |= PORT_PCR_MUX(1);
	PORTC_PCR8 |= PORT_PCR_MUX(1);

	GPIOC_PDDR |=GPIO_PDDR_PDD(1<<7);	
	GPIOC_PDDR |=GPIO_PDDR_PDD(1<<8);

	GPIOC_PSOR |= GPIO_PSOR_PTSO(1<<7);
	GPIOC_PSOR |= GPIO_PSOR_PTSO(1<<8);

	printf("Accelerometer Check\n");
	i2c_init();
	mma8451q_read_default();
	mma8451q_init();

}


/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  pause                                                            		   	 */
/*                                                                                               */
/* Input(s) : None                                                           					 */
/* Output : None                                                                                 */
/* Functionality : generates Delay                                             				     */
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


VOID pause(VOID)
{
	INT n;
	for(n=1;n<50;n++) 
	{
		asm("nop");
	}

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_read                                                                */
/*                                                                                               */
/* Input(s) : Slave Register address                                                             */
/* Output : None                                                                                 */
/* Functionality : Read data from accelerometer                                                  */
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


UCHAR mma8451q_read(UCHAR register_address)
{
	i2c_start();
	//Slave address passed for write
	i2c_write(0x3A); 
	i2c_write(register_address);
	i2c_repeat_start();
	//Slave address passed for read
	i2c_write(0x3B); 
	UCHAR data = i2c_read();
	i2c_disable_ack();
	i2c_stop();
	pause();
	return (data);

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_write                                                               */
/*                                                                                               */
/* Input(s) : Slave Register address and data                                                    */
/* Output : None                                                                                 */
/* Functionality : Sends the data to the register                                                */
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

VOID mma8451q_write(UCHAR register_address, UCHAR data)
{
	i2c_start();
	//Slave address passed for write
	i2c_write(0x3A); 
	//Register address
	i2c_write(register_address);
	//Data to be written is passed
	i2c_write(data);
	i2c_stop();
	pause();

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_read_default                                                        */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Reads the default value of accelerometer                                      */
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


VOID mma8451q_read_default(VOID)
{
	//Prints default value for checking working of accelerometer
	UINT default_value = mma8451q_read(WHO_AM_I);
	printf(" The default value is %d \n", default_value);
	pause();

}



/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_get                                                       			 */
/*                                                                                               */
/* Input(s) : Coordinate                                                                         */
/* Output : None                                                                                 */
/* Functionality : Gets the current coordinates of the accelerometer                             */
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

VOID mma8451q_get(short* cordinate) 
{
	INT i=0;
	// The value of OUT_X_MSB (Auto increment to OUT_X_LSB, OUT_Y_MSB and so on)
	INT n=0x01; 
	short int coordinate_value[3];
	for(i=0;i<3;i++)
	{
		coordinate_value[i]= mma8451q_read(n++);
		coordinate_value[i]= coordinate_value[i]<<8;
		coordinate_value[i]|= mma8451q_read(n++);
		coordinate_value[i]=coordinate_value[i]>>2;
	}

	cordinate[0] = coordinate_value[0];
	cordinate[1] = coordinate_value[1];
	cordinate[2] = coordinate_value[2];



}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_calibrate                                                       	 */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Calibrates coordinates of the accelerometer for flat surface                  */
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


VOID mma8451q_calibrate(VOID)
{
	UCHAR read_val=0;
	static short cordinate[3];
	// Control Reg 1 to stand by mode
	mma8451q_write(CTRL_REG1,0x3C);
	// Control Reg 2 to reset on Power ON	
	mma8451q_write(CTRL_REG2,0x40);           	

	//If reset is enabled, stay in loop
	do
	{
		read_val= mma8451q_read(CTRL_REG2) & 0x40; 
	} while(read_val);

	//Page 6, AN4069 2g Mode
	mma8451q_write(XYZ_DATA_CFG,0x00); 
	//Control Register 2 to high resolution mode
	//mma8451q_write(CTRL_REG2,0x02);
	
	//Control Register 1 ,1.5kHz Active mode
	mma8451q_write(CTRL_REG1,0x3D);   

	while(!read_val)
	{
		//Check if overwrite has occurred on ZYXDR bit of Status Register
		read_val= mma8451q_read(STATUS_F_STATUS) & 0x08;
	}

	mma8451q_get(cordinate);

	cordinate[0]=(cordinate[0]/8)*(-1);
	cordinate[1]=(cordinate[1]/8) *(-1);
	cordinate[2]=cordinate[2]-4096;
	cordinate[2]=(cordinate[2]/8)*(-1);

	//Control Reg1, to put in Standby Mode
	mma8451q_write(CTRL_REG1, 0x00);      	   
	mma8451q_write(OFF_X, cordinate[0]);
	mma8451q_write(OFF_Y, cordinate[1]);
	mma8451q_write(OFF_Z, cordinate[2]);

	//Control Register 1 ,1.5kHz Active mode
	mma8451q_write(CTRL_REG1,0x3D);  
	
	//printf("The caliberated values are : \n");
	//printf("X:%d, y:%d, z:%d\n", cordinate[0], cordinate[1],cordinate[2]);
	pause();
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_threshold                                                       	 */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Compares the threshold for crash detection and generates interrupt          */
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

VOID mma8451q_threshold(VOID)
{
	PORTC_PCR12 |= 	PORT_PCR_PE_MASK;
	PORTC_PCR12 |= 	PORT_PCR_PS_MASK;
	PORTC_PCR12 |= 	PORT_PCR_MUX(1);
	PORTC_PCR12 |= 	PORT_PCR_IRQC(10);

	NVICICPR2|= (1<<(89%32));
	NVICISER2|= (1<<(89%32));
	
	UCHAR data;

	//Stand by mode
	mma8451q_write(CTRL_REG1, 0x18);
	//Configuration
	mma8451q_write(TRANSIENT_CFG, 0x17);
	//Setting the threshold - 1g
	mma8451q_write(TRANSIENT_THS, 0x10); 
	//Transient count
	mma8451q_write(TRANSIENT_COUNT,0x01);
	//Interrupt detection
	mma8451q_write(CTRL_REG4,0x20);
	//Sends it to INT1
	mma8451q_write(CTRL_REG5,0x20); 
	
	//Active mode	
	data=mma8451q_read(CTRL_REG1);
	data|= 0x01;
	mma8451q_write(CTRL_REG1, data); 

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  mma8451q_init                                                       	     */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality :Initialisation of accelerometer    										     */
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
VOID mma8451q_init(VOID)
{
	mma8451q_calibrate();
	mma8451q_threshold();
	//Disabling the Tap detection
	//mma8451q_write(0x21,0x00); 
	//Put to active mode, enable in auto sleep; Page 46 of Main acc file
	//mma8451q_write(CTRL_REG2,0x04); 
}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  isr_acc                                                       	 		     */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality :Interrupt for crash detection		   										     */
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

VOID isr_acc(VOID)
{
	//Value corresponding to 30ms
	ULNG side_time= 0x2BF1FF; 
	//Value corresponding to 50ms
	ULNG front_time = 0x493DFF;

	ULNG difference =0;
	ULNG cval_count = 0;
	UCHAR sourceTrans;
	ULNG time;

	PIT_MCR=0X00;

	//Load maximum value (count down reg)
	PIT_LDVAL1=0XFFFFFFFF; 
	
	//PIT_TCTRL1=0X02; //ENABLE
	
	//START
	PIT_TCTRL1=0X03; 

	//Clear the interrupt flag
	PORTC_ISFR=0XFFFFFFFF;

	//Check occurrence of an event in X or Y direction
	sourceTrans = mma8451q_read(TRANSIENT_SRC);

	if((sourceTrans & 0x08)==0x08)
	{
		cval_count = PIT_CVAL1;
		//side crash function to be called
		GPIOC_PCOR |= GPIO_PCOR_PTCO(1<<8);
		PIT_LDVAL1=0XFFFFFFFF;
		difference = 0xFFFFFFFF - cval_count;
		time= (difference+1)/(96);
		if(difference <= side_time)
		{
			printf("The side airbag was deployed within %lu counts \n", difference);
			printf("The side airbag was deployed within %lu micro seconds \n\n\n", time);
			PIT_TCTRL1=0X00;
		}

		else 
			printf("fail");

	}

	if((sourceTrans & 0x02)==0x02)
	{
		cval_count = PIT_CVAL1;
		//front crash function to be called		
		GPIOC_PCOR |= GPIO_PCOR_PTCO(1<<7);
		PIT_LDVAL1=0XFFFFFFFF;
		difference = 0xFFFFFFFF - cval_count;
		time= (difference+1)/(96);
		if(difference <= front_time)
		{			
			printf("The front airbag was deployed within %lu  counts \n", difference);
			printf("The front airbag was deployed within %lu micro seconds \n\n\n", time);
			PIT_TCTRL1=0X00;
		}

		else 
			printf("fail");

	}

}

int main_accelerometer(VOID)
{
	//static short cordinate[3];
	init_config();
#if 0
	while(1)
	{
		mma8451q_get(cordinate);
		printf("X:%d, y:%d, z:%d\n", cordinate[0], cordinate[1],cordinate[2]);
		time_delay_ms(500);	

	}
#endif
	return 0;
}
