/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : application.c                                  	     */
/* Date          : Apr 19, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "application.h"

enu_app_states Current_State;

u8 temp_char;
u8 char_counter=0;
u8 input_temp_string[array_max_size];
u8 input_username_string[array_max_size];
u8 input_psw_string[array_max_size];


LED_cfg RED_LED = {
		.PortName = PORTB,
		.PinNum	  = PIN1,
		.InitialStatus = InitiallyOff
};


UART_tcfgInitialize UART1 = {
		.GLOBAL_tcfgCharSize = CHAR_8_BITS,
		.GLOBAL_tcfgParityState = PARITY_DISABLED,
		.GLOBAL_tcfgStopBits = STOP_BITS_1,
		.GLOBAL_tcfgUartBaudRate1X = UART_BR1X_38400,
		.GLOBAL_tcfgUartClkMode = UART_ASYNCHRONOUS,
		.GLOBAL_tcfgUartCommMode = UART_1X_SPEED,
		.GLOBAL_tcfgUartInterrupt = UART_INTERRUPT_DISABLED
};

SERVO_PWM_cfg_t SERVO1 = {
		.ServoPWM.PWM_TimerChannel = TIMER1_FastICR,
		.ServoPWM.PWM_TimerPrescale  = PRE_64,
		.ServoPWM.PWM_ToggleMode  = PWM_OCmode,
		.ServoPWM.PWM_InvertOrNot   = PWM_NonInvertingMode,
		.ServoInitialDirection = SERVO_0,
		.ICR_Value = 2500,
		.OCR_0degree_Value = 125,
		.OCR_90degree_Value = 188,
		.OCR_180degree_Value = 250
};

LED_cfg roomOneLed = {
		.PortName = PORTA,
		.PinNum	  = PIN0,
		.InitialStatus = InitiallyOff
};
LED_cfg roomTwoLed = {
		.PortName = PORTA,
		.PinNum	  = PIN1,
		.InitialStatus = InitiallyOff
};
LED_cfg roomThreeLed = {
		.PortName = PORTA,
		.PinNum	  = PIN2,
		.InitialStatus = InitiallyOff
};
LED_cfg roomFourLed = {
		.PortName = PORTA,
		.PinNum	  = PIN3,
		.InitialStatus = InitiallyOff
};
LED_cfg roomFiveLed = {
		.PortName = PORTA,
		.PinNum	  = PIN4,
		.InitialStatus = InitiallyOff
};

TMR_cfg_t TIMER2 = {
		.TMR_TimerChannel = TIMER2_NORMAL,
		.TMR_ToggleMode = TMR_InterruptMode,
		.TMR_OCMode = OC_Disconnected,
		.TMR_Prescale = PRE_1024
}; // overflow time = 32.768ms

void app_vInit(void){
	/* Initialize hardware components */
	LED_vInit(&roomOneLed);
	LED_vInit(&roomTwoLed);
	LED_vInit(&roomThreeLed);
	LED_vInit(&roomFourLed);
	LED_vInit(&roomFiveLed);
	//SERVO_vInit(&SERVO1);
	UART_vInit(&UART1);
	UART_vEnable(&UART1);
	//EEPROM_vinit();
	Siren_vInit();
	TMR_vInit(&TIMER2);
	Current_State = start_state;

	/* Initialize variables */

}

void app_ReceiveInput(void){
	while(temp_char != '\r'){
		temp_char = UART_u8ReceiveData();
		UART_vSendData(temp_char);
		if(temp_char != '\r'){
			if(array_max_size != char_counter){
				input_temp_string[char_counter] = temp_char;
				char_counter++;
			}
		}
	}
	temp_char = 0;
	UART_vSendString((u8*)"\r\n");
	switch(Current_State){
	case locked_user_input:
		/* Save entered username and jump to locked_psw_input state */
		app_copy_string(input_temp_string, input_username_string, char_counter);
		app_clear_string(input_temp_string, char_counter);
		char_counter = 0;
		break;
	case locked_psw_input:
		/* Save entered password and call a function to check if username and password are correct
		 * if username and password correct, jump to unlocked_state
		 * if username and password incorrect, go back to locked_user_input state
		 */
		app_copy_string(input_temp_string, input_psw_string, char_counter);
		app_clear_string(input_temp_string, char_counter);
		char_counter = 0;
		break;
	case unlocked_normal_user:
		/* Save current command and send it to a function to execute command
		 * if function returns 0, that means to lock the system and go back to locked_user_input
		 */

		// Function to handle the command
		break;
	default: /* Do Nothing */ break;
	}

}
