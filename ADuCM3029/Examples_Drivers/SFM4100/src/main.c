/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: SFM4100.
 * 				A new sample is read every 1 second and transmitted through the UART (115200 baud)
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "SFM4100.h"


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
	I2C_parameters_t    mySFM4100_I2C_parameters;
	SFM4100_data_t 		mySFM4100_Data;
	SFM4100_status_t  	aux;

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


	/* I2C definition   */
	mySFM4100_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	mySFM4100_I2C_parameters.sda         	 =    I2C0_SDA;
	mySFM4100_I2C_parameters.scl         	 =    I2C0_SCL;
	mySFM4100_I2C_parameters.addr        	 =    SFM4100_ADDRESS_AIR;
	mySFM4100_I2C_parameters.freq        	 =    100000;
	mySFM4100_I2C_parameters.pclkFrequency 	 =	  6400000;
	mySFM4100_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	mySFM4100_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral  */
	aux  =   SFM4100_Init  ( mySFM4100_I2C_parameters );

	/* Perform a softreset   */
	aux  =   SFM4100_SoftReset  ( mySFM4100_I2C_parameters );
	for ( uint32_t ii = 0UL; ii < 0x2323; ii++ );


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

			/* Trigger a new conversion  */
			aux  =   SFM4100_TriggerNewFlow ( mySFM4100_I2C_parameters );

			/* Get the result  */
			aux  =   SFM4100_GetFlow ( mySFM4100_I2C_parameters, &mySFM4100_Data );

			/* Transmit result through the UART  */
			sprintf ( (char*)myMessage, "Flow = %d sccm | Current CRC: %x | Calculated CRC: %x\r\n", (int16_t)mySFM4100_Data.conversion.flow_sccm, mySFM4100_Data.crc.current_crc, mySFM4100_Data.crc.calculated_crc );


			/* Check that is safe to send data	 */
			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );

			/* Transmit data back	 */
			myPtr            =   &myMessage[0];
			pADI_UART0->TX	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables and turn both LEDs off	 */
			myState	 		 =	 0UL;
			pADI_GPIO1->CLR	|=	 DS4;
			pADI_GPIO2->CLR	|=	 DS3;
		}
	}

	/* It should never reach here	 */
	return 0;
}

