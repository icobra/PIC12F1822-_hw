/*
 * Interfacing PIC12F1822 microcontroller with I2C LCD screen
 * C Code for MPLAB XC8 compiler
 * Internal oscillator used @ 8MHz
 * This is a free software with NO WARRANTY
 * http://simple-circuit.com/
*/ 
 
// set configuration words
#pragma config CONFIG1 = 0x3F84
#pragma config CONFIG2 = 0x1613
 
#include <xc.h>
#define _XTAL_FREQ 8000000
#include "I2C_LCD.c"       // include I2C LCD driver source file
 
char i = 0, text[4];
 
void main(void)
{
  OSCCON = 0x70;      // set internal oscillator to 8MHz
  I2C_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
 
  LCD_Begin(0x4E);    // Initialize LCD module with I2C address = 0x4E
 
  LCD_Goto(2, 1);     // Go to column 2 row 1
  LCD_Print("Hello, world!");
 
  while(1)
  {
    // store 'i' into 'text' ( '0' for ASCII format )
    text[0] =  i / 100      + '0';  // store hundreds
    text[1] = (i / 10) % 10 + '0';  // store tens
    text[2] =  i % 10       + '0';  // store ones
 
    LCD_Goto(7, 2);      // go to column 7, row 2
    LCD_Print(text);     // print 'text'
 
    i++;                 // increment i
    __delay_ms(500);     // wait 0.5 second
 
  }
 
}
// end of code.