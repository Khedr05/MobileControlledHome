/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : EEPROM_program.c                                  	     */
/* Date          : Apr 7, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "EEPROM_interface.h"

void EEPROM_vinit(void){
	TWI_vInit();
}
u8 EEPROM_u8WriteByte(u8 Copy_u8Address, u8 Copy_u8Data, enu_EEPROM_Blocks Copy_enuBlock){
	TWI_vStart();
	if(TWI_u8GetStatus() != TW_START){
		return 0;
	}
	/* Send the device address, we need to get A8 A9 A10 address bits from
	 * memory location address and R/W=0 (write) */
	//TWI_vWriteData( ((EEPROM_Address | EEPROM_EN_CFG | Copy_enuBlock) & 0xFE) );
	TWI_vWriteData( 0xA2 );
	if(TWI_u8GetStatus() != TW_MT_SLA_W_ACK){
		return 1;
	}
	/* Send the required memory location address */
	TWI_vWriteData(Copy_u8Address);
	if(TWI_u8GetStatus() != TW_MT_DATA_ACK){
		return 2;
	}

	/* Write byte to eeprom */
	TWI_vWriteData(Copy_u8Data);
	if(TWI_u8GetStatus() != TW_MT_DATA_ACK){
		return 3;
	}
	TWI_vStop();
	return 4;
}

u8 EEPROM_u8ReadByte(u8 Copy_u8Address, u8 *Copy_u8Data, enu_EEPROM_Blocks Copy_enuBlock){
	TWI_vStart();
	if(TWI_u8GetStatus() != TW_START){
		return 0;
	}
	/* Send the device address, we need to get A8 A9 A10 address bits from
	 * memory location address and R/W=0 (write) */
	//TWI_vWriteData( (EEPROM_Address | EEPROM_EN_CFG | Copy_enuBlock) & 0xFE );
	TWI_vWriteData( 0xA2 );
	if(TWI_u8GetStatus() != TW_MT_SLA_W_ACK){
		return 1;
	}
	/* Send the required memory location address */
	TWI_vWriteData(Copy_u8Address);
	if(TWI_u8GetStatus() != TW_MT_DATA_ACK){
		return 2;
	}
	TWI_vStart();
	if(TWI_u8GetStatus() != TW_REP_START){
		return 3;
	}
	//TWI_vWriteData( EEPROM_Address | EEPROM_EN_CFG | Copy_enuBlock | 1 );
	TWI_vWriteData( 0xA3 );
	if(TWI_u8GetStatus() != TW_MT_SLA_R_ACK){
		return 4;
	}
	*Copy_u8Data = TWI_u8ReadWithNoAck();
	TWI_vStop();
	return 5;
}
