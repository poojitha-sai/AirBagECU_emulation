/*
 * front_crash.c
 *
 *  Created on: Aug 19, 2016
 *      Author: APS3KOR
 */

#include "derivative.h" /* include peripheral declarations */
#include "FRCRSH.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name : front_crash                                                                   */
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

VOID front_crash(VOID)
{
	// Front airbag deployed (RED LED)	
	GPIOC_PCOR|= GPIO_PCOR_PTCO(1<<7);
}
