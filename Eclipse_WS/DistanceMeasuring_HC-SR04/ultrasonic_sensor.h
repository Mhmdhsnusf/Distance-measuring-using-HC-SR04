 /******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic_sensor.h
 *
 * Description: Header file for the ultrasonic sensor
 *
 * Author: Mohamed Hassan
 *
 *******************************************************************************/

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_VCC_PORT_ID
#define ULTRASONIC_SENSOR_VCC_PIN_ID
#define ULTRASONIC_SENSOR_GND_PORT_ID
#define ULTRASONIC_SENSOR_GND_PIN_ID
#define ULTRASONIC_SENSOR_TRIGGER_PORT_ID PORTB_ID
#define ULTRASONIC_SENSOR_TRIGGER_PIN_ID PIN5_ID
#define ULTRASONIC_SENSOR_ECHO_PORT_ID PORTD_ID
#define ULTRASONIC_SENSOR_ECHO_PIN_ID PIN6_ID
#define ULTRASONIC_SENSOR_PULSE_DELAY 15
#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the ultrasonic sensor driver
 * 	1. Initialize the ICU driver as required.
 * 	2. Setup the ICU call back function.
 * 	3. Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);

/*
 * Description : Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void);

/*
 * Description :
 * 	1. Send the trigger pulse by using Ultrasonic_Trigger function.
 * 	2. Start the measurements by the ICU from this moment.
 * 	3. Return the measured distance in Centimeter.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description :
 * 	1. This is the call back function called by the ICU driver.
 * 	2. This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_SENSOR_H_ */



