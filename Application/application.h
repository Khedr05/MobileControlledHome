/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : application.h                                  	     */
/* Date          : Apr 19, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

/* Section : Includes */
#include "../HAL/LED/led_interface.h"
#include "../HAL/SERVO/servo_interface.h"
#include "../HAL/Bluetooth_Module/bluetooth.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/ATMEGA32/TMR/TMR_interface.h"
#include "../HAL/SIREN/siren.h"
#include "Password_Check/Psw.h"
#include "String_Functions/string_functions.h"
#include "Normal_User/normal.h"
#include "Master_User/master.h"
#include <util/delay.h>

/* Section : Macro Declarations */
#define array_max_size		20
#define MAX_WRONG_ENTRIES	3
#define F_CPU				8000000UL

/* Section : Hardware Configuration */

/* Section : Data Type Declarations */
typedef enum{
	start_state,
	locked_user_input,
	locked_psw_input,
	locked_checking_user_psw,
	unlocked_master_user,
	unlocked_normal_user
}enu_app_states;

/* Section : Function Declarations */
void app_vInit(void);

void app_ReceiveInput(void);

u8 app_password_check();


#endif /* APPLICATION_APPLICATION_H_ */
