/* 
 * File:   LCDFunctions.h
 * Author: rodri
 *
 * Created on 7 de febrero de 2020, 03:22 PM
 */
#include <xc.h> // include processor files - each processor file is guarded.  
#ifndef __LCDFUNCTIONS_H
#define	__LCDFUNCTIONS_H
void delay(int cnt);
void Lcd_CmdWrite(char cmd);
void Lcd_DataWrite(char dat);
void StartLCD(void);


#endif	/* LCDFUNCTIONS_H */

