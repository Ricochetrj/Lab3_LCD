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

#include <xc.h>
#include <stdint.h>

#define LCD_E PORTDbits.RD6
#define LCD_RS PORTDbits.RD7
#define LCD_Data PORTB

#define LCD_E_Dir TRISDbits.TRISD6
#define LCD_RS_Dir TRISDbits.TRISD7
#define LCD_Data_IO TRISB

#define _XTAL_FREQ 4000000
void PulsoE(void);
void WriteCMLCD(unsigned char CM);
void WriteDataLCD( char msg);
void initLCD(void);
void StringLCD(const char *letras );
void ClearScreenLCD(void);
const char *yea;
void main(void){
    initLCD();
    StringLCD(yea);
    
    
}
void PulsoE(void){
    LCD_E = 1;
    __delay_us(10);
    LCD_E = 0;
    __delay_us(10);
}

void WriteCMLCD(unsigned char CM){
    LCD_RS=0; // Identifica que se le esta mandando un comando
    LCD_Data = CM; // Mandar comando a la LCD
    PulsoE();
}

void WriteDataLCD(char msg ){
    LCD_RS = 1;
    LCD_Data = msg;
    PulsoE();
}

void initLCD(void){
   LCD_E = 0;// Inicializar variables y puertos
   LCD_RS = 0;
   LCD_Data = 0;
   LCD_E_Dir = 0;
   LCD_RS_Dir = 0;
   LCD_Data_IO = 0;
    
    __delay_ms(40);
    WriteCMLCD(0x30);
    
    __delay_ms(6);
    WriteCMLCD(0x30);
    
    __delay_us(300);
    WriteCMLCD(0x30);
    
    __delay_ms(2);
    
    WriteCMLCD(0x38); //Se manda la funcion
    WriteCMLCD(0x0C); //Encender Display, Apagar cursor, Apagar Parpadeo
    WriteCMLCD(0x01); //Limpiar Display
    WriteCMLCD(0x06); //Entry mode
    
}

void StringLCD(const char *letras){ //Parametro Volatil
    while(*letras){
        WriteDataLCD(*letras ++);
    }
}

void ClearScreenLCD(void){
    WriteCMLCD(0x01);
    __delay_ms(2);
}
