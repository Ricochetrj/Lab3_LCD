/*
 * File:   LCD_Instructions.c
 * Author: rodri
 *
 * Created on 10 de febrero de 2020, 07:52 PM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include "LCD_Instructions.h"

void main(void) {
    TRISA= 0;
    TRISD = 0;
    PORTA = 0;
    PORTD = 0;
    ADCinit();
    lcd_init();
    lcd_clear();
    __delay_ms(250);
    
    while(1){
        lcd_clear();
        //Lcd_Shift_Right();
        lcd_cursor(1,1);
        lcd_palabra("V1");
        lcd_cursor(1,7);
        lcd_palabra("V2");
        lcd_cursor(1,13);
        lcd_palabra("V3");
        
        ADCON0bits.CHS = 0b1011;
        lcd_cursor(2,1);
        ADCread();
        __delay_ms(10);
        ADCON0bits.CHS = 0b1101;
        lcd_cursor(2,8);
        ADCread();
        __delay_ms(250);
        
    }
}
