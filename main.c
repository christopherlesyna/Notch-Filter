//-----------------------------------------------------------------------------
// Title:   Technical Training Organization (TTO) SYS/BIOS 1.5-DAY Workshop 0.80
// File:	main.c 
// Rev:		0.80
// Date:	07-25-2011
// Author:	Eric Wilbur (ericw@ti.com)
// Ref:		C6748 BSL, Experimenter Test Example (audio, mcasp)
//
// Brief:	Definitions, prototypes and externs
//
// Notes:	1. Refer to main.h for key definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"


//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
int16_t echo_buff_l[BUFFSIZE];
int16_t echo_buff_r[BUFFSIZE];

int16_t buff_fir_l[FIRSIZE];
int16_t buff_fir_r[FIRSIZE];

int16_t buff_iir_x_l[IIRSIZE];
int16_t buff_iir_x_r[IIRSIZE];
int16_t buff_iir_y_l[IIRSIZE];
int16_t buff_iir_y_r[IIRSIZE];

uint16_t leftRight = LEFT;

//-----------------------------------------------------------------------------
// main()
//-----------------------------------------------------------------------------

void main(void)
{
    init_buffers();								// zero buffers					

   	I2C_init(I2C0, I2C_CLK_400K);				// init I2C comm channel

   	McASP_Init_TTO();							// init McASP
   	AIC3106_Init_TTO();							// init AIC3106

	McASP_Start_TTO();							// start McASP clocks

	BIOS_start();  								// start BIOS scheduler
}												 


//-----------------------------------------------------------------------------
// init_buffers()
//-----------------------------------------------------------------------------

void init_buffers(void)
{
uint32_t i;

	for (i=0; i<BUFFSIZE; i++){
		echo_buff_l[i]=0;
		echo_buff_r[i]=0;
	}

	for (i=0; i<FIRSIZE; i++){

		buff_fir_l[i] = 0;
		buff_fir_r[i] = 0;
	}

	for (i=0; i<IIRSIZE; i++){
		buff_iir_x_l[i] = 0;
		buff_iir_x_r[i] = 0;
		buff_iir_y_l[i] = 0;
		buff_iir_y_r[i] = 0;
	}
}


//-----------------------------------------------------------------------------
// USTIMER_delay()
//
// LogicPD BSL fxn - re-written for a few BSL.c files that need it.
// The original USTIMER_init() is not used because it is NOT BIOS compatible
// and took both timers so that BIOS PRDs would not work. This is a
// workaround.
//
// If you need a "delay" in this app, call this routine with the number
// of usec's of delay you need. It is approximate - not exact.
// value for time<300 is perfect for 1us. We padded it some.
//-----------------------------------------------------------------------------

void USTIMER_delay(uint32_t usec)
{
	volatile int32_t i, start, time, current;

	for (i=0; i<usec; i++)
	{
		start = Timestamp_get32();
		time = 0;
		while (time < 350)
		{
			current = Timestamp_get32();
			time = current - start;
		}
	}
}



