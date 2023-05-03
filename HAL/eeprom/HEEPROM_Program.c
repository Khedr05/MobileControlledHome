/*
 * HEEPROM_Program.c
 *
 *  Created on: Feb 3, 2023
 *      Author: hp
 */

#include "HEEPROM_Interface.h"

#define EEPROM_ADDRESS		0b01010000



void eeprom_init(void)
{
	i2c_init_master();
}


void eeprom_write_byte(Uint16_t address, Uchar8_t data)  // address is 10 bit
{
	Uchar8_t deviceAddress;
	//Uchar8_t dataAddress;
		
	deviceAddress = EEPROM_ADDRESS;	
	/*deviceAddress = EEPROM_ADDRESS | ((address >> 8) & 0x0003);*/
//	dataAddress = (address & 0b0011111111);

	/* Send start condition */
	i2c_start();
	/* Send slave address */
	i2c_send_slave_address_with_write_req(deviceAddress);     // i2c_write_byte(0x50 | (address >> 8) & 0x00000111 );
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  // 520 = 0b 01010 0  0  1   1 01110 11
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	  //                A2 P1 P2  B7      B0
	/* Send data location */
	i2c_write_byte((Uchar8_t) (address >> 8)); // or i2c_write_byte(dataAddress);
	i2c_write_byte((Uchar8_t) address);
	/* Send data */
	i2c_write_byte(data);
	/* Send Stop Condition */
	i2c_stop();
}


Uchar8_t eeprom_read_byte(Uint16_t address)
{
	Uchar8_t deviceAddress;
	//Uchar8_t dataAddress;
	Uchar8_t data;
	
	deviceAddress = EEPROM_ADDRESS;

// 	deviceAddress = EEPROM_ADDRESS | ((address >> 8) & 0x0003);

	/* Send start condition */
	i2c_start();
	/* Send slave address with write request*/
	i2c_send_slave_address_with_write_req(deviceAddress);
	/* Send Data location*/
		i2c_write_byte((Uchar8_t) (address >> 8));
		i2c_write_byte((Uchar8_t) address);
	/* Send Repeated Start Condition*/
	i2c_repeated_start();
	/* Send slave address with read request*/
	i2c_send_slave_address_with_read_req(deviceAddress);
	/*Read Received Byte*/
	data = i2c_read_byte();
	/* Send Stop Condition */
	i2c_stop();

	return data;
}


/*
void eeprom_write_string(Uint16_t Copy_u8Address, const Uchar8_t* str)
{
	Uchar8_t sendedAddress;
	Uchar8_t dataAddress, count = 0;

	while(str[count] != '\0')
	{
		count++;

	}
	sendedAddress = EEPROM_ADDRESS | ((Copy_u8Address >> 8) & 0x0003);
	dataAddress = (Uchar8_t)Copy_u8Address;
	i2c_start();

	i2c_send_slave_address_with_write_req(sendedAddress);
	i2c_write_byte((Uchar8_t) dataAddress);

    i2c_write_byte(count);

	    for(Uchar8_t i=0;i<count;i++)
	    {
		    i2c_write_byte(*str++);
	    }
	    i2c_write_byte('\0');

		i2c_stop();
}
*/



void eeprom_write_string(Uint16_t Copy_u8Address, const Uchar8_t* str)
{
		Uchar8_t len = 0;
			
			do 
			{
				eeprom_write_byte(Copy_u8Address++,str[len]);
				_delay_ms(200);
			}
			while(str[len++] != '\0');

			
}


void eeprom_read_string(Uint16_t Copy_u8Address, Uchar8_t* str)
{
			Uchar8_t len = 0;
			do
			{
				str[len] = eeprom_read_byte(Copy_u8Address++);
				_delay_ms(200);
			}
			while(str[len++] != '\0');
}

