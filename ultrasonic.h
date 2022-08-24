/*
 * ultrasonic.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nouhan Ehab
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* function to capture the time measured by ICU for the sensor wave to hit the object*/
void Ultrsonic_edgeProcessing(void);

/* function to initialize ultrasonic sensor*/

void Ultrasonic_init(void);

/* function to send a pulse to trigger pin*/

void Ultrasonic_trigger(void);

/*function to calculate the distance and return it */
uint16 Ultrasonic_readDistance(void);


#endif /* ULTRASONIC_H_ */
