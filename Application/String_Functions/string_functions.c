/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : string_functions.c                                  	     */
/* Date          : Apr 25, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "string_functions.h"

/*
 * Function to save a string with known length into another variable
 */
void app_copy_string(u8* Copy_u8InputString, u8* Copy_u8OutputString, u8 Copy_u8Length){
	app_clear_string(Copy_u8OutputString, array_max_size);
	for(int i=0;i<Copy_u8Length;i++){
		Copy_u8OutputString[i] = Copy_u8InputString[i];
	}
}

/**
 * Function to clear an array to null
 */
void app_clear_string(u8* Copy_u8InputString, u8 Copy_u8Length){
	for(int i=0;i<Copy_u8Length;i++){
		Copy_u8InputString[i] = NULL;
	}
}
