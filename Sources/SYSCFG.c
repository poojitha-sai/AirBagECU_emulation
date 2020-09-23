/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "common.h"
#include "derivative.h" /* include peripheral declarations */
#include "MMAQ.h"
#include "CLCD.h"
#include "IGNTN.h"
#include "SYSCFG.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : init_leds                                                                     */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Configuration of all LEDs                                                     */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 18th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/

VOID init_leds(VOID)
{
	
	//Clock config for Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; 
	//Clock config for Port B
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	
	//Clock for timer
	
	SIM_SCGC6|= SIM_SCGC6_PIT_MASK;
	
	//Enable GPIO for all LEDs
	
	PORTC_PCR7 |= PORT_PCR_MUX(1);
	PORTC_PCR8 |= PORT_PCR_MUX(1);
	PORTC_PCR9 |= PORT_PCR_MUX(1);
	PORTB_PCR11 |= PORT_PCR_MUX(1);
	
	// Setting Port C and Port B as output
	
	GPIOC_PDDR |=GPIO_PDDR_PDD(1<<7);	
	GPIOC_PDDR |=GPIO_PDDR_PDD(1<<8);
	GPIOC_PDDR |=GPIO_PDDR_PDD(1<<9);
	GPIOB_PDDR |=GPIO_PDDR_PDD(1<<11);
	
	// Turning off all LEDs
	
	GPIOC_PSOR |= GPIO_PSOR_PTSO(1<<7);
	GPIOC_PSOR |= GPIO_PSOR_PTSO(1<<8);
	GPIOC_PSOR |= GPIO_PSOR_PTSO(1<<9);
	GPIOB_PSOR |= GPIO_PSOR_PTSO(1<<11);

}

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : init_switch                                                                   */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Configuration of all switch                                                   */
/*                                                                                               */
/* Member of : -                                                                                 */
/* Friend of : -                                                                                 */
/*                                                                                               */
/* Author(s) : Batch6_Team2                                                                      */
/* Date Created : 18th August,2016                                                               */
/* Modifications : - None   													                 */
/* - Modification Details                                                                        */
/*                                                                                               */
/*************************************************************************************************/


VOID init_switch(VOID)
{
	// Enable clock for Port C
	SIM_SCGC5|= SIM_SCGC5_PORTC_MASK;
	
	//Enable GPIO for the switched on PCR5 and PCR 13
	
	PORTC_PCR13= PORT_PCR_MUX(1)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTC_PCR5|= PORT_PCR_MUX(1)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;

	//Enable the Port pins 5 and 13 as inputs
	
	GPIOC_PDDR &= ~ (GPIO_PDDR_PDD(1<<13));
	GPIOC_PDDR &= ~ (GPIO_PDDR_PDD(1<<5));

	GPIOC_PSOR|= GPIO_PSOR_PTSO(1<<9);
	GPIOB_PSOR|= GPIO_PSOR_PTSO(1<<11);
}

int main(VOID)
{
	// Initialise all LEDs
	 init_leds();
	 
	 //Initializing LCD display
	 
	 display_init();	 
	 
	 // Initiate Ignition Module
	 
	 main_ignition();	
	  
 
	 return 0;
}
