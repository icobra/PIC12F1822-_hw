/*
 * Interfacing PIC12F1822 microcontroller with I2C LCD screen
 * C Code for MPLAB XC8 compiler
 * Internal oscillator used @ 8MHz
 * This is a free software with NO WARRANTY
 *
 * Created on 18 12 2019
 */

// button definitions
#define button1      RA5   // button B1 is connected to RA5 pin
#define button2      RA4   // button B2 is connected to RA4 pin

// set configuration words
#pragma config CONFIG1 = 0x3F84
#pragma config CONFIG2 = 0x1613


// set libs
#include <xc.h>
#define _XTAL_FREQ 8000000
#include <stdint.h>        // include stdint header
#include "I2C_LCD.c"       // include I2C LCD driver source file

// a small function for buttons debounce
__bit debounce ()
{
  uint8_t count = 0;
  for(uint8_t i = 0; i < 5; i++) {
    if(button1 == 0 || button2 == 0);
      count++;
    __delay_ms(10);
  }
  if(count > 2)  return 1;
  else           return 0;
}

int main(int argc, char** argv)
{
    OSCCON = 0x70;   // set internal oscillator to 8MHz
    ANSELA = 0;      // configure all PORTA pins as digital
 
    // enable RA4 and RA5 internal pull ups
    nWPUEN = 0;      // clear WPUEN bit (OPTION_REG.7)
    WPUA   = 0x30;   // WPUA register = 0b00110000
    
    I2C_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
    LCD_Begin(0x4E);    // initialize LCD module with I2C address = 0x4E
  
    LCD_Goto(1, 1);   // move cursor to column 1, row 1
    LCD_Print("BUTTON TEST");
    LCD_Goto(1, 2);   // move cursor to column 1, row 2
    LCD_Print("         Count:0");
    
    uint8_t count = 0;
    while(1){
        if(!button1)     // if button B1 is pressed
        if(debounce())   // call debounce function (make sure B1 is pressed)
        {
            LCD_Goto(1, 2);   // move cursor to column 1, row 2
            LCD_Print("B1 TEST");
            count++;
            LCD_Goto(16, 2); 
            LCD_PutC(count);
        }
        if(!button2)     // if button B1 is pressed
        if(debounce())   // call debounce function (make sure B1 is pressed)
        {
            LCD_Goto(1, 2);   // move cursor to column 1, row 2
            LCD_Print("B2 TEST");
            count--;
            LCD_Goto(16, 2); 
            LCD_PutC(count);
        }
        
        
    }
    return (EXIT_SUCCESS);
}

