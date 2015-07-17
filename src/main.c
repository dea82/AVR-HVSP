/*
 * main.c
 *
 *  Created on: 11 jul 2015
 *      Author: andreas
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "butt.h"
#include "disp.h"

#define MYUBBR ((F_CPU / (9600 * 16L)) - 1)


int main(void)
{
	/* Check for WDT reset (save code size and assume true) - if a runaway pointer enables it,
	 * then it must be disabled here because it's kept after a reset! Ref. AVR132 chap 2.4. */
	WDTCSR = 0;

	Butt_init();
	Disp_init();

	sei();
	Butt_sampleButton(TRUE);


	for (;;)
	{

	}
	return 0;
}
