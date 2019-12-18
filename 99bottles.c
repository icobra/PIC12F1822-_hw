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

void main(void)
{
    OSCCON = 0x70;      // set internal oscillator to 8MHz
    I2C_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
 
    LCD_Begin(0x4E);    // Initialize LCD module with I2C address = 0x4E

    int bottles = 99; // Number of bottles at the beginning of the song
    char str_bottles[3];
    int number;
    while(1)
    {
        if(bottles > 1){
            LCD_Goto(1,1);  // Go to column 1 row 7
            number = bottles;
            str_bottles[1] = number % 10 + '0';
            number = number / 10;
            str_bottles[0] = number % 10 + '0';
            LCD_Print(str_bottles); 
            LCD_Goto(1,2);  // Go to column 2 row 1
            LCD_Print("Bottles of beer!");
            bottles--;
        }
        else{
            LCD_Goto(1,1);  // Go to column 1 row 7
            LCD_Print("01"); 
            LCD_Goto(1,2);  // Go to column 2 row 1
            LCD_Print("Bottle of beer!");
            LCD_Goto(1,1);  // Go to column 1 row 7
            LCD_Print("No more bottles of beer on the wall"); 
            LCD_Goto(1,2);  // Go to column 2 row 1
            LCD_Print("Go to the store and buy some more");        
            // Go to market and start again    
            bottles = 99;
            __delay_ms(1500);     // wait 1.5 second
            // Clear LCD
            LCD_Goto(1,1);
            LCD_Print("                ");
            LCD_Goto(1,2);
            LCD_Print("                ");
        }
    __delay_ms(500);     // wait 0.5 second
 
    }
 
}
// end of code.