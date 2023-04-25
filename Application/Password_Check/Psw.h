/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : Psw.h                                  	     */
/* Date          : Apr 24, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef APPLICATION_PASSWORD_CHECK_PSW_H_
#define APPLICATION_PASSWORD_CHECK_PSW_H_

/* Section : Includes */
#include "../../SERVICES/STD_TYPES/STD_TYPES.h"
#include "../../SERVICES/BIT_MATH/BIT_MATH.h"
#include <string.h>

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
	wrong_data,
	correct_data,
	master_data
}enu_psw_check_return;

/* Section : Function Declarations */

/*
 * This function takes username and password as input and check if it's equal to the saved ones
 * returns 2 if the inputs are for master user
 * returns 1 if the inputs are for saved username and password
 * returns 0 if the inputs are not identical for any saved username and password
 */
enu_psw_check_return psw_Check_Credentials();

#endif /* APPLICATION_PASSWORD_CHECK_PSW_H_ */
