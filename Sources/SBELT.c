/*
 * seat_belt.c
 *
 *  Created on: Aug 19, 2016
 *      Author: APS3KOR
 */

#include "derivative.h" /* include peripheral declarations */
#include "CLCD.h"
#include "MMAQ.h"
#include "SYSCFG.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  blue_led                                                       	 	         */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Detection of seat belt to activate ACS  									     */
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

VOID blue_led(VOID)
{
	static int once1 = 1;
	// Use of Switch on pin 5 as seat belt

	if(((~GPIOC_PDIR) & 0x0020) && once1)
	{
		//CLEAR_DISP_SCREEN;
		once1=0;
		GPIOB_PTOR |= GPIO_PTOR_PTTO(1<<11);
		if(((~GPIOB_PDOR) & 0x0800))
		{
			//Display at first position on first line of LCD
			display_print("ACS Activated   ", 0x80);
			//Display at first position on second line of LCD
			display_print("                ", 0xC0);
			main_accelerometer();
		}

	}
	else if((GPIOC_PDIR & 0x0020))
	{
		//CLEAR_DISP_SCREEN;
		once1=1;
		if(!((~GPIOB_PDOR) & 0x0800))
		{
			//Display at first position on first line of LCD
			display_print("Insert Seat Belt", 0x80);
			//Display at first position on second line of LCD
			display_print("ACS disabled", 0xC0);			
			//Disable interrupt
			PORTC_PCR12 &= 	PORT_PCR_IRQC(00);
		}
	}

}

int main_seatbelt(VOID)
{
	//To glow/dim BLUE LED on insertion of Seat Belt
	blue_led();
	return 0;
}

