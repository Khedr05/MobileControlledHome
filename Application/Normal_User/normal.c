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
u8 temparrcommand[ARR_MAX_SIZE];
u8 ledOnStr[] = "led on";
u8 ledOffStr[] = "led off";
u8 doorOpenStr[] = "door open";
u8 doorCloseStr[] = "door close";
u8 logoutStr[] = "logout";
EN_COMMAND_MODES userCommand = IDLE_COMMAND;


EN_COMMAND_MODES setCommand(void)
{ 	//u8 i = 0;
	EN_COMMAND_MODES ret = WRONG_COMMAND;

	if(ret == WRONG_COMMAND)
	{
		for(int i =0;temparrcommand[i+1]!='\0';i++)
		{
			if(temparrcommand[i] == ledOnStr[i])
			{
				ret = LED_ON;
			}
			else
			{
				ret = WRONG_COMMAND;
				break;
			}
		}
	}
	if(ret == WRONG_COMMAND)
	{
		for(int i =0;temparrcommand[i+1]!='\0';i++)
		{
			if(temparrcommand[i] == ledOffStr[i])
			{
				ret = LED_OFF;
			}
			else
			{
				ret = WRONG_COMMAND;
				break;
			}
		}
	}
	if(ret == WRONG_COMMAND)
	{
		for(int i =0;temparrcommand[i+1]!='\0';i++)
		{
			if(temparrcommand[i] == doorOpenStr[i])
			{
				ret = DOOR_OPEN;
			}
			else
			{
				ret = WRONG_COMMAND;
				break;
			}
		}
	}
	if(ret == WRONG_COMMAND)
	{
		for(int i =0;temparrcommand[i+1]!='\0';i++)
		{
			if(temparrcommand[i] == doorCloseStr[i])
			{
				ret = DOOR_CLOSE;
			}
			else
			{
				ret = WRONG_COMMAND;
				break;
			}
		}
	}
	if(ret == WRONG_COMMAND)
	{
		for(int i =0;temparrcommand[i+1]!='\0';i++)
		{
			if(temparrcommand[i] == logoutStr[i])
			{
				ret = LOGOUT;
			}
			else
			{
				ret = WRONG_COMMAND;
				break;
			}
		}
	}

	return ret;
}

void getCommand(void)
{
	u8 tempChar,arrIndex = ZERO_INDEX;
	while(tempChar != '\r'){
		tempChar = UART_u8ReceiveData();
		UART_vSendData(tempChar);
			if(ARR_MAX_SIZE != arrIndex+1){
				arrcommand[arrIndex] = tempChar;
				arrIndex++;
			}
			arrcommand[arrIndex] = '\0';
	}
	strcpy((char *)temparrcommand,(char *)arrcommand);
	arrIndex = ZERO_INDEX;
	tempChar = ZERO_INDEX;
	UART_vSendString((u8*)"\r\n");
	userCommand = setCommand();
}



u8 normalUserInterface(void)
{
	UART_vSendString((u8 *)"WelCome In User Mode \r");
	while(1)
	{
		UART_vSendString((u8 *)"1 - led on \r");
		UART_vSendString((u8 *)"2 - led off \r");
		UART_vSendString((u8 *)"3 - door open \r");
		UART_vSendString((u8 *)"4 - door close \r");
		UART_vSendString((u8 *)"5 - logout \r");
		getCommand();
		switch(userCommand)
		{
		case IDLE_COMMAND:
		{
			/*nothing*/
			break;
		}
		case LED_ON:
		{
			UART_vSendString((u8 *)"Turning Led On... \r");
			LED_vTurnOn(&roomOneLed);
			LED_vTurnOn(&roomTwoLed);
			LED_vTurnOn(&roomThreeLed);
			LED_vTurnOn(&roomFourLed);
			LED_vTurnOn(&roomFiveLed);
			UART_vSendString((u8 *)"All Led Turned On Successfully\r");
			userCommand = IDLE_COMMAND;
			break;
		}
		case LED_OFF:
		{
			UART_vSendString((u8 *)"Turning Led Off... \r");
			LED_vTurnOff(&roomOneLed);
			LED_vTurnOff(&roomTwoLed);
			LED_vTurnOff(&roomThreeLed);
			LED_vTurnOff(&roomFourLed);
			LED_vTurnOff(&roomFiveLed);
			UART_vSendString((u8 *)"All Led Turned Off Successfully\r");
			userCommand = IDLE_COMMAND;
			break;
		}
		case DOOR_OPEN:
		{
			UART_vSendString((u8 *)"Opening Door Lock... \r");
			/*Call Your Function Here To Open Door*/
			UART_vSendString((u8 *)"Door Lock Opened Successfully... \r");
			userCommand = IDLE_COMMAND;
			break;
		}
		case DOOR_CLOSE:
		{
			UART_vSendString((u8 *)"Close Door Lock... \r");
			/*Call Your Function Here To Close Door*/
			UART_vSendString((u8 *)"Door Lock Closed Successfully... \r");
			userCommand = IDLE_COMMAND;
			break;
		}
		case LOGOUT:
		{
			UART_vSendString((u8 *)"Logging Out...\r");
			userCommand = IDLE_COMMAND;
			return 0;
			break;
		}
		case WRONG_COMMAND:
		{
			UART_vSendString((u8 *)"You Enter Invalid Command Please Try Again \r");
			userCommand = IDLE_COMMAND;
		}
		}

	}
}
