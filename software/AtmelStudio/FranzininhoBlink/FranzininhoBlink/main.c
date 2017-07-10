/*
 * FranzininhoBlink.c
 *
 * Created: 07/07/2017 21:20:40
 * Author : fabio
 */ 

#define F_CPU 8000000UL   //clock em 8 MHz

#include <avr/io.h>
#include "util/delay.h"


int main(void)
{
	DDRB = 0b00000010;   //configura PB1 como saída
	
	/* Replace with your application code */
	while (1)
	{
		PORTB ^=(1<<PB1);
		_delay_ms(500);
	}
}

