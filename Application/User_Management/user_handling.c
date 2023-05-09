/*
 * user_handling.c
 *
 *  Created on: 4 May 2023
 *      Author: 20101
 */

#include "user_handling.h"

u8 userSlots = MAX_NUMBER_OF_USERS;
u8 NumberOfRegistars = 0;





ST_userData_t USER_ONE =
{
		.block = BLOCK0,
		.userNameAdd = 0x00,
		.userPassAdd = 0x18,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_TWO =
{
		.block = BLOCK0,
		.userNameAdd = 0x30,
		.userPassAdd = 0x48,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_THREE =
{
		.block = BLOCK0,
		.userNameAdd = 0x60,
		.userPassAdd = 0x78,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_FOUR =
{
		.block = BLOCK0,
		.userNameAdd = 0x90,
		.userPassAdd = 0xA8,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_FIVE =
{
		.block = BLOCK0,
		.userNameAdd = 0xC0,
		.userPassAdd = 0xD8,
		.userName = "FREE",
		.userPass = "FREE"
};
/*ST_userData_t USER_SIX =
{
		.block = BLOCK1,
		.userNameAdd = 0x108,
		.userPassAdd = 0x120,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_SEVEN =
{
		.block = BLOCK1,
		.userNameAdd = 0x138,
		.userPassAdd = 0x150,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_EGIHT =
{
		.block = BLOCK1,
		.userNameAdd = 0x168,
		.userPassAdd = 0x180,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_NINE =
{
		.block = BLOCK1,
		.userNameAdd = 0x198,
		.userPassAdd = 0xB0,
		.userName = "FREE",
		.userPass = "FREE"
};
ST_userData_t USER_TEN =
{
		.block = BLOCK1,
		.userNameAdd = 0xC8,
		.userPassAdd = 0xE0,
		.userName = "FREE",
		.userPass = "FREE"
};*/

ST_userData_t *dbAccounts[MAX_NUMBER_OF_USERS] =
{
		&USER_ONE,
		&USER_TWO,
		&USER_THREE,
		&USER_FOUR,
		&USER_FIVE
/*		&USER_SIX,
		&USER_SEVEN,
		&USER_EGIHT,
		&USER_NINE,
		&USER_TEN*/
};






u8 addNewUser(ST_userData_t *_user)
{
	Bluetooth_vClearBuffer();
	u8 ret = 0;
	EEPROM_u8ReadByte(0xF8,&NumberOfRegistars,BLOCK1);
	Bluetooth_vSendString((u8 *)"\n\r===== Adding New User =====");

	if(NumberOfRegistars == MAX_NUMBER_OF_USERS)
	{
		Bluetooth_vSendString((u8 *)"\n\r You Reach The Max Number Of Users");
	}
	else
	{
		u8 tempname[USER_NAME_MAX_SIZE];
		u8 temppass[USER_PASS_MAX_SIZE];
		Bluetooth_vSendString((u8 *)"\n\rEnter User Name : ");
		Bluetooth_vClearBuffer();
		u8 counterNmae = 0;
		while(tempname[counterNmae-1] != '\r')
		{
			tempname[counterNmae] = Bluetooth_u8ReceiveData();
			Bluetooth_vSendData(tempname[counterNmae]);
			counterNmae++;
			if(counterNmae == USER_NAME_MAX_SIZE - 1) break;
		}
		tempname[counterNmae-1] = '\0';
		if(isUserExist(tempname) && isFreeSlot(_user))
		{
			strcpy((char *)_user->userName,(char *)tempname);
			ret = 1;
		}
		if(ret == 1)
		{
			Bluetooth_vSendString((u8 *)"\n\rEnter User Password : ");
			u8 counterPass = 0;
			while(temppass[counterPass - 1] != '\r')
			{
				temppass[counterPass] = Bluetooth_u8ReceiveData();
				Bluetooth_vSendData(temppass[counterPass]);
				counterPass++;
				if(counterPass == USER_PASS_MAX_SIZE - 1) break;
			}
			temppass[counterPass-1] = '\0';
			strcpy((char *)_user->userPass,(char *)temppass);
			//EEPROM_vWriteString(_user->userNameAdd,_user->userName,_user->block);
			//_delay_ms(200);
			//EEPROM_vWriteString(_user->userPassAdd,_user->userPass,_user->block);
			Bluetooth_vSendString((u8 *)"\n\rUser Added Successfully ");
			NumberOfRegistars++;
			EEPROM_u8WriteByte(0xF8,NumberOfRegistars,BLOCK1);
		}
		else
		{
			Bluetooth_vSendString((u8 *)"\n\rUser Is Already Exist");
		}
	}
	return ret;
}
u8 editUser(ST_userData_t *_user)
{
	Bluetooth_vClearBuffer();
	u8 ret = 0;
	Bluetooth_vSendString((u8 *)"\n\r===== Editing User =====");

	u8 tempname[USER_NAME_MAX_SIZE];
	u8 temppass[USER_PASS_MAX_SIZE];
	Bluetooth_vSendString((u8 *)"\n\rEnter User Name : ");
	u8 counterNmae = 0;
	while(tempname[counterNmae-1] != '\r')
	{
		tempname[counterNmae] = Bluetooth_u8ReceiveData();
		Bluetooth_vSendData(tempname[counterNmae]);
		counterNmae++;
		if(counterNmae == USER_NAME_MAX_SIZE - 1) break;
	}
	tempname[counterNmae-1] = '\0';
	if(isUserExist(tempname))
	{
		u8 func_ret = isFreeSlot(_user);
		if(func_ret == 0)
		{
			eraseUser(_user);
			strcpy((char *)_user->userName,(char *)tempname);
			ret = 1;
		}
	}
	if(ret == 1)
	{
		Bluetooth_vSendString((u8 *)"\n\rEnter User Password : ");
		u8 counterPass = 0;
		while(temppass[counterPass - 1] != '\r')
		{
			temppass[counterPass] = Bluetooth_u8ReceiveData();
			Bluetooth_vSendData(temppass[counterPass]);
			counterPass++;
			if(counterPass == USER_PASS_MAX_SIZE - 1) break;
		}
		temppass[counterPass-1] = '\0';
		strcpy((char *)_user->userPass,(char *)temppass);
		//EEPROM_vWriteString(_user->userNameAdd,_user->userName,_user->block);
		//_delay_ms(200);
		//EEPROM_vWriteString(_user->userPassAdd,_user->userPass,_user->block);
		Bluetooth_vSendString((u8 *)"\n\rUser Edited Successfully ");
	}
	else
	{
		Bluetooth_vSendString((u8 *)"\n\rUser Is Not Exist");
	}
	return ret;
}

u8 isUserExist(u8 *userName)
{
	u8 ret = 1;
	u8 i = 0;
	while(i < userSlots)
	{
		if(!strcmp((char *)userName,(char *)dbAccounts[i]->userName))
		{
			ret = 0;
		}
		i++;
	}
	return ret;
}

void databaseLoad()
{
	u8 i = 0;
	while(i < userSlots)
	{
		EEPROM_vReadString(dbAccounts[i]->userNameAdd,dbAccounts[i]->userName,dbAccounts[i]->block);
		EEPROM_vReadString(dbAccounts[i]->userPassAdd,dbAccounts[i]->userPass,dbAccounts[i]->block);
		i++;
	}
}


void databaseSave()
{
	u8 i = 0;
	while(i < userSlots)
	{
		EEPROM_vWriteString(dbAccounts[i]->userNameAdd,dbAccounts[i]->userName,dbAccounts[i]->block);
		EEPROM_vWriteString(dbAccounts[i]->userPassAdd,dbAccounts[i]->userPass,dbAccounts[i]->block);
		i++;
	}
}


void viewUsers()
{
	u8 i = 0;
	while(i < userSlots)
	{
		Bluetooth_vSendString((u8 *)"\n\rUser Name Address : ");
		Bluetooth_vSendData(dbAccounts[i]->userNameAdd);

		Bluetooth_vSendString((u8 *)"\n\rUser Password Address : ");
		Bluetooth_vSendData(dbAccounts[i]->userPassAdd);


		Bluetooth_vSendString((u8 *)"\n\rUser Name : ");
		Bluetooth_vSendString(dbAccounts[i]->userName);


		Bluetooth_vSendString((u8 *)"\n\rUser Password : ");
		Bluetooth_vSendString(dbAccounts[i]->userPass);
		i++;
	}
}

void UsersList()
{
	u8 i = 0;
	while(i < userSlots)
	{
		Bluetooth_vSendString((u8 *)"\n\r");
		Bluetooth_vSendData((i) + '0');
		Bluetooth_vSendString((u8 *)" - User Name : ");
		Bluetooth_vSendString(dbAccounts[i]->userName);
		i++;
	}
}

void eraseUser(ST_userData_t *_user)
{
	u8 i = 0;
	u8 j = 0;
	while(i <= USER_NAME_MAX_SIZE)
	{
		strcpy((char *)_user->userName[i],"\0");
		i++;
	}
	while(j <= USER_PASS_MAX_SIZE)
	{
		strcpy((char *)_user->userPass[j],"\0");
		j++;
	}
	strcpy((char *)_user->userName,"FREE");
	strcpy((char *)_user->userPass,"\0");
}

void removeUser(ST_userData_t *_user)
{
	eraseUser(_user);
	EEPROM_u8ReadByte(0xF8,&NumberOfRegistars,BLOCK1);
	NumberOfRegistars--;
	EEPROM_u8WriteByte(0xF8,NumberOfRegistars,BLOCK1);
	Bluetooth_vSendString((u8 *)"\n\rUser Removed Successfully ");
}

u8 isFreeSlot(ST_userData_t *_user)
{

		u8 ret = 0;

		if(strcmp("FREE",(char *)_user->userName)==0)
		{
			ret = 1;
		}

		return ret;
}

