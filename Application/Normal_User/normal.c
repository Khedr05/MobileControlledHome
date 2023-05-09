/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : normal.c                                	     		 */
/* Date          : Apr 24, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/


#include "normal.h"


extern LED_cfg roomOneLed,roomTwoLed,roomThreeLed,roomFourLed,roomFiveLed;
extern SERVO_PWM_cfg_t SERVO1;

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
		tempChar = Bluetooth_u8ReceiveData();
		Bluetooth_vSendData(tempChar);
			if(ARR_MAX_SIZE != arrIndex+1){
				arrcommand[arrIndex] = tempChar;
				arrIndex++;
			}
			arrcommand[arrIndex] = '\0';
	}
	strcpy((char *)temparrcommand,(char *)arrcommand);
	arrIndex = ZERO_INDEX;
	tempChar = ZERO_INDEX;
	Bluetooth_vSendString((u8*)"\r\n");
	userCommand = setCommand();
}



u8 normalUserInterface(void)
{
	Bluetooth_vSendString((u8 *)"WelCome In User Mode \r\n\n");
	while(1)
	{
		Bluetooth_vSendString((u8 *)"1 - led on \r\n");
		Bluetooth_vSendString((u8 *)"2 - led off \r\n");
		Bluetooth_vSendString((u8 *)"3 - door open \r\n");
		Bluetooth_vSendString((u8 *)"4 - door close \r\n");
		Bluetooth_vSendString((u8 *)"5 - logout \r\n");
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
			Bluetooth_vSendString((u8 *)"Turning Led On... \r\n");
			LED_vTurnOn(&roomOneLed);
			LED_vTurnOn(&roomTwoLed);
			LED_vTurnOn(&roomThreeLed);
			LED_vTurnOn(&roomFourLed);
			LED_vTurnOn(&roomFiveLed);
			Bluetooth_vSendString((u8 *)"All Led Turned On Successfully\r\n");
			userCommand = IDLE_COMMAND;
			break;
		}
		case LED_OFF:
		{
			Bluetooth_vSendString((u8 *)"Turning Led Off... \r\n");
			LED_vTurnOff(&roomOneLed);
			LED_vTurnOff(&roomTwoLed);
			LED_vTurnOff(&roomThreeLed);
			LED_vTurnOff(&roomFourLed);
			LED_vTurnOff(&roomFiveLed);
			Bluetooth_vSendString((u8 *)"All Led Turned Off Successfully\r\n");
			userCommand = IDLE_COMMAND;
			break;
		}
		case DOOR_OPEN:
		{
			Bluetooth_vSendString((u8 *)"Opening Door Lock... \r\n");
			SERVO_vChangeDirection(&SERVO1, SERVO_180);
			Bluetooth_vSendString((u8 *)"Door Lock Opened Successfully... \r\n");
			userCommand = IDLE_COMMAND;
			break;
		}
		case DOOR_CLOSE:
		{
			Bluetooth_vSendString((u8 *)"Close Door Lock... \r\n");
			SERVO_vChangeDirection(&SERVO1, SERVO_0);
			Bluetooth_vSendString((u8 *)"Door Lock Closed Successfully... \r\n");
			userCommand = IDLE_COMMAND;
			break;
		}
		case LOGOUT:
		{
			Bluetooth_vSendString((u8 *)"Logging Out...\r\n");
			userCommand = IDLE_COMMAND;
			return 0;
			break;
		}
		case WRONG_COMMAND:
		{
			Bluetooth_vSendString((u8 *)"You Enter Invalid Command Please Try Again \r\n");
			userCommand = IDLE_COMMAND;
		}
		}

	}
}
