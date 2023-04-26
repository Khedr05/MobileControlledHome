/*
 * ECU_init.c
 *
 *  Created on: 26 Apr 2023
 *      Author: 20101
 */

#include "ECU_init.h"

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


void initEcu(void)
{
	LED_vInit(&roomOneLed);
	LED_vInit(&roomTwoLed);
	LED_vInit(&roomThreeLed);
	LED_vInit(&roomFourLed);
	LED_vInit(&roomFiveLed);
}
