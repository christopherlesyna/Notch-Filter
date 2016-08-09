/*
 *
 */
//-----------------------------------------------------------------------------
// Title:   Technical Training Organization (TTO) SYS/BIOS 1.5-DAY Workshop 0.80
// File:	isr.c 
// Rev:		0.8
// Date:	07-25-2011
// Author:	Eric Wilbur (ericw@ti.com)
// Ref:		C6748 BSL, Experimenter Test Example (audio, mcasp)
//
// Brief:	Interrupt Service Routine (INT5), Triggered when RDATA/XDATA ready
//          One ISR for both RCV/XMT, Read & Write 32 bits EVERY INTERRUPT
//          McASP combines interrupts (RCV/XMT), Datasheet = EVT SRC #61
//			With a combined interrupt, we must check to see WHICH side (RCV or XMT)
//			caused the interrupt. Otherwise, we are reading or writing twice
//			the necessary data (and it causes a slight static noise).
//
//
// Notes:	1. Refer to main.h for key definitions
//			2. Refer to .CFG (INT5) properties for more info
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
//#include "main.h"
//#include <math.h>  //UNCOMMENT THESE

//#define FIR
//#define IIR
//#define ECHO
//#define MULTIRATE

//-----------------------------------------------------------------------------
// isrAudio()
//-----------------------------------------------------------------------------

/*
void isrAudio(void)
{
	static uint32_t sample = 0;
	static int32_t dataIn32, dataOut32;

	static int16_t temp;
	static int16_t temp_1;
	int notchfilt[15] = {0.0736, 0.1009, .01273, .1514, 0.1717, .1871, .1967, -.8, .1967, .1871, .1717, .1514, .1273, .1009, 0.0736};
	static int16_t *buffer_local_l, *buffer_local_r;
	static int16_t *buffer_x_l, *buffer_x_r, *buffer_y_l, *buffer_y_r;
	static int16_t *buffer_left, *buffer_right;

	float num[3] = {1, -1.902, 1};
	float den[3] = {1, -1.9, .998001};
	float IIR[5] = {1, -1.902, 1, 1.9, -.998001};


	if (sample == 0){
		buffer_local_l = echo_buff_l;
		buffer_local_r = echo_buff_r;

		buffer_left = buff_fir_l;
		buffer_right = buff_fir_r;

		buffer_x_l = buff_iir_x_l;
		buffer_x_r = buff_iir_x_r;
		buffer_y_l = buff_iir_y_l;
		buffer_y_r = buff_iir_y_r;
	}

	if(CHKBIT(MCASP->SRCTL12, RRDY)) {				//if ISR triggered by XRDY...
		dataIn32 = MCASP->XBUF12;
		temp = (int16_t) dataIn32;
		int16_t n=0;
		int16_t i=0;
		float dataout;
		*/

		//temp_1 = 0.7*temp + 307*sin(2*3.1415926*2400/48000*sample);  //Part 3 sinusoid


		/*
		//buff_fir_l, PART 4
		uint16_t i=0;
		if(!leftRight){

			while(1)
			{
			buffer_left[i%FIRSIZE] = temp[i%FIRSIZE];
			for(x4=0;x4<14;x4=x4+1){
				temp_1 = temp_1 + (notchfilt[x4])*buffer_left[x4];
			}
			i++;
			}

			//temp_1 = 0.7*temp + 0.3*buffer_local_l[sample];  //OLD CODE
			//buffer_local_l[sample] = temp;
		}
		else{


			//temp_1 = 0.7*temp + 0.3*buffer_local_r[sample];  //OLD CODE
			//buffer_local_r[sample] = temp;
		}
		//END PART 4
	 */




		//buff_iir_1, PART 5

