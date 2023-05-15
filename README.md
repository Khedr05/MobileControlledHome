


# Mobile Controlled Home

[Mobile Controlled Home (AVR-ATmega32 Proteus Simulation)](https://www.youtube.com/watch?v=cHHTXfkM3TI&list=PLC3Wwc_IeCN8d-kV1xPaiXWGpabYQGxY_&index=7)

## Description:

#### The system allows controlling the home by mobile phone application through Bluetooth. 

#### Two subsystems are implemented; a Safety door that could be opened by the mobile application by entering the user name and password, and a light on/off that could also be controlled by the mobile phone. 

#### The system supports 5 users with different names and passwords, and uses an external EEPROM to read and save users' data.

#### In case of entering the username and password 3 times wrong, the system should give an alarm.

#### After powering on and initialization, the system enters the login state.

### Login interface:
![login_interface](https://github.com/sherifkhadr/MobileControlledHome/blob/main/Screenshots/Login_Interface.png?raw=true)
- The program asks the user to enter a username and password, and checks if it matches any user that is saved in the EEPROM.
- If the user entered a wrong username or password 3 times, the system is locked for 10 seconds, and a siren sound is generated from the buzzer using PWM, then the system is unlocked again after 10 seconds.
- If the user entered "**MASTER**" as a username and password, the system enters the "Master User" state.
- If the user entered a correct username and password, the system enters the "Normal User" state.

### Master User interface:
![master_interface](https://github.com/sherifkhadr/MobileControlledHome/blob/main/Screenshots/Master_Interface.png?raw=true)
 - Master interface manages the users in the system and updates the data on the EEPROM.
 - It has 3 options,
	 1. **Add User:** Adds a new user to the system
	 2. **Edit User:** Edits an existing user
	 3. **Remove User:** Removes an existing user from the system
	 4. **Exit:** Exits master user interface and returns to login interface

### Normal User interface:
![normal_interface](https://github.com/sherifkhadr/MobileControlledHome/blob/main/Screenshots/Normal_Interface.png?raw=true)
 - Normal interface controls the door and lights in the home.
 - The user can choose from 5 commands
	 1. **led on:** Turns the lights on
	 2. **led off:** Turns the lights off
	 3. **door open:** Opens the door
	 4. **door close:** Closes the door
	 5. **logout:** Exits normal user interface and returns to the login interface


## Project Design:
### The project is based on Layered Architecture and operates on a State Machine inside a Super Loop.

### Peripherals used:

 1. DIO: Used for controlling GPIO pins.
 2. Timer0: used in PWM mode to create a siren sound from the buzzer
 3. Timer1: Used in PWM mode to control the servo motor
 4. Timer2: Used in normal mode for generating delays in the system
 5. TWI (I2C): Used for interfacing with the EEPROM
 6. UART: Used for interfacing with the Bluetooth module

### Files:
- #### Application Layer:
	1. Master_User: Provides the master user interface
	2. Normal_User: Provides the master user interface
	3. Password_Check: Contains functions responsible for password-checking mechanisms
	4. String_Functions: Contains functions that help in dealing with strings
	5. User_Management: Contains functions that manage all the users in the system.
 - #### Hardware Abstraction Layer:
	 1. Bluetooth_Module: Driver for HC-05 Bluetooth module and is used for interfacing with mobile phone
	 2. EEPROM: Driver for ST24C08 EEPROM and is used to read and write data from and to the EEPROM
	 3. SERVO: Driver used to control the servo motor
	 4. SIREN: Driver used to make a siren sound from the buzzer
 - #### Hardware Abstraction Layer:
	 1. DIO: Driver used to control the GPIO pins
	 2. GIE: Driver used to control the global interrupt enable for the MCU
	 3. PWM: Driver used for controlling timers 0/1/2 in PWM mode
	 4. TMR: Driver used for controlling timers 0/1/2 in normal mode
	 5. TWI: Driver used for interfacing with the I2C peripheral
	 6. UART: Driver used for interfacing with the UART peripheral
- #### Service Layer:
	1. BIT_MATH: Contains bit-wise operations
	2. STD_TYPES: Contains all the data types used
## Project design:

![Project Design](https://github.com/sherifkhadr/MobileControlledHome/blob/main/design.png?raw=true)

  
