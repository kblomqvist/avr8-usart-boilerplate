#ifndef __USART_H
#define __USART_H 1

#define USART_DATARECEIVED (UCSR0A & (1 << RXC0))
#define USART_ESCAPE (USART_DATARECEIVED && (getchar() == 27))

/*  Send character */
int usart_putchar(char c, FILE *stream);

/*  Receive character */
uint8_t usart_getchar(FILE *stream);

#endif

