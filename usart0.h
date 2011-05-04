#ifndef __USART0_H
#define __USART0_H 1

#define USART0_DATARECEIVED (UCSR0A & (1 << RXC0))
#define USART0_ESCAPE (USART0_DATARECEIVED && (getchar() == 27))

/*  Send character */
int usart0_putchar(char c, FILE *stream);

/*  Receive character */
int usart0_getchar(FILE *stream);

#endif

