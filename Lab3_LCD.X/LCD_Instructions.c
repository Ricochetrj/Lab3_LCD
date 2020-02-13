/****************************************
    * File:    Lab_2_Timers_Int               *
     * Date:    7/02/2020                   *
     * Author:  Rodrigo Figueroa             *
     * Prof:     Pablo Mazariegos            *
     * Seccion:     20                       *
     * Clase:   Digital 2                    *
     * Compiler:    MPLAB XC8 v2.10          *
     * Arquitectura:    PIC16F887            *
     * Descripcion: Tercer Laboratorio donde Se leen valores analogicos a una
     *  LCD Utilizando la configuracion de 8bits de la LCD. Luego usando 
     *comunicacion serial tipo USART se le manda un valor al display que se incrementa
     * o decrementa en la terminal de la PC
     * 
     * 
     * Asignacion de Pins:
     * Puerto B = 
     *          RB5 = Entrada Analogica 1
     *          RB4 = Entrada Analogica 2
     * Puerto A = Entrada de datos (D7-D0) de la LCD
     * 
     * Puerto C = Entrada y salida Serial
     * 
     * Puerto D = 
     *          RD1 = Enable LCD
     *          RD0 = RS LCD             
     * 
     * 
     *
     * Link al Github: https://github.com/Ricochetrj/Lab3_LCD.git
     * 
     ****************************************/ 
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
uint8_t sent;
uint8_t sent2;
uint8_t sent3;
uint8_t sent4;
void Recieve(void){
    cascada:
    if(PIR1bits.RCIF== 1){
        goto cascada;
          
        
    } 
    
   if(PIR1bits.RCIF== 0){
       sent = 1;
   }
    
    if(PIR1bits.TXIF== 1){
         PORTDbits.RD3=0;
        
    }
    if(PIR1bits.TXIF==0){
     
    PORTDbits.RD3=1;
    if(ADCON0bits.GO==1){;
    TXREG= 5;}
    }
    
}
void main(void) {
    TRISA= 0;
    TRISD = 0;
    //TRISCbits.TRISC7 = 1;
    PORTA = 0;
    PORTD = 0;
    sent = 0;
    /////Com Serial
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH =1;
  
    BAUDCTLbits.BRG16 = 1;
    SPBRG = 25;
    SPBRGH = 0;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    TXSTAbits.TXEN = 1;
    PORTD = 0;
    
    ///
    ADCinit();
    lcd_init();
    lcd_clear();
    __delay_ms(250);
    
    while(1){
        //lcd_clear();

        lcd_cursor(1,1);
        lcd_palabra("Pot1");
        lcd_cursor(1,7);
        lcd_palabra("Pot2");
        lcd_cursor(1,13);
        lcd_palabra("+/-");
        
        ADCON0bits.CHS = 0b1011;
        lcd_cursor(2,2);
        ADCread();
        lcd_cursor(2,1);
        //itoa(buffer,voltaje,10);
        ADC2read();
        __delay_ms(10);
        ADCON0bits.CHS = 0b1101;
        lcd_cursor(2,8);
        ADCread();
        lcd_cursor(2,7);
        ADC2read();
        __delay_ms(10);
       
       
        
        lcd_cursor(2,13);
        
        
        //Recieve();
       
        ftoa2(sent, buffer,2);
        lcd_palabra(buffer);
        __delay_ms(50);
        __delay_ms(250);
        
    }
}