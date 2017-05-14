/* 
 * File:   Uart_add.h
 * Author: ROBERT
 *
 * Created on February 27, 2017, 11:23 PM
 */

#ifndef  _Uart_add_h
#define  _Uart_add_h

#include "uart2.h"

// useful macros
#define Clrscr() putsU2("\x1b[2J")			// clear the screen
#define Home()	 putsU2("\x1b[1;1H")		// return cursor home
#define pcr()	 putsU2("\r"); putsU2("\n")	// carriage return
#define BACKSPACE 0x8   // ASCII backspace character code 

// send a null terminated string to the serial port
void putsU2(char *s);

// send a character to the serial port
int putU2(int c);

// wait for a new character to arrive to the serial port
char getU2(void);

// receive a null terminated string in a buffer of len char
char * getsU2(char *s, int n);

#endif