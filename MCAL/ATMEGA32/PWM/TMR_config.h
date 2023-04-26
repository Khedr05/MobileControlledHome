/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : TMR_config.h                                  	     */
/* Date          : Feb 26, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef MCAL_ATMEGA32_TMR_TMR_CONFIG_H_
#define MCAL_ATMEGA32_TMR_TMR_CONFIG_H_

/****************** MACROS FOR CONDITIONS ******************/
// 16 bit modes

#define NORMAL_16_MODE		0
#define PWM_8_MODE			1
#define PWM_9_MODE			2
#define PWM_10_MODE			3
#define CTC_OCR1A_MODE		4
#define FAST_PWM_8_MODE		5
#define FAST_PWM_9_MODE		6
#define FAST_PWM_10_MODE	7
#define PWM_PF_ICR_MODE		8
#define PWM_PF_OCR1A_MODE	9
#define PWM_ICR1_MODE		10
#define PWM_OCR1A_MODE		11
#define CTC_ICR1_MODE		12
#define FAST_PWM_ICR1_MODE	14
#define FAST_PWM_OCR1A_MODE	15

#define NONE				0
#define INVERTING_MODE		1
#define NON_INVERTING_MODE	2

#define TMR0_CHNL		0
#define TMR1_CHNL		1
#define TMR2_CHNL		2

#define PRE_NO_CLK		0
#define PRE_0			1
#define PRE_8			2
#define PRE_64			3
#define PRE_256			4
#define PRE_1024		5
#define PRE_EXT_FALLING	6
#define PRE_EXT_RISING	7
#define PRE_32			8
#define PRE_128			9

#define CTC_IE_ENABLE	0
#define TOF_IE_ENABLE	1
#define TIE_DISABLE		2

// 8 bit modes
#define NORMAL_MODE		0
#define PWM_MODE		1
#define	CTC_MODE		2
#define FAST_PWM_MODE	3



#endif /* MCAL_ATMEGA32_TMR_TMR_CONFIG_H_ */
