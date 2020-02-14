
#ifndef LCD_INSTRUCTIONS_H
#define	LCD_INSTRUCTIONS_H
#define RS PORTDbits.RD0
#define EN PORTDbits.RD1

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned char *buffer[10];
uint8_t i;
uint8_t valadc;
float voltaje;
void lcd_chara(uint8_t dato);
void ftoa2(float n, char* res, int afterpoint);
void ADCinit(void){
    ADCON1bits.ADFM =0;// Justificacion izquierda y voltajes de referencia VDD y VSS
    ADCON1bits.VCFG0 =0;
    ADCON1bits.VCFG1 =0;
    ADCON0bits.ADCS0 =1;// Iniciar ADC y determinar como va a leer
    ADCON0bits.ADCS1 =0;
    ADCON0bits.ADON = 1;
                   }

void lcd_puerto(char a){ // Mandar valores al puerto donde esta conectado la LCD
    PORTA = a;
}

void lcd_comando(char a){ // Apagar RS para que la LCD sepa que se le esta mandando un comando y no datos
    RS = 0;
    lcd_puerto(a);
    EN = 1;
    __delay_us(5);
    EN = 0;
}

void lcd_clear(void){ // Limpiar pantalla de la LCD
	lcd_comando(0);
	lcd_comando(1);
}
void lcd_cursor(char a, char b){ // Poner el cursor de la LCD en una posicion para que imprima caracteres ahi
	char temp;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
      lcd_comando(temp);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		
        lcd_comando(temp);
	}
    __delay_ms(4);
}

void lcd_init() // Mandar los comandos segun la guia, para inicializar la LCD
{
 
   __delay_ms(20);
  lcd_comando(0x30);
	__delay_ms(10);
  lcd_comando(0x30);
	__delay_us(110);
  lcd_comando(0x30);
	__delay_ms(11);
 
  /////////////////////////////////////////////////////
  lcd_comando(0x38);
  __delay_ms(4);
  lcd_comando(0x08);
  __delay_ms(4);
  lcd_comando(0x01);
  __delay_ms(4);
  lcd_comando(0x06);
  __delay_ms(4);
  lcd_comando(0x0C);
  __delay_ms(4);
}

void lcd_char(char a) // Mandar un solo character a la LCD
{
   RS = 1;             // => RS = 1
   lcd_puerto(a);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
}



void lcd_palabra(char *a) // Mandar string de caracteres y leerlos 1 por 1
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   lcd_char(a[i]);
}

void Lcd_Shift_Right()// Correr la pantalla a la Derecha
{
	lcd_comando(0x01);
	lcd_comando(0x0C);
}

void Lcd_Shift_Left() // Correr la Pantalla a la izquierda
{
	lcd_comando(0x01);
	lcd_comando(0x08);
}

void ADCread(){ // Iniciar lectura de ADC, Esperar a que termine de leer, convertir dato de 0-1024 a 0-5 y desplegar los decimales en la LCD 
    __delay_ms(10);
    ADCON0bits.GO_DONE=1;
    while(ADCON0bits.GO_DONE);
    valadc= ADRESH;
    voltaje=valadc*5.0/255.0;
 // itoa(buffer,voltaje,10);
    ftoa2(voltaje,buffer,2);

    lcd_palabra(buffer);
    __delay_ms(50);
    
}
void ADC2read(void){ // Iniciar lectura de ADC, Esperar a que termine de leer, convertir dato de 0-1024 a 0-5 y desplegar los enteros en la LCD 
    __delay_ms(10);
    ADCON0bits.GO_DONE=1;
    while(ADCON0bits.GO_DONE);
    valadc= ADRESH;
    voltaje=valadc*5.0/255.0;
     itoa(buffer,voltaje,10);
    lcd_palabra(buffer);
    __delay_ms(50);
    
}

////Tomado de Geeks- Fuuncion para convertir Floats y Doubles en Strings
void reverse(char* str, int len){
    int i = 0, j= len - 1, temp;
    while (i<j){
        temp = str[  i ];
        str[i] = str[j];
        str[j] = temp ;
        i++;
        j--;
    }
}

int intToStr (int x, char str[], int d){
    int i = 0;
    while(x){
        str[i++] = (x % 10) + '0';
        x =x/10;
    }
    while(i<d){
        str[i++] = '0';
        reverse(str,i);
        str[i] = '\0';
        return i;
    }
}

void ftoa2(float n, char* res, int afterpoint){
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = intToStr(ipart, res, 0);
    if(afterpoint != 0){
        res[i] = '.';
        fpart = fpart* pow(10,afterpoint);
        intToStr((int)fpart, res +1,afterpoint);
                
    }
}

#endif	/* LCD_INSTRUCTIONS_H */

