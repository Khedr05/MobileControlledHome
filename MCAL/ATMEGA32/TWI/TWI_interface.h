/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : TWI_interface.h                                  	     */
/* Date          : Apr 7, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef MCAL_ATMEGA32_TWI_TWI_INTERFACE_H_
#define MCAL_ATMEGA32_TWI_TWI_INTERFACE_H_

/* Section : Includes */
#include "TWI_config.h"
#include "TWI_private.h"
#include "../DIO/DIO_interface.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */
void TWI_vInit();

void TWI_vStart();

void TWI_vStop();

void TWI_vWriteData(u8 Copy_u8Data);

u8 TWI_u8ReadWithAck();

u8 TWI_u8ReadWithNoAck();

u8 TWI_u8GetStatus();

#endif /* MCAL_ATMEGA32_TWI_TWI_INTERFACE_H_ */