/*
		if(leftRight)
			{
				for (i = 2; i>-1; i--){
				buff_iir_x_r[i+1] = buff_iir_x_r[i];
				buff_iir_y_r[i+1] = buff_iir_y_r[i];
				}
				buff_iir_x_r[0] = (temp + 307*sin(2*3.14*24/480*sample));

				buff_iir_y_r[0] = 0;
				for (i=0; i<3; i++){
					buff_iir_y_r[0] = buff_iir_y_r[0] + buff_iir_x_r[i] *num[i];
				}
				for (i=0; i<2; i++){
					buff_iir_y_r[0] = buff_iir_y_r[0] + buff_iir_y_r[i] *den[i];
				}
				dataout = buff_iir_y_r[0];

				MCASP->XBUF11 = (int32_t)dataout;  // command to play
				sample++;
	   		}
			else {
				for (i = 2; i>-1; i--){
	//			buffer_right[i+1] = buffer_right[i];
					buff_iir_x_l[i+1] = buff_iir_x_l[i];
					buff_iir_y_l[i+1] = buff_iir_y_l[i];
				}
				buff_iir_x_l[0] = (temp + 307*sin(2*3.14*24/480*sample));

				buff_iir_y_r[0] = 0;
				for (i=0; i<3; i++){
					buff_iir_y_l[0] = buff_iir_y_l[0] + buff_iir_x_l[i] *num[i];
				}
				for (i=0; i<2; i++){
					buff_iir_y_l[0] = buff_iir_y_l[0] + buff_iir_y_l[i] *den[i];
				}
				dataout = buff_iir_y_l[0];

				MCASP->XBUF11 = (int32_t)dataout;  // command to play
			}


			if (sample >= 20){
				sample = 0;
			}
			leftRight ^=1;
		}

		//END PART 5


*/


		/*
		//Part 2
		if(!leftRight){
			temp_1 = 0.7*temp + 0.3*buffer_local_l[sample];
			buffer_local_l[sample] = temp;
		}
		else{
			temp_1 = 0.7*temp + 0.3*buffer_local_r[sample];
			buffer_local_r[sample] = temp;
		}
		*/

/*

		dataOut32 = temp_1;
	}

	if(CHKBIT(MCASP->SRCTL11, XRDY)) {				//if ISR triggered by XRDY...
		MCASP->XBUF11 = dataOut32;

		if(leftRight)
			sample++;

		leftRight ^=1;
	}

	//if(sample>=0)
	if (sample == 24000)  //comment this line out once part 2 is done
		sample = 0;
}


*/







//-----------------------------------------------------------------------------
// Title:   Technical Training Organization (TTO) SYS/BIOS 1.5-DAY Workshop 0.80
// File:	isr.c
// Rev:		0.8
// Date:	07-25-2011
// Author:	Eric Wilbur (ericw@ti.com)
// Ref:		C6748 BSL, Experimenter Test Example (audio, mcasp)
//
// Brief:	Interrupt Service Routine (INT5), Triggered when RDATA/XDATA ready
//          One ISR for both RCV/XMT, Read & Write 32 bits EVERY INTERRUPT
//          McASP combines interrupts (RCV/XMT), Datasheet = EVT SRC #61
//			With a combined interrupt, we must check to see WHICH side (RCV or XMT)
//			caused the interrupt. Otherwise, we are reading or writing twice
//			the necessary data (and it causes a slight static noise).
//
//
// Notes:	1. Refer to main.h for key definitions
//			2. Refer to .CFG (INT5) properties for more info
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"
#include <math.h>

//#define FIR
//#define IIR
//#define ECHO
//#define MULTIRATE

//-----------------------------------------------------------------------------
// isrAudio()
//-----------------------------------------------------------------------------

int16_t sine_table[128]={0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724,0,724,1023,724,0,-724,-1023,-724};


