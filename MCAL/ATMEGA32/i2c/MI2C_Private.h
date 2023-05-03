/*
 * Author		: Bassel Yasser
 * Version      : V0.0.0
 * Date			: 3 - 2 - 2023
 * Description	: MI2C_Private.h  ---> Register file
 */



/****************************************************************************/
/*								Header Guard								*/
 /***************************************************************************/
#ifndef MCAL_I2C_V2_MI2C_PRIVATE_H_
#define MCAL_I2C_V2_MI2C_PRIVATE_H_

/*		 TWCR register		 */
#define TWIE		0
#define TWEN		2
#define TWWC		3
#define TWSTO		4
#define TWSTA		5
#define TWEA		6
#define TWINT		7

/*		 TWSR register		 */
#define TWPS0		0
#define TWPS1		1

/*		 TWAR register		 */
#define TWGCE		0   // broadcast

/*		 TWDR register		 */
#define R_W		0
/****************************************************************************/
/*								I2C Registers								*/
 /***************************************************************************/
#define TWBR		(*((volatile Uchar8_t*)(0x20)))
#define TWSR		(*((volatile Uchar8_t*)(0x21)))
#define TWAR		(*((volatile Uchar8_t*)(0x22)))
#define TWDR		(*((volatile Uchar8_t*)(0x23)))
#define TWCR		(*((volatile Uchar8_t*)(0x56)))




#endif /* MCAL_I2C_V2_MI2C_PRIVATE_H_ */
