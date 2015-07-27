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
#include "coio.h"
#include "conf.h"
#include "disp.h"
#include "ledc.h"

#define MYUBBR ((F_CPU / (9600 * 16L)) - 1)

#define TIMER_TICKS_TO_REACH_ISR 3
#define TIMER_PRESCALER 8
#define TIMER_INIT_VALUE (0xFFFF - (TICK*F_CPU/TIMER_PRESCALER/1000) + 1 + TIMER_TICKS_TO_REACH_ISR)

typedef enum
{
	INIT_E, DEVICE_E, LO_FUSE_E, HI_FUSE_E, EXT_FUSE_E, ERR_E
} tSelectState_E;

static char * byteToDispString_pC(tU08 byte_U08);

volatile static tB tick_B;

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
	tick_B = TRUE;
}

int main(void)
{
	/* Check for WDT reset (save code size and assume true) - if a runaway pointer enables it,
	 * then it must be disabled here because it's kept after a reset! Ref. AVR132 chap 2.4. */
	WDTCSR = 0;

	Butt_init();
	Coio_init();
	Disp_init();
	Ledc_init();

	/* Initialize timer */
	TCNT1 = TIMER_INIT_VALUE;
	TCCR1B = _BV(CS11);
	TIMSK = _BV(TOIE1);

	sei();

	for (;;)
	{

		static tSelectState_E selectState_E = INIT_E;

		if (tick_B == TRUE)
		{
			Butt_update();
			if (Butt_pressed_B(BUTT_RESET_E) == TRUE)
			{
				tU16 timePressed_U16 = Butt_getTickInState_U08(
						BUTT_RESET_E) * TICK;
				Ledc_set(LEDC_NONE_E);
				if (timePressed_U16 < 1000)
				{
					Disp_write("4---");

				}
				else if (timePressed_U16 < 2000)
				{
					Disp_write("-3--");
				}
				else if (timePressed_U16 < 3000)
				{
					Disp_write("--2-");
				}
				else if (timePressed_U16 < 4000)
				{
					Disp_write("---1");
				}
				else if (timePressed_U16 >= 5000)
				{

				}

			}
			else

			{
				if (Butt_pressedFlank_B(BUTT_SELECT_E) == TRUE
						|| selectState_E == INIT_E)
				{
					if (selectState_E >= EXT_FUSE_E)
					{
						selectState_E = DEVICE_E;
					}
					else
					{
						selectState_E++;
					}
					if (Coio_readChip_E() != COIO_OK_E)
					{
						selectState_E = ERR_E;
					}
					IO_SET(BUZZ_CFG);
					_delay_ms(10);
					IO_CLR(BUZZ_CFG);

				}
				switch (selectState_E)
				{
				case DEVICE_E:
					Ledc_set(LEDC_DEVICE_E);
					Disp_write("----");
					break;
				case LO_FUSE_E:
					Ledc_set(LEDC_LO_FUSE_E);
					Disp_write(byteToDispString_pC(Coio_getLowFuse_U08()));
					break;
				case HI_FUSE_E:
					Ledc_set(LEDC_HI_FUSE_E);
					Disp_write(byteToDispString_pC(Coio_getHighFuse_U08()));
					break;
				case EXT_FUSE_E:
					Ledc_set(LEDC_EXT_FUSE_E);
					Disp_write(byteToDispString_pC(Coio_getExtendedFuse_U08()));
					break;
				case ERR_E:
					Ledc_set(LEDC_NONE_E);
					Disp_write("E---");
					break;
				default:
					Disp_write("E--8");
					break;
				}

			}

			tick_B = FALSE;
		}
	}
	return 0;
}

static char * byteToDispString_pC(tU08 byte_U08)
{
	static char buff[4];
	tU08 i_U08;

	buff[0] = ' ';
	buff[1] = ' ';

	for (i_U08 = 0; i_U08 < 2; i_U08++)
	{
		if ((byte_U08 & 0xF) < 0xA)
		{
			buff[3 - i_U08] = (byte_U08 & 0xF) + 0x30;
		}
		else
		{
			buff[3 - i_U08] = (byte_U08 & 0xF) + 0x37;
		}
		byte_U08 = byte_U08 >> 4;
	}

	return buff;
}
