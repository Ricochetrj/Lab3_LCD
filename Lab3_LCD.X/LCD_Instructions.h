/* 
 * File:   LCD_Instructions.h
 * Author: rodri
 *
 * Created on 10 de febrero de 2020, 08:03 PM
 */

#ifndef LCD_INSTRUCTIONS_H
#define	LCD_INSTRUCTIONS_H
#define RS PORTDbits.RD0
#define EN PORTDbits.RD1


#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
unsigned char *buffer[7];
uint8_t i;
uint8_t valadc;

//uint8_t valana2;
char word;
int voltaje;
//float voltaje2;
void lcd_chara(uint8_t dato);

void ADCinit(void){
    ADCON1bits.ADFM =0;
    ADCON1bits.VCFG0 =0;
    ADCON1bits.VCFG1 =0;
    ADCON0bits.ADCS0 =1;
    ADCON0bits.ADCS1 =0;
    //ADCON0bits.CHS = 0;
    ADCON0bits.ADON = 1;
                   }

void lcd_puerto(char a){
    PORTA = a;
}

void lcd_comando(char a){
    RS = 0;
    lcd_puerto(a);
    EN = 1;
    __delay_us(5);
    EN = 0;
}

void lcd_clear(void){
	lcd_comando(0);
	lcd_comando(1);
}
void lcd_cursor(char a, char b){
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

void lcd_init()
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

void lcd_char(char a)
{
   RS = 1;             // => RS = 1
   lcd_puerto(a);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
}



void lcd_palabra(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   lcd_char(a[i]);
}

void Lcd_Shift_Right()
{
	lcd_comando(0x01);
	lcd_comando(0x0C);
}

void Lcd_Shift_Left()
{
	lcd_comando(0x01);
	lcd_comando(0x08);
}

void ADCread(){
    __delay_ms(10);
    ADCON0bits.GO_DONE=1;
    while(ADCON0bits.GO_DONE);
    valadc= ADRESH;
    voltaje=valadc;//*5.0/255.0;
    itoa(buffer,voltaje,10);

    lcd_palabra(buffer);
    __delay_ms(50);
    
}

void lcd_chara (uint8_t dato){
    EN =0;
    RS =1;
    RB7 = (dato & 0b10000000)>>7;
    RB6 = (dato & 0b01000000)>>6;
    RB5 = (dato & 0b00100000)>>5;
    RB4 = (dato & 0b00010000)>>4;
    RB3 = (dato & 0b00001000)>>3;
    RB2 = (dato & 0b00000100)>>2;
    RB1 = (dato & 0b00000010)>>1;
    RB0 = (dato & 0b00000001);
    __delay_ms(10);
    EN = 1;
    __delay_ms(5);
    EN = 0;
    __delay_ms(5);
    __delay_ms(30);
    
}
#endif	/* LCD_INSTRUCTIONS_H */

