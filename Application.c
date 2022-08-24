/*
 * Application.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nourhan Ehab
 */
#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h> /* To use SREG REG. */

int main ()
{
	/* Variable to store the distance in it */
	uint16 distance = 0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	/* Initialize the LCD */
	LCD_init ();
	/* Initialize the Ultrasoinc */
	Ultrasonic_init ();
	while (1)
	{
		distance = Ultrasonic_readDistance ();
		LCD_displayStringRowColumn(0 , 0 , "Distance in cm =");
		LCD_moveCursor(1 , 7);
		if(distance >= 100)
		{
			LCD_intgerToString (distance);
		}
		else
		{
			LCD_intgerToString (distance);
			LCD_displayCharacter(' ');
		}

	}
}
