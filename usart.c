#include <stdio.h>
#include <avr/io.h>
#include "usart.h"

int usart_putchar(char c, FILE *stream) {
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
	return 0;
}

uint8_t usart_getchar(FILE *stream) {
	while(!USART_DATARECEIVED);
	return UDR0;
}

