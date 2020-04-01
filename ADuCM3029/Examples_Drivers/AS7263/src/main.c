/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: AS7263.
 * 				A new sample is read every 1 second and transmitted through the UART (115200 baud).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/April/2020
 * @version     01/April/2020    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "AS7263.h"


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t  myState	 =	 0UL;   /*!<   State that indicates when to perform the next action   */
volatile uint8_t   *myPtr;             	/*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	uint8_t  			myMessage[ TX_BUFF_SIZE ];
	I2C_parameters_t    myAS7263_I2C_parameters;
	AS7263_data_t 		myAS7263_Data;
	AS7263_status_t  	aux;

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */
	SystemInit ();

	conf_CLK  	();
	conf_GPIO 	();
	conf_UART 	();
	conf_Timer0 ();


//	/* I2C definition   */
//	myAS7263_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
//	myAS7263_I2C_parameters.sda         	 =    I2C0_SDA;
//	myAS7263_I2C_parameters.scl         	 =    I2C0_SCL;
//	myAS7263_I2C_parameters.addr        	 =    AS7263_ADDRESS;
//	myAS7263_I2C_parameters.freq        	 =    100000;
//	myAS7263_I2C_parameters.pclkFrequency 	 =	  6400000;
//	myAS7263_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
//	myAS7263_I2C_parameters.sclPort     	 =    pADI_GPIO0;
//
//	/* Configure I2C peripheral */
//	aux  =   AS7263_Init ( myAS7263_I2C_parameters );
//
//	/* Power off the device	 */
//	myAS7263_Data.configuration.als_sd	 =	 ALS_CONF_ALS_SD_SHUTDOWN;
//	aux	 =	 AS7263_SetShutDownMode ( myAS7263_I2C_parameters, myAS7263_Data );
//
//	/* Set sensitivity: low sensitivity ( 1/8x )	 */
//	myAS7263_Data.configuration.als_sens	 =	 ALS_CONF_SENS_LOW_SENSITIVITY;
//	aux	 =	 AS7263_SetSensitivity ( myAS7263_I2C_parameters, myAS7263_Data );
//
//	/* Set digital gain (DG): Double	 */
//	myAS7263_Data.configuration.als_dg	 =	 ALS_CONF_DG_DOUBLE;
//	aux	 =	 AS7263_SetDG ( myAS7263_I2C_parameters, myAS7263_Data );
//
//	/* Set Gain: Double sensitivity	 */
//	myAS7263_Data.configuration.als_gain	 =	 ALS_CONF_GAIN_DOUBLE_SENSITIVITY;
//	aux	 =	 AS7263_SetGain ( myAS7263_I2C_parameters, myAS7263_Data );
//
//	/* Set ALS integration time: Integration time 100ms	 */
//	myAS7263_Data.configuration.als_it	 =	 ALS_CONF_ALS_IT_100MS;
//	aux	 =	 AS7263_SetIntegrationTime ( myAS7263_I2C_parameters, myAS7263_Data );


	/* Enable Timer0	 */
	pADI_TMR0->CTL	|=	 ( 1U << BITP_TMR_CTL_EN );


	while ( 1 )
	{
		/* Low power mode: Flexi Mode	 */
		pADI_PMG0->PWRKEY	 =	 0x4859;
		pADI_PMG0->PWRMOD	&=	~( 0b11 << BITP_PMG_PWRMOD_MODE );
		pADI_PMG0->PWRKEY	 =	 0x0000;

		/* Disable key protection for clock oscillator	 */
		pADI_CLKG0_OSC->KEY	 =	 0xCB14U;

		/* Clocks to all peripherals are gated off	 */
		pADI_CLKG0_CLK->CTL5	|=	 ( 1U << BITP_CLKG_CLK_CTL5_PERCLKOFF );

		/* Block registers	 */
		pADI_CLKG0_OSC->KEY	 =	 0x0000U;

		/* Enter in low power Flexi mode	 */
		__WFI();

		if ( myState != 0UL )
		{
			/* Turn both LEDs on	 */
			pADI_GPIO1->SET	|=	 DS4;
			pADI_GPIO2->SET	|=	 DS3;

//			/* Get the raw light data	 */
//			aux  	 =   AS7263_GetALS_HighResOutputData ( myAS7263_I2C_parameters, &myAS7263_Data );
//
//			/* Get the raw white channel output data	 */
//			aux  	 =   AS7263_GetWhiteChannelOutputData ( myAS7263_I2C_parameters, &myAS7263_Data );
//
//			/* Calculate light data and resolution	 */
//			AS7263_CalculateLuxLevel ( &myAS7263_Data );
//
//
//			/* Transmit data through the UART	 */
//			sprintf ( (char*)myMessage, "White counter: %d | Lux: %0.4f lx\r\n", myAS7263_Data.white_channel_output_data, myAS7263_Data.light_level );
//
//			/* Check that is safe to send data	 */
//			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );
//
//			/* Transmit data back	 */
//			myPtr            =   &myMessage[0];
//			pADI_UART0->TX	 =	 *myPtr;
//
//			/* Transmit Buffer Empty Interrupt: Enabled	 */
//			pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables and turn both LEDs off	 */
			myState	 		 =	 0UL;
			pADI_GPIO1->CLR	|=	 DS4;
			pADI_GPIO2->CLR	|=	 DS3;
		}
	}

	/* It should never reach here	 */
	return 0;
}
