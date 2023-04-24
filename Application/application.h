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
#include "../HAL/PBD/PBD_interface.h"
#include "../HAL/SERVO/servo_interface.h"
#include "../HAL/BUZZER/buzzer_interface.h"
#include "../MCAL/ATMEGA32/UART/UART_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"

/* Section : Macro Declarations */

/* Section : Hardware Configuration */

PB_cfg PB_OnOff = {
		.PortName = PORTB,
		.PinNum   = PIN0,
		.PBmode   = MODE_PULLUP
};

LED_cfg RED_LED = {
		.PortName = PORTB,
		.PinNum	  = PIN1,
		.InitialStatus = InitiallyOff
};

LED_cfg YELLOW_LED = {
		.PortName = PORTB,
		.PinNum	  = PIN2,
		.InitialStatus = InitiallyOff
};

LED_cfg GREEN_LED = {
		.PortName = PORTB,
		.PinNum	  = PIN3,
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

buzzer_cfg BUZZ1 = {
		.buzzer_port = PORTB,
		.buzzer_pin = PIN4
};

/* Section : Data Type Declarations */
typedef enum{
	off_state,
	initializing_state,
	ready_locked_state,
	on_unlocked_state
}enu_app_states;

/* Section : Function Declarations */
void app_vInit(void);

void app_vMain(void);

#endif /* APPLICATION_APPLICATION_H_ */
