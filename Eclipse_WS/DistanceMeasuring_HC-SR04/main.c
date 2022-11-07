/******************************************************************************
 *
 * Module: MiniProject_4
 *
 * File Name: main.c
 *
 * Description: Source file MiniProject_4
 *
 * Author: Mohamed Hassan
 *
 *******************************************************************************/

#include"lcd.h"
#include"ultrasonic_sensor.h"
#include<avr/io.h>
#include<util/delay.h>
int main(void)
{
	SREG|=(1<<7); /* Enable Global Interrupt I-Bit */

	/* Initialize both the LCD and Ultrasonic driver */
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=    cm ");



	while (1)
	{

		LCD_moveCursor(0, 10);
		LCD_intgerToString(Ultrasonic_readDistance());
		if(Ultrasonic_readDistance()<100)
		{
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayChar(' ');
		}

	}
}

