/*
 * LCD.c
 *
 *  Created on: Oct 6, 2022
 *      Author: HSNUS
 */
#include "lcd.h"
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "gpio.h"
void LCD_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LCD_READ_MODE);

	_delay_ms(20);
#if(LCD_MODE ==8)
	GPIO_setupPortDirection(LCD_DATA_PATH_REG,PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINE_EIGHT_BIT_MODE);

#elif(LCD_MODE==4)
	GPIO_setupPinDirection(LCD_DATA_PATH_REG,LCD_DB7_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PATH_REG,LCD_DB6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PATH_REG,LCD_DB5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PATH_REG,LCD_DB4_ID,PIN_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1 );
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2 );
	LCD_sendCommand(LCD_TWO_LINE_FOUR_BIT_MODE);
#endif

	LCD_sendCommand( LCD_CURSOR_OFF );
	LCD_sendCommand(LCD_CLEAR_DISPLAY );
}

void LCD_sendCommand(unsigned char command){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LCD_WRITE_MODE);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if(LCD_MODE ==8)
	GPIO_writePort(LCD_DATA_PATH_REG, command);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#elif(LCD_MODE==4)
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB4_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB5_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB6_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB7_ID,GET_BIT(command,7));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB4_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB5_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB6_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB7_ID,GET_BIT(command,3));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif

}

void LCD_displayChar(unsigned char data){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LCD_WRITE_MODE);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if(LCD_MODE ==8)
	GPIO_writePort(LCD_DATA_PATH_REG, data);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#elif(LCD_MODE==4)
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB4_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB5_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB6_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB7_ID,GET_BIT(data,7));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB4_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB5_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB6_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PATH_REG,LCD_DB7_ID,GET_BIT(data,3));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif

}

void LCD_displayString(unsigned char * LCD_data_ptr){
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LCD_WRITE_MODE);
	while(*LCD_data_ptr!='\0'){
		LCD_displayChar(*LCD_data_ptr);
		LCD_data_ptr++;
	}
}
void LCD_moveCursor(unsigned char row,unsigned char column){
	unsigned char LCD_address=0;
	switch(row){
	case 0 :
	{
		LCD_address=column;
		break;
	}
	case 1 :
	{
		LCD_address=0x40+column;
		break;
	}
	case 2:
	{
		LCD_address=0x10+column;
		break;
	}
	case 3:
	{
		LCD_address=0x50+column;
		break;
	}
	}
	LCD_sendCommand(LCD_CURSOR_POSITION|LCD_address);
}

void LCD_displayStringRowColumn(unsigned char row,unsigned char column,const char*Str){
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LCD_WRITE_MODE);
	LCD_moveCursor(row,column);
	LCD_displayString(Str);
}

void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
}
void LCD_intgerToString(int data)
{
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LCD_WRITE_MODE);
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff); /* Display the string */
}




