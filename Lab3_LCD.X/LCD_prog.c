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

void main(void){
    
}