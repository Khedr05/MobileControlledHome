/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : master.c                                		  	     */
/* Date          : Apr 25, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "master.h"

static void master_add_user();

static void master_remove_user();

static void master_list_users();

void master_main_interface(void){

	UART_vSendString((u8*)"\n\rWelcome to master user mode\n\r");
	UART_vSendString((u8*)"---------------------------\n\r");
	u8 user_choice;
	while(1){
		UART_vSendString((u8*)"\n\r1- Add new user\n\r");
		UART_vSendString((u8*)"2- Remove a user\n\r");
		UART_vSendString((u8*)"3- List all users\n\r");
		UART_vSendString((u8*)"0- Exit master user\n\r");
		UART_vSendString((u8*)"Your choice: ");
		user_choice = UART_u8ReceiveData();
		UART_vSendData(user_choice);
		switch(user_choice){
		case '0':
			UART_vSendString((u8*)"\n\rLogging out of master user\n\r");
			UART_vSendString((u8*)"App locked\n\r\n\r");
			return;
			break;
		case '1':
			master_add_user();
			break;
		case '2':
			master_remove_user();
			break;
		case '3':
			master_list_users();
			break;
		default:
			UART_vSendString((u8*)"\n\rWrong choice, please enter a correct option\n\r");
			break;
		}
	}
}

static void master_add_user(){
	UART_vSendString((u8*)"\n\rAdd new user\n\r");
}

static void master_remove_user(){
	UART_vSendString((u8*)"\n\rRemove a user\n\r");
}

static void master_list_users(){
	UART_vSendString((u8*)"\n\rList all users\n\r");
}
