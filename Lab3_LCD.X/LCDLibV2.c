/*
 * File:   LCDLibV2.c
 * Author: rodri
 *
 * Created on 10 de febrero de 2020, 03:26 PM
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

#include <xc.h>
#include <stdint.h>

#define rs PORTDbits.RD7
#define rw PORTDbits.RD5
#define en PORTDbits.RD6
#define delay for(j=0;j<1000;j++)

int j;
unsigned int i;
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void Start(void);

void main()
{
    
    Start();
    lcd_init();
    cmd(0x90);
    show("Puto");
    while(1) {
        for(i=0;i<15000;i++);
        cmd(0x18);  //Shift Entire Display to the left
        for(i=0;i<15000;i++);
        
    }   
}
void Start(void){
    TRISB = 0;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    rs = 0;
    rw = 0;
    en = 0;
    j =0;
    i = 0;
    
            
}
void lcd_init()
{
    cmd(0x38); //2 Filas, 5x7
    cmd(0x0C); //Encender Display, Apagar Cursor
    cmd(0x06); // Incrementar Cursor- Mover a la derecha
    cmd(0x80); //Obligar al cursor al inicio de la primera linea
}
 
void cmd(unsigned char a)
{
    PORTB=a;
    rs=0;
    rw=0;
    en=1;
    delay;
    en=0;
}
 
void dat(unsigned char b)
{
    PORTB=b;
    rs=1;
    rw=0;
    en=1;
    delay;
    en=0;
}
 
void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}

void ADCencender(void) {
    ADCON0bits.ADCS1 = 0;//Fosc/8
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.CHS = 0b0111; //Canal 7
    ADCON0bits.ADON = 0;//Apagar ADC
    ADCON1bits.VCFG0 = 0; //LEFT Justified
    ADCON1bits.VCFG1 = 0; //VDD
    ADCON1bits.ADFM = 0; //VSS
    
    PIE1bits.ADIE = 1; //Enable ADC interrupt
    PIR1bits.ADIF = 0; //Bandera = 0
    return;}