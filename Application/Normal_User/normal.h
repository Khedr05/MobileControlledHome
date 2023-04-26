/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : Cmds.h                                  	     */
/* Date          : Apr 24, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef APPLICATION_NORMAL_USER_NORMAL_H_
#define APPLICATION_NORMAL_USER_NORMAL_H_

/* Section : Includes */
#include "../../MCAL/ATMEGA32/UART/UART_interface.h"
#include "../../HAL/LED/led_interface.h"
#include "ECU_init.h"
#include <string.h>
/* Section : Macro Declarations */

#define ARR_MAX_SIZE      20
#define TWO_EQUAL_ARR	  0
#define ZERO_INDEX		  0
/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */

void getCommand(void);
void normalUserInterface(void);


#endif /* APPLICATION_NORMAL_USER_NORMAL_H_ */
