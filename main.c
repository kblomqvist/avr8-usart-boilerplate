/**
 * AVR8 USART Boilerplate
 *
 * Quickly setup 8-bit AVR microcontroller to communicate through USART
 *
 * REQUIREMENTS
 * - WinAVR toolchain
 * - Originally coded for ATmega88PA. Check register names if other MCU is used.
 *
 * HISTORY
 * - 05/03/2011 Initial version
 *
 * @copyright Copyright (c) 2011 Kim Blomqvist
 * @license   http://creativecommons.org/licenses/by/3.0/ (CC BY 3.0)
 */

#include <stdlib.h>    // general utilities
#include <stdio.h>     // standard io facilities
#include <avr/io.h>    // avr device-specific io definitions
#include <avr/power.h> // power reduction management
#include "usart.h"

#ifndef F_CPU
    #error Define F_CPU (CPU frequency) in your makefile
#endif

/*  Usart
 * ----------------------------------------------------------------------*/
#define BAUD      19200   // baud rate, see <util/setbaud.h>
#define BOUD_TOL  2       // baud tolerance 2%, see <util/setbaud.h>
#define USE_2X    0       // don't use prescaler, see <util/setbaud.h>
#include <util/setbaud.h> // helper macros for baud rate calculations

#define USART_PORT DDRD   // usart port
#define USART_RX   DDD0   // usart rx pin
#define USART_TX   DDD1   // usart tx pin

/*  Setup streams for communication via usart */
static FILE usart_stream = FDEV_SETUP_STREAM(
    usart_putchar, usart_getchar, _FDEV_SETUP_RW);

/*  Usart initiliazator */
void usart_init()
{
    /*  Set baud rate using avr-libc helper macros */
    UBRR0L = UBRRL_VALUE;
    UBRR0H = UBRRH_VALUE;
    
    /*  Asynchronous USART, Parity = none, Stop bits = 1, Data bits = 8 */
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    
    /*  Enable RX and TX */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    /*  Override general io pins for usart rx/tx */
    USART_PORT &= ~_BV(USART_RX);
    USART_PORT |= _BV(USART_TX);
}

/*  Main
 * ----------------------------------------------------------------------*/
void init(void)
{
    /*  Initialize general io pins */

    // @todo It's always a good idea to specifically setup io pin states
    // before doing anything special, but i'm feeling lazy with this

    /*  Make sure that usart module is powered up. Note that modules has to be
     *  reinitialized if powered down. */
    power_usart0_enable();

    /*  Initialize usart and declare standard input and output streams */
    usart_init();
    stdin = stdout = &usart_stream;
}

int main(void)
{
    /*  Initialize */
    init();

    /*  Main loop */
    while (1) {
        printf("Command >> ");
        switch (getchar()) { // wait user input
            case 'h':
                printf("\r\n");
                printf("s = Say \"Hello!\" in loop\r\n");
                printf("h = Help\r\n");
                break;

            case 's':
                for(;;) {
                    if (USART_ESCAPE) // break if ESC was pressed
                        break;
                    printf("\r\nHello! Press ESC to stop!");
                }
                break;
            default:
                printf("\r\nPress 'h' for help");
        }
        printf("\r\n");
    }
}

