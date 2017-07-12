/**
 * @brief       main.c
 * @details     [todo] xxx
 *
 *              This firmware is just an example about how to use the RTCs on the nrf51422.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/July/2017
 * @version     12/July/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


int main( void )
{
    uint32_t page_number          =  NRF_FICR->CODESIZE - 1;
    uint32_t *p_page_base_address =  ( uint32_t * ) ( page_number * NRF_FICR->CODEPAGESIZE );
    uint32_t myValue              =  0x23232323;


    conf_GPIO   ();
    conf_LFCLK  ();
    conf_RTC0   ();


    NRF_RTC0->TASKS_START = 1;    // Start RTC0


    while( 1 )
    {
        // NRF_POWER->SYSTEMOFF    = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();


		if ( writeNVMC  ==  YES )
        {
            NRF_GPIO->OUTCLR         =   ( 1UL << LED1 );

            if ( *p_page_base_address != myValue )
            {
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );

                NRF_NVMC->ERASEPAGE  = ( uint32_t )p_page_base_address;

                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );

                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );

                *p_page_base_address =   myValue;
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );
            }
            else
            {
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );

                *p_page_base_address =   myValue;
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );
            }

            writeNVMC                =   NO;
            NRF_GPIO->OUTSET         =   ( 1UL << LED1 );
        }
    }
}
