/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : application.c                                  	     */
/* Date          : Apr 19, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "application.h"
#include <util/delay.h>
static enu_app_states Current_State;

u8 Entered_Username[50];
u8 Entered_Password[50];

void app_vInit(void){
	Current_State = off_state; // Initial state is off

	/* Initialize hardware components */
	LED_vInit(&RED_LED);
	LED_vInit(&YELLOW_LED);
	LED_vInit(&GREEN_LED);
	SERVO_vInit(&SERVO1);
	UART_vInit(&UART1);
	BUZZER_vInit(&BUZZ1);
	EEPROM_vinit();
}

void app_vMain(void){
	UART_vEnable(&UART1);


}

int main(void){
	/* Initialization part */
	app_vInit();
	app_vMain();
	u8 temp;
	u8 i, j;
/*	UART_vSendString((u8*)"Initialization Complete...\r\n");
	UART_vSendString((u8*)"Welcome To Mobile Controlled System!\r\n");
	UART_vSendString((u8*)"\r\nEnter Username: ");
	while('\r' != temp){
		temp = UART_u8ReceiveData();
		UART_vSendData(temp);
		Entered_Username[i++] = temp;
	}
	i=0;
	temp = 0;
	UART_vSendString((u8*)"\r\nEnter Password: ");
	while('\r' != temp){
		temp = UART_u8ReceiveData();
		UART_vSendData(temp);
		Entered_Password[i++] = temp;
	}
	UART_vSendString((u8*)"\r\nLogging...\r\n");*/
	temp = EEPROM_u8WriteByte(0, 'A', BLOCK1);
	UART_vSendData(temp+48);
	_delay_ms(1000);
	temp = EEPROM_u8WriteByte(9, 'B', BLOCK1);
	UART_vSendData(temp+48);
	_delay_ms(1000);
	temp = EEPROM_u8ReadByte(0, &i, BLOCK1);
	UART_vSendData(temp+48);
	_delay_ms(1000);
	temp = EEPROM_u8ReadByte(9, &j, BLOCK1);
	UART_vSendData(temp+48);
	_delay_ms(1000);
	UART_vSendData(i);
	_delay_ms(1000);
	UART_vSendData(j);
	while(1){
	/* Main Program */

	}
	return 0;
}
