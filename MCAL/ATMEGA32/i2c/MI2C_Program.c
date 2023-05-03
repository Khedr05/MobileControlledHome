/****************************************************************************
 * Author			: Bassel Yasser
 * Version      	: V0.0.0
 * Date				: 3 - 2 - 2023
 * Description		: MI2C_Interface.h  ---> Functions Prototype
 * Module Feature	:
 * 						01- i2c_init_master()
 * 						02- i2c_init_slave ()
 * 						03- i2c_start()
 * 						04- i2c_repeated_start()
 * 						05- i2c_send_slave_address_with_write_req()
 * 						06- i2c_send_slave_address_with_read_req()
 * 						07- i2c_write_byte()
 * 						08- i2c_read_byte()
 * 						09- i2c_stop()
 * 						10- i2c_slave_check_slave_address_received_with_write_req()
 * 						11- i2c_slave_check_slave_address_received_with_read_req()
 * 						12- i2c_slave_read_byte()
 * 						13- i2c_slave_write_byte()
 ****************************************************************************/

/*********************************************************************/
/*					Standard Types LIB								 */
/*********************************************************************/

/*********************************************************************/
/*					Peripheral Files 								*/
/*********************************************************************/
#include "MI2C_Interface.h"

#define MASTER_ADDRESS		0x50
#define SLAVE_ADDRESS		0x40
/****************************************************************************/
/*								Function Implementation			     		*/
/****************************************************************************/

void i2c_init_master(void)
{
//	TWBR = 0x02; // bit rate = 400.000 kbps, F_CPU = 8M   SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
//	TWSR &= ~((1<<TWPS1) | (1<<TWPS0));    //baud rate
//	TWAR = (1<<1);    // my address = 0x01
//	TWCR = (1<<TWEN);


//	/* Set prescallar to 1 to get 400 KHz  */
	CLEAR_BIT(TWSR, TWPS0);
	CLEAR_BIT(TWSR, TWPS1);
//	/* According to this formula {SCL_freq = (CPU_freq)/(16 + (2(TWBR)*4^TWPS)) }
//	 * According to prescallar is 1 ----> TWPS = 0 , so wet put 0x02 to TWBR to get 400 kHz
//	 **/
	TWBR = 0x02;
//	/* Set Master Address */
	TWAR = (MASTER_ADDRESS << 1);
//	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
}


void i2c_init_slave (void)
{
	/* Set Slave Address */
	TWAR = (SLAVE_ADDRESS << 1);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
}


void i2c_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/* Clear TWINT flag */
//	SET_BIT(TWCR, TWINT);
	/* Enable Start bit */
//	SET_BIT(TWCR, TWSTA);
	/* Enable I2C peripheral */
//	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != START_ACK );
	/* Disable Start bit */
//	CLEAR_BIT(TWCR, TWSTA);
}


void i2c_repeated_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/* Clear TWINT flag */
//	SET_BIT(TWCR, TWINT);
	/* Enable Start bit */
//	SET_BIT(TWCR, TWSTA);
	/* Enable I2C peripheral */
//	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != REP_START_ACK );
	/* Disable Start bit */
//	CLEAR_BIT(TWCR, TWSTA);
}


void i2c_send_slave_address_with_write_req(Uchar8_t slave_address)
{
	/* Putting slave address to TWDR register to be transmitted */
	TWDR = (slave_address<<1);
	/* Set bit 0 on TWDR register to make write operation */
	CLEAR_BIT(TWDR, R_W);

	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Clear TWINT flag */
//	SET_BIT(TWCR, TWINT);
	/* Enable I2C peripheral */
//	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK );
}


void i2c_send_slave_address_with_read_req(Uchar8_t slave_address)
{
	TWDR = (slave_address<<1);
	TWDR |= (1<<0);
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Putting slave address to TWDR register to be transmitted */
//	TWDR = (slave_address<<1);
	/* Set bit 0 on TWDR register to make read operation */
//	SET_BIT(TWDR, R_W);
	/* Clear TWINT flag */
//	SET_BIT(TWCR, TWINT);
/******************* If ACK enabled or not **************************************/
#if MI2C_ACK_STATUS == MI2C_ACK_DISABLE
	/* Disable ACK bit */
//	CLEAR_BIT(TWCR, TWEA);
#elif MI2C_ACK_STATUS == MI2C_ACK_ENABLE
	/* Enable ACK bit */
	SET_BIT(TWCR, TWEA);
#endif
/*********************************************************************************/
	/* Enable I2C peripheral */
//	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
//	while ( (TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK );
}


void i2c_write_byte(Uchar8_t byte)
{

	/* Putting data to TWDR register to be transmitted */
	TWDR = byte;

//	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Clear TWINT flag */
	SET_BIT(TWCR, TWINT);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != WR_BYTE_ACK );
}


Uchar8_t i2c_read_byte(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Clear TWINT flag */
//	SET_BIT(TWCR, TWINT);
	/* Enable I2C peripheral */
//	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
/******************* If ACK enabled or not **************************************/
#if MI2C_ACK_STATUS == MI2C_ACK_DISABLE
	/* Waiting if this condition becoming true */
//	while ( (TWSR & 0xF8) != RD_BYTE_WITH_NACK );
#elif MI2C_ACK_STATUS == MI2C_ACK_ENABLE
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != RD_BYTE_WITH_ACK );
#endif
/*********************************************************************************/
	return TWDR;
}


void i2c_stop(void)
{
//	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	/* Clear TWINT flag */
	SET_BIT(TWCR, TWINT);
	/* Enable Stop bit */
	SET_BIT(TWCR, TWSTO);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);

	while(TWCR&(1<<TWSTO));

//	CLEAR_BIT(TWCR, TWSTA);
}



void i2c_slave_check_slave_address_received_with_write_req(void)
{
	/* Clear TWINT flag */
	SET_BIT(TWCR, TWINT);
	/* Enable ACK bit */
	SET_BIT(TWCR, TWEA);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != SLAVE_ADD_RCVD_WR_REQ );
}


void i2c_slave_check_slave_address_received_with_read_req(void)
{
	/* Clear TWINT flag */
	SET_BIT(TWCR, TWINT);
	/* Enable ACK bit */
	SET_BIT(TWCR, TWEA);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != SLAVE_ADD_RCVD_RD_REQ );
}


Uchar8_t i2c_slave_read_byte(void)
{
	/* Clear TWINT flag */
	SET_BIT(TWCR, TWINT);
	/* Enable ACK bit */
	SET_BIT(TWCR, TWEA);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != SLAVE_DATA_RECEIVED );

	return TWDR;
}


void i2c_slave_write_byte(Uchar8_t byte)
{
	/* Putting data to TWDR register to be transmitted */
	TWDR = byte;
	/* Clear TWINT flag */
	SET_BIT(TWCR, TWINT);
	/* Enable ACK bit */
	SET_BIT(TWCR, TWEA);
	/* Enable I2C peripheral */
	SET_BIT(TWCR, TWEN);
	/* Waiting for TWINT flag to be set */
	while ( !(GET_BIT(TWCR,TWINT)) );
	/* Waiting if this condition becoming true */
	while ( (TWSR & 0xF8) != SLAVE_BYTE_TRANSMITTED );
}


