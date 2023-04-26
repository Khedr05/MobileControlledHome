/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : Psw.c                                  	    		 */
/* Date          : Apr 24, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "psw.h"


extern u8 input_username_string[20];
extern u8 input_psw_string[20];
static u8 psw_Check_If_Master();
extern TMR_cfg_t TIMER2;
extern u8 timer2_flag;

u8 saved_user1[20] 	   = "Omar";
u8 saved_user1_psw[20] = "Yamany";
u8 saved_user2[20] 	   = "Sherif";
u8 saved_user2_psw[20] = "Ashraf";

/*
 * This function takes username and password as input and check if it's equal to the saved ones
 * returns master_data if the inputs are for master user
 * returns correct_data if the inputs are for saved username and password
 * returns wrong_data if the inputs are not identical for any saved username and password
 */
enu_psw_check_return psw_Check_Credentials(){
	u8 temp_return = 0;
	/* Check if username and password are for master */
	temp_return = psw_Check_If_Master();
	if(temp_return == 1){
		return master_data;
	}
	/* If not, check for saved users */
	if(strcmp((char*)saved_user1, (char*)input_username_string) == 0){
		if(strcmp((char*)saved_user1_psw, (char*)input_psw_string) == 0){
			return correct_data;
		}
	}
	else if(strcmp((char*)saved_user2, (char*)input_username_string) == 0){
		if(strcmp((char*)saved_user2_psw, (char*)input_psw_string) == 0){
			return correct_data;
		}
	}
	/* If not, return 0 as not found */
	return wrong_data;
}

/*
 * This function checks if username and password are for master user or not
 * returns 1 if the inputs are identical to master login credentials
 * returns 0 if the inputs are not identical to master login credentials
 */
static u8 psw_Check_If_Master(){
	u8 Master_username[20] = "MASTER";
	u8 Master_password[20] = "MASTER";
	/* If username and password equals to master user and password, return 1 */
	if( (strcmp((char*)input_username_string, (char*)Master_username) == 0) && (strcmp((char*)input_psw_string, (char*)Master_password) == 0) ){
		return 1;
	}
	/* If username and password are not for master user, return 0 */
	return 0;
}

/**
 * This function activate theft protection system
 * It enables an alarm siren for 10 seconds and display remaining time
 */
void psw_theft_protection(void){

	/* Enable timer 2 */
	TMR_vStartTimer(&TIMER2);
	timer2_flag = FLAG_OFF;
	/* While loop until flag is off */
	while(timer2_flag == FLAG_OFF){
		SIREN_vChangeSound(500);  // produce low sound
		_delay_ms(250);  // wait for 500ms
		SIREN_vChangeSound(1100); // produce high sound
		_delay_ms(250);  // wait for 500ms
		SIREN_vChangeSound(500);  // produce low sound
		_delay_ms(250);  // wait for 500ms
		SIREN_vChangeSound(1100); // produce high sound
		_delay_ms(250);
		SIREN_vStop();
		_delay_ms(1000);
	}
	TMR_vStop(&TIMER2);
}
