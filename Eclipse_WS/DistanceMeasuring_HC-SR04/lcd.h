
/*
 * LCD.h
 *
 *  Created on: Oct 6, 2022
 *      Author: HSNUS
 */
#ifndef LCD_FILES
#define LCD_FILES
#include"std_types.h"

#define LCD_RS_PORT_ID PORTB_ID
#define LCD_RS_PIN_ID PIN0_ID
#define LCD_ENABLE_PIN_ID PIN2_ID
#define LCD_ENABLE_PORT_ID PORTB_ID
#define LCD_RW_PORT_ID PORTB_ID
#define LCD_RW_PIN_ID PIN1_ID
#define LCD_DATA_PATH_REG PORTA_ID
#define LCD_TWO_LINE_EIGHT_BIT_MODE 0x38
#define LCD_ONE_LINE_EIGHT_BIT_MODE 0x30
#define LCD_ONE_LINE_FOUR_BIT_MODE 0x20
#define LCD_TWO_LINE_FOUR_BIT_MODE 0x28
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_CURSOR_OFF   0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_POSITION 0x80
#define LCD_READ_MODE 1
#define LCD_WRITE_MODE 0
#define LCD_MODE 8
#if(LCD_MODE==4)
#define LCD_DB4_ID PIN3_ID
#define LCD_DB5_ID PIN4_ID
#define LCD_DB6_ID PIN5_ID
#define LCD_DB7_ID PIN6_ID
#endif
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#endif
void LCD_init(void);
void LCD_sendCommand(unsigned char command);
void LCD_displayChar(unsigned char data);
void LCD_displayString(unsigned char * LCD_data_ptr);
void LCD_moveCursor(unsigned char row,unsigned char column);
void LCD_displayStringRowColumn(unsigned char row,unsigned char column,const char*Str);
void LCD_intgerToString(int data);



