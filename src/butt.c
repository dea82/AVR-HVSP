/*
 * butt.c
 *
 *  Created on: 13 jul 2015
 *      Author: andreas
 */
#include <avr/interrupt.h>
#include <avr/io.h>

#include "conf.h"
#include "type.h"

#define TICK 20 // [ms]
#define TIMER_TICKS_TO_REACH_ISR 3
#define TIMER_PRESCALER 8
#define TIMER_INIT_VALUE (0xFFFF - (TICK*F_CPU/TIMER_PRESCALER/1000) + 1 + TIMER_TICKS_TO_REACH_ISR)

void Butt_init(void)
{
    /* Activate internal pull-up */
    CONF_IO(SELECT_BTN_CFG, INPUT, PULLUP);
    CONF_IO(RESET_BTN_CFG, INPUT, PULLUP);

	/* Initialize timer */
	TCCR0B = _BV(CS11);
	TCNT1 = TIMER_INIT_VALUE;
	TIMSK = _BV(TOIE1);
}


void Butt_loop(void)
{

}

ISR(TIMER1_OVF_vect)
{
	/* How to figure out start value:
	 * Number of clock cycles to reach interrupt is normally minimum 4 clock cycles:
	 *
		push	r1				#2
		push	r0				#2
		in	r0, 0x3f	; 63	#1
		push	r0				#2
		eor	r1, r1				#1
		push	r24				#2
		push	r25				#2
		ldi	r24, 0xE0	; 224	#1
		ldi	r25, 0xB1	; 177	#1
		out	0x2d, r25	; 45	#1
		out	0x2c, r24	; 44	#1

	 Total: 4 + 16 = 20 clock cycles.

	 Timer prescaler  is 8 => ~3 timer ticks



	 */
	TCNT1 = TIMER_INIT_VALUE;
}

void Butt_sampleButton(tB sample_B)
{

}
