//#include <pic16f877.h>
#include <xc.h>
#include "LCDFunctions.h"
/*Tomado de https://www.exploreembedded.com/wiki/Interfacing_LCD_with_PIC16F877A_8-bit_mode
 Credito al autor original: Explore embedded wiki*
 * 7/2/20/
/* Configure the data bus and Control bus as per the hardware connection 
   Dtatus bus is connected to PB0:PB7 and control bus PD0:PD2*/
#define LcdDataBus      PORTB
#define LcdControlBus   PORTD

#define LcdDataBusDirnReg   TRISB
#define LcdCtrlBusDirnReg   TRISD

#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     2


/* local function to generate delay */
void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}


/* Function to send the command to LCD */
void Lcd_CmdWrite(char cmd)
{
    LcdDataBus = cmd;               //Send the Command nibble
    LcdControlBus &= ~(1<<LCD_RS);  // Send LOW pulse on RS pin for selecting Command register
    LcdControlBus &= ~(1<<LCD_RW);  // Send LOW pulse on RW pin for Write operation
    LcdControlBus |= (1<<LCD_EN);   // Generate a High-to-low pulse on EN pin
    delay(100);
    LcdControlBus &= ~(1<<LCD_EN); 

    delay(10000);
}

void StartLCD(void){
    LcdDataBusDirnReg = 0x00;  // Configure all the LCD pins as output
    LcdCtrlBusDirnReg = 0x00;  // Configure the Ctrl pins as output


    Lcd_CmdWrite(0x38);        // enable 5x7 mode for chars 
    Lcd_CmdWrite(0x0E);        // Display OFF, Cursor ON
    Lcd_CmdWrite(0x01);        // Clear Display
    Lcd_CmdWrite(0x80);        // Move the cursor to beginning of first line
}



/* Function to send the Data to LCD */
void Lcd_DataWrite(char dat)
{
    LcdDataBus = dat;               //Send the data on DataBus nibble
    LcdControlBus |= (1<<LCD_RS);   // Send HIGH pulse on RS pin for selecting data register
    LcdControlBus &= ~(1<<LCD_RW);  // Send LOW pulse on RW pin for Write operation
    LcdControlBus |= (1<<LCD_EN);   // Generate a High-to-low pulse on EN pin
    delay(100);
    LcdControlBus &= ~(1<<LCD_EN);

    delay(10000);
}


