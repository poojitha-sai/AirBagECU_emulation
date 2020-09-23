/*
 * side_crash.c
 *
 *  Created on: Aug 19, 2016
 *      Author: APS3KOR
 */

#include "derivative.h" /* include peripheral declarations */
#include "SDCRSH.h"

/*************************************************************************************************/
/*                                                                                               */
/* Function Name :  side_crash                                                     	 	         */
/*                                                                                               */
/* Input(s) : None                                                                               */
/* Output : None                                                                                 */
/* Functionality : Detection of side crash 													     */
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

VOID side_crash(VOID)
{
	// To inflate side airbag (ORANGE LED)	
	GPIOC_PCOR|= GPIO_PCOR_PTCO(1<<8);
}
