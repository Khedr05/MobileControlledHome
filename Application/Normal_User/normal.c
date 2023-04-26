/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : Cmds.c                                  	     */
/* Date          : Apr 24, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/


#include "normal.h"


extern LED_cfg roomOneLed,roomTwoLed,roomThreeLed,roomFourLed,roomFiveLed;

u8 arrcommand[ARR_MAX_SIZE];
u8 ledOnStr[]="led on";
u8 ledOffStr[]="led off";
u8 dooropenStr[]="door open";
u8 doorCloseStr[]="door close";
u8 logoutStr[]="log out";

void getCommand(void)
{
	u8 tempChar,arrIndex = ZERO_INDEX;
	while(tempChar != '\r' || tempChar != '\n'){
		tempChar = UART_u8ReceiveData();
		UART_vSendData(tempChar);
		if(tempChar != '\r'|| tempChar != '\n'){
			if(ARR_MAX_SIZE != arrIndex){
				arrcommand[arrIndex] = tempChar;
				arrIndex++;
			}
		}
	}
	arrIndex = ZERO_INDEX;
	tempChar = ZERO_INDEX;
	UART_vSendString((u8*)"\r\n");
}



void normalUserInterface(void)
{

	while(1)
	{
		getCommand();
		if(strcmp((char *)arrcommand,(char *)ledOnStr) == TWO_EQUAL_ARR)
		{
			LED_vTurnOn(&roomOneLed);
			LED_vTurnOn(&roomTwoLed);
			LED_vTurnOn(&roomThreeLed);
			LED_vTurnOn(&roomFourLed);
			LED_vTurnOn(&roomFiveLed);
		}
		else if(strcmp((char *)arrcommand,(char *)ledOffStr) == TWO_EQUAL_ARR)
		{
			LED_vTurnOff(&roomOneLed);
			LED_vTurnOff(&roomTwoLed);
			LED_vTurnOff(&roomThreeLed);
			LED_vTurnOff(&roomFourLed);
			LED_vTurnOff(&roomFiveLed);
		}
		else if(strcmp((char *)arrcommand,(char *)dooropenStr) == TWO_EQUAL_ARR)
		{
			/*call open door func*/
		}
		else if(strcmp((char *)arrcommand,(char *)doorCloseStr) == TWO_EQUAL_ARR)
		{
			/*call close door func*/
		}
		else if(strcmp((char *)arrcommand,(char *)logoutStr) == TWO_EQUAL_ARR)
		{
			break;
		}
	}
}
