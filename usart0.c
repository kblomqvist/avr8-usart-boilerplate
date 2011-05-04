#include <stdio.h>
#include <avr/io.h>
#include "usart0.h"

int usart0_putchar(char c, FILE *stream) {
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}

int usart0_getchar(FILE *stream) {
    while(!USART0_DATARECEIVED);
    return UDR0;
}

