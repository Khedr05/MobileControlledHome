/*
 * user_hnadling.h
 *
 *  Created on: 4 May 2023
 *      Author: 20101
 */

#ifndef USER_MANAGMENT_USER_HNADLING_H_
#define USER_MANAGMENT_USER_HNADLING_H_

#include <string.h>
#include <util/delay.h>
#include "../../SERVICES/STD_TYPES/STD_TYPES.h"
#include "user_handling_cfg.h"
#include "../../HAL/Bluetooth_Module/bluetooth.h"
#include "../../HAL/EEPROM/EEPROM_interface.h"

typedef struct
{
	enu_EEPROM_Blocks block;
	u16 userNameAdd;
	u16 userPassAdd;
	u8 userName[USER_NAME_MAX_SIZE];
	u8 userPass[USER_PASS_MAX_SIZE];

}ST_userData_t;


u8 addNewUser(ST_userData_t *_user);
u8 editUser(ST_userData_t *_user);
void eraseUser(ST_userData_t *_user);
u8 isUserExist(u8 *userName);
void removeUser(ST_userData_t *_user);
u8 isFreeSlot(ST_userData_t *_user);
void databaseLoad();
void databaseSave();
void viewUsers();
void UsersList();





#endif /* USER_MANAGMENT_USER_HNADLING_H_ */
