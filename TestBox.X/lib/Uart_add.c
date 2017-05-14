/*
 * File:   Uart_add.c
 * Author: ROBERT
 *
 * Created on February 27, 2017, 11:21 PM
 */

#include <Uart_add.h>
#include "xc.h"

// send a character to the UART2 serial port
int putU2(int c)
{
	while ( U2STAbits.UTXBF);   // wait while Tx buffer full
	U2TXREG = c;
	return c;
} 

// send a null terminated string to the UART2 serial port
void putsU2( char *s)
{
    while( *s)                  // loop until *s == '\0' the  end of the string
        UART2_Write( *s++);     // send the character and point to the next one
    UART2_Write( '\r');         // terminate with a cr / line feed
    UART2_Write( '\n');
} // putsU2


// wait for a new character to arrive to the UART2 serial port
char getU2(void)
{
	while ( !U2STAbits.URXDA);	// wait for a new character to arrive
	return U2RXREG;		// read the character from the receive buffer
}

//
char *getsU2(char *s, int len)
{
    char *p = s;            // copy the buffer pointer 
    do
    {
        *s = getU2();       // wait for a new character
        putU2( *s);         // echo character       
        if (( *s==BACKSPACE)&&( s>p))
        {
            putU2(' ');     // overwrite the last character
            putU2(BACKSPACE);
            len++;
            s--;            // back the pointer
            continue;
        }
        if ( *s=='\n')      // line feed, ignore it
            continue;
        if ( *s=='\r')      // end of line, end loop
            break;          
        s++;                // increment buffer pointer
        len--;
    } 
    while ( len>1 );      // until buffer full 
    *s = '\0';              // null terminate the string    
    return p;               // return buffer pointer
}