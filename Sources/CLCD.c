
#include "derivative.h" /* include peripheral declarations */
#include "CLCD.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : display_init                                                                  */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Configuration/Initialization of CLCD                                          */
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

VOID display_init(VOID)
{
	// initialise the clock

	SIM_SCGC5|= SIM_SCGC5_PORTE_MASK; 

	// Initialise the Ports of the LCD	

	//Initialise RS bit
	PORTE_PCR6 |= PORT_PCR_MUX(1);

	//Initialise R/W Bit
	PORTE_PCR7 |= PORT_PCR_MUX(1);

	//Data enable
	PORTE_PCR8 |= PORT_PCR_MUX(1);

	//Data ports
	PORTE_PCR9  |= PORT_PCR_MUX(1);
	PORTE_PCR10 |= PORT_PCR_MUX(1);
	PORTE_PCR11 |= PORT_PCR_MUX(1);
	PORTE_PCR12 |= PORT_PCR_MUX(1);

	//Setting Port E as output port 
	GPIOE_PDDR|=0X00001FC0;

	// R/W=0 since always write.

	GPIOE_PDOR = (GPIOE_PDOR & (~GPIO_PDOR_PDO(1<<7))); 						

	STABILIZE_LCD;
	CURSOR_HOME;
	DISP_ON_AND_CURSOR_OFF;
	CLEAR_DISP_SCREEN;
}		 

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : display_write                                                                 */
/*                                                                                               */
/* Input(s) : Data, Control Bit                                                                  */
/* Output : None                                                                                 */
/* Functionality : Writing data onto LCD                                                         */
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


VOID display_write (UCHAR data, UCHAR control_bit)
{

	INT i;
	//RS bit value= control_bit. 
	GPIOE_PDOR = (GPIOE_PDOR & (~GPIO_PDOR_PDO(1<<6))) | (control_bit<<6) ;
	// Clear data port and enable higher nibble.
	GPIOE_PDOR = (GPIOE_PDOR & 0xFFFFE1FF) | (((data>>4)&0X0F)<<9); 
	// E=1;
	GPIOE_PDOR |= GPIO_PDOR_PDO(1<<8); 	
	//Pause
	for(i=4000; i--;);	
	// E=0;
	GPIOE_PDOR = (GPIOE_PDOR & (~GPIO_PDOR_PDO(1<<8))); 	
	// Clear data port and enable higher nibble.
	GPIOE_PDOR = (GPIOE_PDOR & 0xFFFFE1FF) | ((data & 0X0F )<<9) ; 	
	// E=1;
	GPIOE_PDOR |= GPIO_PDOR_PDO(1<<8);	
	//Pause
	for(i=4000; i--;);	
	// E=0;
	GPIOE_PDOR = (GPIOE_PDOR & (~GPIO_PDOR_PDO(1<<8))); 				

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : display_put_char                                                              */
/*                                                                                               */
/* Input(s) : Data, Address                                                                      */
/* Output : None                                                                                 */
/* Functionality : Writing one character onto LCD                                                */
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


VOID display_put_char (UCHAR data, UCHAR address)
{
	// Check for the control bit.
	//Address gets selected
	display_write(address,0);		
	display_write(data,1);	

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : display_print                                                                 */
/*                                                                                               */
/* Input(s) : Data, Address                                                                      */
/* Output : None                                                                                 */
/* Functionality : Printing data onto LCD                                                        */
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


VOID display_print (const char *data, UCHAR address)
{
	//Address gets selected
	display_write(address,0);		
	while( *data!= '\0')
	{
		//Data is written serially
		display_write(*data++,1);		

	}
}

/* For testing the functionality of the display*/

#if 0
int main(VOID)
{
	display_init();
	display_print("Eshwari", 0x80);
	return 0;
}

#endif