void isrAudio(void)
{
	static uint32_t sample = 0;
	static int32_t dataIn32, dataOut32;

	static int16_t temp;
	static int16_t *buffer_local_l, *buffer_local_r;
	static int16_t *buffer_x_l, *buffer_x_r, *buffer_y_l, *buffer_y_r;
	static int16_t *buffer_left, *buffer_right;

	float FIR[15] = {.0368, .0505, .0636, .0756, .0858, .0935, .0984, -.4, .0984, .0935, .0858, .0756, .0636, .0505, .0368};
	FIR[0] = 2*FIR[0];
	FIR[1] = 2*FIR[1];
	FIR[2] = 2*FIR[2];
	FIR[3] = 2*FIR[3];
	FIR[4] = 2*FIR[4];
	FIR[5] = 2*FIR[5];
	FIR[6] = 2*FIR[6];
	FIR[7] = 2*FIR[7];
	FIR[8] = 2*FIR[8];
	FIR[9] = 2*FIR[9];
	FIR[10] = 2*FIR[10];
	FIR[11] = 2*FIR[11];
	FIR[12] = 2*FIR[12];
	FIR[13] = 2*FIR[13];
	FIR[14] = 2*FIR[14];

	float yyy[3] = {1, -1.807, .9025};
	float xxx[3]= {1, -1.9, 1};

	float IIIR[5] = {1, -1.9, 1, 1.807, -.9025};

	if (sample == 0){
		buffer_local_l = echo_buff_l;
		buffer_local_r = echo_buff_r;

		buffer_left = buff_fir_l;
		buffer_right = buff_fir_r;

		buffer_x_l = buff_iir_x_l;
		buffer_x_r = buff_iir_x_r;
		buffer_y_l = buff_iir_y_l;
		buffer_y_r = buff_iir_y_r;
	}

	if(CHKBIT(MCASP->SRCTL12, RRDY)) {				//if ISR triggered by XRDY...
		dataIn32 = MCASP->XBUF12;
		temp = (int16_t) dataIn32;
	}
//////////////////////////////////////////////////////////*
	int16_t n=0;
	int16_t i=0;
	float dataout;
	//, Buff_Fir_L[15],Buff_Fir_R[15];

//	if(CHKBIT(MCASP->SRCTL11, XRDY))    //if ISR triggered by XRDY...
//	{
//		if(leftRight)
//		{
//			for (i = 13; i>-1; i--){
//				buffer_left[i+1] = buffer_left[i];
//			}
//			buffer_left[0] = (temp + 307*sin(2*3.14*24/480*sample));
//
//			dataout = 0;
//			for (i=0; i<15; i++){
//				dataout = dataout + buffer_left[i] * FIR[i];
//			}
//
//			MCASP->XBUF11 = (int32_t)dataout;  // command to play
//			sample++;
//   		}
//		else {
//			for (i = 13; i>-1; i--){
//				buffer_right[i+1] = buffer_right[i];
//			}
//			buffer_right[0] = (temp + 307*sin(2*3.14*24/480*sample));
//
//			dataout = 0;
//			for (i=0; i<15; i++){
//				dataout = dataout + buffer_right[i] * FIR[i];
//			}
//
//			MCASP->XBUF11 = (int32_t)dataout;  // command to play
//		}
//
//
//		if (sample >= 20){
//			sample = 0;
//		}
//		leftRight ^=1;
//	}
//}



	float b1 = 1;
	float b2 = -1.9;
	float b3 = 1;
	float a1 = 1;
	float a2 = -1.807;
	float a3 = .9025;









	if(CHKBIT(MCASP->SRCTL11, XRDY))    //if ISR triggered by XRDY...
	{
		if(leftRight)
		{
			for (i = 2; i>-1; i--){
			buff_iir_x_r[i+1] = buff_iir_x_r[i];
			buff_iir_y_r[i+1] = buff_iir_y_r[i];
			}
			buff_iir_x_r[0] = (temp + 307*sin(2*3.14*24/480*sample));

			buff_iir_y_r[0] = 0;
			for (i=0; i<3; i++){
				buff_iir_y_r[0] = buff_iir_y_r[0] + buff_iir_x_r[i] *xxx[i];
			}
			for (i=0; i<2; i++){
				buff_iir_y_r[0] = buff_iir_y_r[0] + buff_iir_y_r[i] *yyy[i];
			}
			dataout = buff_iir_y_r[0];

			MCASP->XBUF11 = (int32_t)dataout;  // command to play
			sample++;
   		}
		else {
			for (i = 2; i>-1; i--){
//			buffer_right[i+1] = buffer_right[i];
				buff_iir_x_l[i+1] = buff_iir_x_l[i];
				buff_iir_y_l[i+1] = buff_iir_y_l[i];
			}
			buff_iir_x_l[0] = (temp + 307*sin(2*3.14*24/480*sample));

			buff_iir_y_r[0] = 0;
			for (i=0; i<3; i++){
				buff_iir_y_l[0] = buff_iir_y_l[0] + buff_iir_x_l[i] *xxx[i];
			}
			for (i=0; i<2; i++){
				buff_iir_y_l[0] = buff_iir_y_l[0] + buff_iir_y_l[i] *yyy[i];
			}
			dataout = buff_iir_y_l[0];

			MCASP->XBUF11 = (int32_t)dataout;  // command to play
		}


		if (sample >= 20){
			sample = 0;
		}
		leftRight ^=1;
	}
}


























