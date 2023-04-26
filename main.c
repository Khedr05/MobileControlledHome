/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : main.c                                  	   			 */
/* Date          : Apr 19, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "Application/application.h"


extern enu_app_states Current_State;
extern u8 input_username_string[20];
extern u8 input_psw_string[20];

int main(void){
	/* Initialization part */
	enu_psw_check_return psw_check_flag;
	u8 wrong_entry_counter=0;
	app_vInit();
	while(1){
		/* Main Program */
		switch(Current_State){
		case start_state:
			UART_vSendString((u8*)"Welcome to Mobile Controlled System\n\r");
			UART_vSendString((u8*)"-----------------------------------\n\n\r");
			Current_State = locked_user_input;
			break;
		case locked_user_input:
			UART_vSendString((u8*)"Enter username: ");
			app_ReceiveInput();
			Current_State = locked_psw_input;
			break;
		case locked_psw_input:
			UART_vSendString((u8*)"Enter password: ");
			app_ReceiveInput();
			Current_State = locked_checking_user_psw;
			break;
		case locked_checking_user_psw:
			psw_check_flag = psw_Check_Credentials(input_username_string, input_psw_string);
			switch(psw_check_flag){
			case wrong_data:
				UART_vSendString((u8*)"Wrong data!\n\r\n\r");
				if(0 == wrong_entry_counter){
					UART_vSendString((u8*)"2 more tries remaining!\n\r\n\r");
					wrong_entry_counter++;
				}
				else if(1 == wrong_entry_counter){
					UART_vSendString((u8*)"1 more try remaining!\n\r\n\r");
					wrong_entry_counter++;
				}
				else if(2 == wrong_entry_counter){
					UART_vSendString((u8*)"You entered wrong password 3 times\n\r");
					UART_vSendString((u8*)"System is locked for 10 seconds!\n\r");
					psw_theft_protection();
					wrong_entry_counter = 0;
				}
				else{ /* Do Nothing */ }
				Current_State = locked_user_input;
				break;
			case correct_data:
				wrong_entry_counter = 0;
				UART_vSendString((u8*)"Normal user activated!\n\r");
				Current_State = unlocked_normal_user;
				break;
			case master_data:
				wrong_entry_counter = 0;
				UART_vSendString((u8*)"Master user activated!\n\r");
				Current_State = unlocked_master_user;
				break;
			default: /* Do Nothing */ break;
			}
			break;
		case unlocked_master_user:
			master_main_interface();
			Current_State = start_state;
			break;
		case unlocked_normal_user:
			normalUserInterface();
			Current_State = start_state;
			break;
		default: /* Do Nothing */ break;
		}
	}
	return 0;
}
