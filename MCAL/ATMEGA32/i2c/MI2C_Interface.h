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



/********************************************************************************************************/
/*											Header Guard												*/
/********************************************************************************************************/
#ifndef MCAL_I2C_V2_MI2C_INTERFACE_H_
#define MCAL_I2C_V2_MI2C_INTERFACE_H_

#include "../../Common/STD_Types.h"
#include "../../Common/Bit_Math.h"
#include "MI2C_Config.h"
#include "MI2C_Private.h"

/********************************************************************************************************/
/*												MACROS      											*/
/********************************************************************************************************/
#define START_ACK                0x08 // start has been sent
#define REP_START_ACK            0x10 // repeated start
#define SLAVE_ADD_AND_WR_ACK     0x18 // Master transmit ( slave address + Write request ) ACK
#define SLAVE_ADD_AND_RD_ACK     0x40 // Master transmit ( slave address + Read request ) ACK
#define WR_BYTE_ACK              0x28 // Master transmit data ACK
#define RD_BYTE_WITH_ACK         0x50 // Master received data with ACK
#define RD_BYTE_WITH_NACK        0x58 // Master received data with not ACK
#define SLAVE_ADD_RCVD_RD_REQ    0xA8 // means that slave address is received with write req
#define SLAVE_ADD_RCVD_WR_REQ    0x60 // means that slave address is received with read req
#define SLAVE_DATA_RECEIVED      0x80 // means that read byte req is received
#define SLAVE_BYTE_TRANSMITTED   0xC0 // means that write byte req is received

/********************************  Acknowledgment En/Dis   *******************************************/
#define MI2C_ACK_DISABLE		0
#define MI2C_ACK_ENABLE			1
/********************************  Enabling broadcasting   *******************************************/
#define MI2C_BROADCAST_DISABLE		0
#define MI2C_BROADCAST_ENABLE		1

/********************************************************************************************************/
/*							     	Function prototype				    					     		*/
/********************************************************************************************************/

/***********************************************************************************/
/*			01- i2c_init_master()									*/
/* ----------------------------------------------------------------------------------
 * @func   : I2C master Initialization
 * @in     : void
 * @out    : void
 ************************************************************************************/
void i2c_init_master(void);

/***********************************************************************************/
/*			02- i2c_init_slaver()									*/
/* ----------------------------------------------------------------------------------
 * @func   : I2C slave Initialization
 * @in     : void
 * @out    : void
 ************************************************************************************/
void i2c_init_slave (void);

/***********************************************************************************/
/*			03- i2c_start()									*/
/* ----------------------------------------------------------------------------------
 * @func   : Send start condition
 * @in     : void
 * @out    : void
 ************************************************************************************/
void i2c_start(void);

/***********************************************************************************/
/*			04- i2c_repeated_start()									*/
/* ----------------------------------------------------------------------------------
 * @func   : Send repeated start condition
 * @in     : void
 * @out    : void
 ************************************************************************************/
void i2c_repeated_start(void);

/***********************************************************************************/
/*			05- i2c_send_slave_address_with_write_req()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: send write request from master to slave
 * @in[1]     	: slave_address
 * 					- Slave address that you want to write on it
 * @out       	: void
 ************************************************************************************/
void i2c_send_slave_address_with_write_req(Uchar8_t slave_address);

/***********************************************************************************/
/*			06- i2c_send_slave_address_with_read_req()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: send read request from master to slave
 * @in[1]     	: slave_address
 * 					- Slave address that you want to read from it
 * @out       	: void
 ************************************************************************************/
void i2c_send_slave_address_with_read_req(Uchar8_t slave_address);

/***********************************************************************************/
/*			07- i2c_write_byte()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: Write data to slave
 * @in[1]     	: byte
 * 					- write data that u need to send
 * @out       	: void
 ************************************************************************************/
void i2c_write_byte(Uchar8_t byte);

/***********************************************************************************/
/*			08- i2c_read_byte()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: read data from slave
 * @in	     	: void
 * @out       	: returned data
 ************************************************************************************/
Uchar8_t i2c_read_byte(void);

/***********************************************************************************/
/*			09- i2c_stop()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: Send Stop condition
 * @in	     	: void
 * @out       	: void
 ************************************************************************************/
void i2c_stop(void);




/***********************************************************************************/
/*			10- i2c_slave_check_slave_address_received_with_write_req()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: Checking if master wants to write on slave
 * @in	     	: void
 * @out       	: void
 ************************************************************************************/
void i2c_slave_check_slave_address_received_with_write_req(void);

/***********************************************************************************/
/*			11- i2c_slave_check_slave_address_received_with_read_req()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: Checking if master wants to read from slave
 * @in	     	: void
 * @out       	: void
 ************************************************************************************/
void i2c_slave_check_slave_address_received_with_read_req(void);

/***********************************************************************************/
/*			12- i2c_slave_read_byte()									*/
/* ----------------------------------------------------------------------------------
 * @func   		: if slave recieved write request from master
 * @in	     	: void
 * @out       	: returned data
 ************************************************************************************/
Uchar8_t i2c_slave_read_byte(void);

/***********************************************************************************/
/*			13- i2c_slave_write_byte()									*/
/* ----------------------------------------------------------------------------------
 * @func   			: if slave recieved read request from master
 * @in[1]	     	: byte
 * 						- Data to be sent
 * @out       		: void
 ************************************************************************************/
void i2c_slave_write_byte(Uchar8_t byte);


#endif /* MCAL_I2C_V2_MI2C_INTERFACE_H_ */
