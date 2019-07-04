#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"
void initialise_uart()
{
    //	(a) Implement a function called initialise_uart which requires no arguments and
    //	returns no value.
    //	(a.a) Set the data transmission rate to 4800 bits per second,
    //	using the formula provided in the Topic 10 Technical Notes.
    UBRR1 = (F_CPU / 4 / 4800 - 1) / 2;
    //	(a.b) Set the UART speed to double speed.
    UCSR1A = (1 << U2X1);
    //	(a.c) Enable receive and transmit, but do not enable any UART-related
    //	interrupts.
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);

    //	(a.d) Set the character size to 8 bits, with no parity
    //	and 2 stop bits.
    UCSR1C = (0 << UPM10) | (0 << UPM11) | (0 << UCSZ12) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << USBS1);
    //	(b) End of function initialise_uart
}
int main(void)
{
    initialise_uart();

    for (;;)
    {
    }
}
