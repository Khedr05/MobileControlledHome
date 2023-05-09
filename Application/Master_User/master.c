/*
 * master.c
 *
 *  Created on: 5 May 2023
 *      Author: 20101
 */


#include "master.h"



extern ST_userData_t USER_ONE,USER_TWO,USER_THREE,USER_FOUR,USER_FIVE;

void master_user_interface()
{
	Bluetooth_vSendString((u8 *)"\n\r===== Please Wait While Processing Your Data =====");
	databaseLoad();
	u8 tempNumberOfRegistars;
	EEPROM_u8ReadByte(0xF8,&tempNumberOfRegistars,BLOCK1);
	if(tempNumberOfRegistars == 0xFF)
	{
		EEPROM_u8WriteByte(0xF8,0,BLOCK1);
	}
	u8 operation = '0';
	Bluetooth_vSendString((u8 *)"\n\r===== User Management System =====");
	Bluetooth_vSendString((u8 *)"\n\r===== Choose Operation =====");
	Bluetooth_vSendString((u8 *)"\n\r1 - Add User ");
	Bluetooth_vSendString((u8 *)"\n\r2 - Edit User ");
	Bluetooth_vSendString((u8 *)"\n\r3 - Remove User ");
	Bluetooth_vSendString((u8 *)"\n\r4 - Exit ");
	Bluetooth_vSendString((u8 *)"\n\rEnter Choice : ");
	while(1)
	{
		operation = Bluetooth_u8ReceiveData();
		Bluetooth_vClearBuffer();
		Bluetooth_vSendData(operation);
		switch(operation)
		{
		case '1' :
		{
			u8 user;
			UsersList();
			Bluetooth_vSendString((u8 *)"\n\rChoose Free User Slot : ");
			user = Bluetooth_u8ReceiveData();
			Bluetooth_vSendData(user);
			Bluetooth_vClearBuffer();
			switch(user)
			{
			case '0' : addNewUser(&USER_ONE); break;
			case '1' : addNewUser(&USER_TWO); break;
			case '2' : addNewUser(&USER_THREE); break;
			case '3' : addNewUser(&USER_FOUR); break;
			case '4' : addNewUser(&USER_FIVE); break;
/*			case '5' : addNewUser(&USER_SIX); break;
			case '6' : addNewUser(&USER_SEVEN); break;
			case '7' : addNewUser(&USER_EGIHT); break;
			case '8' : addNewUser(&USER_NINE); break;
			case '9' : addNewUser(&USER_TEN); break;*/
			default: Bluetooth_vSendString((u8 *)"\n\rWrong Entry!\n\r ");
			}
			Bluetooth_vSendString((u8 *)"\n\r===== Choose Operation =====");
			Bluetooth_vSendString((u8 *)"\n\r1 - Add User ");
			Bluetooth_vSendString((u8 *)"\n\r2 - Edit User ");
			Bluetooth_vSendString((u8 *)"\n\r3 - Remove User ");
			Bluetooth_vSendString((u8 *)"\n\r4 - Exit ");
			Bluetooth_vSendString((u8 *)"\n\rEnter Choice : ");
			break;
		}
		case '2':
		{
			u8 user;
			UsersList();
			Bluetooth_vSendString((u8 *)"\n\rChoose User To Edit : ");
			user = Bluetooth_u8ReceiveData();
			Bluetooth_vSendData(user);
			Bluetooth_vClearBuffer();
			switch(user)
			{
			case '0' : editUser(&USER_ONE); break;
			case '1' : editUser(&USER_TWO); break;
			case '2' : editUser(&USER_THREE); break;
			case '3' : editUser(&USER_FOUR);break;
			case '4' : editUser(&USER_FIVE); break;
/*			case '5' : editUser(&USER_SIX); break;
			case '6' : editUser(&USER_SEVEN); break;
			case '7' : editUser(&USER_EGIHT); break;
			case '8' : editUser(&USER_NINE); break;
			case '9' : editUser(&USER_TEN); break;*/
			default: Bluetooth_vSendString((u8 *)"\n\rWrong Entry!\n\r ");
			}
			Bluetooth_vSendString((u8 *)"\n\r===== Choose Operation =====");
			Bluetooth_vSendString((u8 *)"\n\r1 - Add User ");
			Bluetooth_vSendString((u8 *)"\n\r2 - Edit User ");
			Bluetooth_vSendString((u8 *)"\n\r3 - Remove User ");
			Bluetooth_vSendString((u8 *)"\n\r4 - Exit ");
			Bluetooth_vSendString((u8 *)"\n\rEnter Choice : ");
			Bluetooth_vClearBuffer();
			break;
		}
		case '3':
		{
			u8 user;
			UsersList();
			Bluetooth_vSendString((u8 *)"\n\rChoose User To Remove : ");

			user = Bluetooth_u8ReceiveData();
			Bluetooth_vClearBuffer();
			Bluetooth_vSendData(user);
			switch(user)
			{
			case '0' : removeUser(&USER_ONE); break;
			case '1' : removeUser(&USER_TWO); break;
			case '2' : removeUser(&USER_THREE); break;
			case '3' : removeUser(&USER_FOUR);break;
			case '4' : removeUser(&USER_FIVE); break;
/*			case '5' : removeUser(&USER_SIX); break;
			case '6' : removeUser(&USER_SEVEN); break;
			case '7' : removeUser(&USER_EGIHT); break;
			case '8' : removeUser(&USER_NINE); break;
			case '9' : removeUser(&USER_TEN); break;*/
			default: Bluetooth_vSendString((u8 *)"\n\rWrong Entry!\n\r ");
			}
			Bluetooth_vSendString((u8 *)"\n\r===== Choose Operation =====");
			Bluetooth_vSendString((u8 *)"\n\r1 - Add User ");
			Bluetooth_vSendString((u8 *)"\n\r2 - Edit User ");
			Bluetooth_vSendString((u8 *)"\n\r3 - Remove User ");
			Bluetooth_vSendString((u8 *)"\n\r4 - Exit ");
			Bluetooth_vSendString((u8 *)"\n\rEnter Choice : ");
			Bluetooth_vClearBuffer();
			break;
		}
		case '4':
		{
			Bluetooth_vSendString((u8 *)"\n\r===== Please Wait While Saving Your Data =====\r\n\r\n");
			databaseSave();
			return;
		}
		default :
		{
			Bluetooth_vSendString((u8 *)"\n\rWrong Choice Try Again : ");
			Bluetooth_vSendString((u8 *)"\n\r===== Choose Operation =====");
			Bluetooth_vSendString((u8 *)"\n\r1 - Add User ");
			Bluetooth_vSendString((u8 *)"\n\r2 - Edit User ");
			Bluetooth_vSendString((u8 *)"\n\r3 - Remove User ");
			Bluetooth_vSendString((u8 *)"\n\r4 - Exit ");
			Bluetooth_vSendString((u8 *)"\n\rEnter Choice : ");
			Bluetooth_vClearBuffer();
			break;
		}
		}

	}
}