/*	if(CHKBIT(MCASP->SRCTL11, XRDY))    //if ISR triggered by XRDY...
	{

		if(leftRight)
		{
			dataOut32 = temp + 307*sin(2*3.14*24/480*sample);
            buff_fir_r[sample] = dataOut32;

	      while(i<15)
           	{
           	dataOut32 = buff_fir_r[(sample+i)%15]*FIR[i];
           	i++;
            }
         MCASP->XBUF11 = dataOut32;  // command to play
				sample++;
   		}

		}
		else {
			dataOut32 = temp + 307*sin(2*3.14*24/480*sample);
            buff_fir_l[sample] = dataOut32;

            while(i<15)
            	{
            	dataOut32 = buff_fir_l[(sample+i)%15]*FIR[i];
            	i++;
	            }
	         MCASP->XBUF11 = dataOut32;  // command to play
       		}
	if(sample >= 15)
		{
		sample = 0;
		}
	leftRight ^=1;
}*/


/*	if(CHKBIT(MCASP->SRCTL11, XRDY))    //if ISR triggered by XRDY...
		{

			if(leftRight)
			{
						dataOut32 = temp + 307*sin(2*3.14*24/480*sample);
//			            buff_fir_r[sample] = dataOut32;


		      while(i<15)
			           	{
			           	dataOut32 += buff_fir_r[(sample+i)%15]*FIR[i];
			           	i++;
			            }

			         MCASP->XBUF11 = dataOut32;  // command to play
					sample++;
		       		}

			}
			else {
				dataOut32 = temp + 307*sin(2*3.14*24/480*sample);
//	            buff_fir_l[sample] = dataOut32;


	            while(i<15)
	            	{
	            	dataOut32 += buff_fir_l[(sample+i)%15]*FIR[i];
	            	i++;
		            }

		         MCASP->XBUF11 = dataOut32;  // command to play
	       		}


		if(sample >= 24000)
		{
			sample = 0;
		}
		leftRight ^=1;
	}*/


///////////////////////////////////////////////////////////////////*/

/*
	if(CHKBIT(MCASP->SRCTL11, XRDY))    //if ISR triggered by XRDY...
	{
		if(leftRight)
		{
            dataOut32 = 0.7*temp + 0.3*buffer_local_r[(sample)];
            buffer_local_r[sample] = temp;
			MCASP->XBUF11 = dataOut32;  // command to play
			sample++;
		}
		else {
			dataOut32 = 0.7*temp + 0.3*buffer_local_l[sample];
			buffer_local_l[sample] = temp;
			MCASP->XBUF11 = dataOut32;  // command to play
		}
		if(sample >= 24000)
		{
			sample = 0;
		}
		leftRight ^=1;
	}

*/


///*



//*/
















	//if(sample>=0)
		//sample = 0;
//}

