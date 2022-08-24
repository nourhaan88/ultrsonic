/*
 * ultrasonic.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nourhan Ehab
 */

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>
/*configure ICU driver with prescaler 8 and detecting the rising edge*/

Icu_ConfigType configType = {F_CPU_8,RISING};

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/*global variable to detect the edge by ICU */
uint8 g_flag =0;
uint8 g_edgeCount = 0;
uint16 g_timeHigh=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Description : function to be called back by ICU when interrupt occurs
 * start the timer with the rising edge
 * stop the timer with the falling edge and store its value to calculate distance.
 */
void Ultrsonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount==1){
		/*
				* Clear the timer counter register to start measurements from the
				* first detected rising edge
				*/
				Icu_clearTimerValue();
				/* Detect falling edge */
				Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount==2){
		/* Store the High time value */
				g_timeHigh = Icu_getInputCaptureValue();
				/*to start count over in the next event*/
				Icu_clearTimerValue();
				/* Detect rising edge */
				Icu_setEdgeDetectionType(RISING);

				g_edgeCount=0;
				/*set the flag to one to detect end of measuring*/
				g_flag =1;
	}
}

/* Description : function to initialize the ultrasonic sensor
 * initialize ICU driver
 * setup the callBack function
 * setup trigger pin direction as output
 */
void Ultrasonic_init(void){
	Icu_init(&configType);
	Icu_setCallBack(Ultrsonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
}
/* Description : function to send a pulse to trigger pin*/
void Ultrasonic_trigger(void){
	GPIO_writePin(PORTB_ID,PIN5_ID,1);
	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,0);
}
/* Description : function to send trigger pulse then calculate the distance
 * by equation includes the time measured by timer1
 */
uint16 Ultrasonic_readDistance(void){
	uint16 measured_distance=0;
	Ultrasonic_trigger();
	while(g_flag==0);
	/*Wait till the flag is set*/
	g_flag=0;
	measured_distance = (0.01715* g_timeHigh +1);
	/*34300 cm/s(sound speed)
	 * divided by two (consider the wave traveled twice to return to sensor)
	 * then *10^-6 "as timer is incremented each 1 us"
	 * (34000*(timer value)*10^-6)/2=0.01715*timer value
	 * 1 added to calibrate the number shown on LCD as integer not float*/

		return measured_distance;
}



