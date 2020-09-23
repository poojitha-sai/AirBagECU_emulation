/*
 * ignition.c
 *
 *  Created on: Aug 19, 2016
 *      Author: APS3KOR
 */

#include "derivative.h" /* include peripheral declarations */
#include "IGNTN.h"
#include "SYSCFG.h"
#include "SBELT.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : green_led                                                                     */
/*                                                                                               */
/* Input(s) :None                                                                                */
/* Output : None                                                                                 */
/* Functionality : Turns on Green LED on ignition key press                                      */
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


VOID green_led(VOID)
{
	static int once = 1;

	// Use of Switch on pin 13 as ignition 

	if(((~GPIOC_PDIR) & 0x2000) && once)
	{
		// To control the LEDs as edge triggered
		once=0;

		// GREEN LED is toggled on key press
		GPIOC_PTOR |= GPIO_PTOR_PTTO(1<<9);

	}

	else if((GPIOC_PDIR & 0x2000))
	{
		once=1;
	}

	//Check if ignition is on and insert seat belt

	if(((~GPIOC_PDOR) & 0x0200))
		main_seatbelt();


}


int main_ignition(VOID)
{
	//To glow/dim GREEN LED on ignition

	init_switch();
	while(1)
	{
		green_led();

	}

	return 0;
}
