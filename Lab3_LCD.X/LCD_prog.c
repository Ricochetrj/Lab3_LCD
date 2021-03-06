   /****************************************
    * File:    Lab_2_Timers_Int               *
     * Date:    7/02/2020                   *
     * Author:  Rodrigo Figueroa             *
     * Prof:     Pablo Mazariegos            *
     * Seccion:     20                       *
     * Clase:   Digital 2                    *
     * Compiler:    MPLAB XC8 v2.10          *
     * Arquitectura:    PIC16F887            *
     * Descripcion: Segundo Laboratorio donde utilizando subrutinas de interrupciones se lee un valor analogico de un potenciometro y este se compara con un valor asignado a unos leds para determinar cuando el valor del potenciometro es mayor
     * 
     * 
     * Asignacion de Pins:
     * Puerto B = 
     *          RB1 = Boton de +
     *          RB0 = Boton de -
     * Puerto A = Salida del contador Binario
     * 
     * Puerto C = Salida del Display de 7 segmentos
     * 
     * Puerto D = D7 y D6 para multiplexar los displays
     * 
     * Puerto E = E2 entrada analogica del potenciometro
     *
     * Link al Github: https://github.com/Ricochetrj/Lab_2-Interrupciones.git
     * 
     ****************************************/

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
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

#include <xc.h>
#include <stdint.h>

#define LCD_E PORTDbits.RD6
#define LCD_RS PORTDbits.RD7
#define LCD_Data PORTB
#define LCD_RW PORTDbits.RD5

#define LCD_E_Dir TRISDbits.TRISD6
#define LCD_RS_Dir TRISDbits.TRISD7
#define LCD_RW_Dir TRISDbits.TRISD5
#define LCD_Data_IO TRISB

#define _XTAL_FREQ 4000000
void PulsoE(void);
void WriteCMLCD(unsigned char CM);
void WriteDataLCD( uint8_t y,uint8_t x,char *msg);
void initLCD(void);
void LCD_CharDisp(uint8_t dato);
//void StringLCD(const char *letras );
//void ClearScreenLCD(void);
const char *yea;
char verga = 10;
void main(void){
    initLCD();
    WriteCMLCD(1);
    while(1){
        WriteDataLCD(1,1,verga);
        __delay_ms(50);
    }
        
    //StringLCD(yea);
    
    
}
void PulsoE(void){
    LCD_E = 0;
    __delay_ms(15);
    LCD_E = 1;
    //__delay_ms(30);
}

void WriteCMLCD(unsigned char CM){
    LCD_Data = 0xFF;
    LCD_Data = 0X14;
    LCD_Data &= 0x80;
    LCD_RS=0; // Identifica que se le esta mandando un comando
    LCD_RW = 1;
    PulsoE();
    if (LCD_Data == 0x80){
        PulsoE();
    }
    LCD_Data = CM; // Mandar comando a la LCD
    LCD_RS = 0;
    LCD_RW = 0;
    PulsoE();
    __delay_ms(5);
    return;
}

void WriteDataLCD(uint8_t y, uint8_t x, char *msg ){
    uint8_t dato;
    switch(y)
    {
        case 1: dato = 128+x;
        break;
        case 2: dato = 192+x;
        break;
        default:
            break;
}
    WriteCMLCD(dato);
    while(*msg){
        LCD_CharDisp(*msg);
        msg ++;
    }
}
void LCD_CharDisp (uint8_t dato){
    LCD_E =0;
    LCD_RS =1;
    PORTBbits.RB7 = (dato & 0b10000000)>>7;
    PORTBbits.RB7 = (dato & 0b01000000)>>6;
    PORTBbits.RB7 = (dato & 0b00100000)>>5;
    PORTBbits.RB7 = (dato & 0b00010000)>>4;
    PORTBbits.RB7 = (dato & 0b00001000)>>3;
    PORTBbits.RB7 = (dato & 0b00000100)>>2;
    PORTBbits.RB7 = (dato & 0b00000010)>>1;
    PORTBbits.RB7 = (dato & 0b00000001);
    __delay_ms(10);
    LCD_E = 1;
    __delay_ms(5);
    LCD_E =0;
    __delay_ms(5);
    __delay_ms(30);
            
}

void initLCD(void){
   LCD_E = 0;// Inicializar variables y puertos
   LCD_RS = 0;
   LCD_RW = 0;
   LCD_Data = 0;
   LCD_E_Dir = 0;
   LCD_RS_Dir = 0;
   LCD_Data_IO = 0;
   LCD_RW_Dir = 0;
    
    __delay_ms(30);
    WriteCMLCD(56);
    
    //__delay_ms(6);
    WriteCMLCD(12);
    
    //__delay_us(300);
    WriteCMLCD(1);
    
    //__delay_ms(2);
     WriteCMLCD(6);
     //__delay_ms(25);
    
    WriteCMLCD(128); //Set interface Lenght to 8,2 lines, font 5*7
//    WriteCMLCD(0x010); //Apagar Display,
//    WriteCMLCD(0x001); //Limpiar Display
//    WriteCMLCD(0x7); //Direccion de movimiento del cursor, shift display
//    WriteCMLCD(0b00001111); //Enable display, cursor y blink
    
}

//void StringLCD(const char *letras){ //Parametro Volatil
//    while(*letras){
//        WriteDataLCD(*letras ++);
//    }
//}
//
//void ClearScreenLCD(void){
//    WriteCMLCD(0x01);
//    __delay_ms(2);
//}
//#define LcdDataBus      PORTB
//#define LcdControlBus   PORTD
//
//#define LcdDataBusDirnReg   TRISB
//#define LcdCtrlBusDirnReg   TRISD
//
//#define LCD_RS     PORTB
//#define LCD_RW     1
//#define LCD_EN     2

//void Lcd_CmdWrite(char cmd)
//{
//    LcdDataBus = cmd;               //Send the Command nibble
//    LcdControlBus &= ~(1<<LCD_RS);  // Send LOW pulse on RS pin for selecting Command register
//    LcdControlBus &= ~(1<<LCD_RW);  // Send LOW pulse on RW pin for Write operation
//    LcdControlBus |= (1<<LCD_EN);   // Generate a High-to-low pulse on EN pin
//    __delay_ms(100);
//    LcdControlBus &= ~(1<<LCD_EN); 
//
//    delay(10000);
//}