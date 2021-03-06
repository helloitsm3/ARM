/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: SSD1306. Every 1 seconds, a new
 *              sample is performed and transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/November/2018
 * @version     3/November/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v4.12
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#if defined (WORK_FROM_HOME)
#include "D:/Workspace/ARM/Drivers/SSD1306/SSD1306_Graphics.h"
#include "D:/Workspace/ARM/Drivers/SSD1306/SSD1306.h" 
#else
#include "D:/vsProjects/ARM/Drivers/SSD1306/SSD1306_Graphics.h"
#include "D:/vsProjects/ARM/Drivers/SSD1306/SSD1306.h" 
#endif


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint32_t myADCDoneFlag;                  /*!<   It indicates when a new ADC conversion is ready        */
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART             */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */




/**@brief Function for application main entry.
 */
int main(void)
{
  I2C_parameters_t         mySSD1306_I2C_parameters;
  SSD1306_status_t         aux;
  SSD1306_vector_data_t    mySSD1306_Data;

  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  //conf_TIMER0 ();

  

  /* I2C definition   */
  mySSD1306_I2C_parameters.TWIinstance =    NRF_TWI0;
  mySSD1306_I2C_parameters.SDA         =    TWI0_SDA;
  mySSD1306_I2C_parameters.SCL         =    TWI0_SCL;
  mySSD1306_I2C_parameters.ADDR        =    SSD1306_ADDRESS_SA0_GND;
  mySSD1306_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  mySSD1306_I2C_parameters.SDAport     =    NRF_P0;
  mySSD1306_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   SSD1306_Init                 ( mySSD1306_I2C_parameters );

  /* Turn off the display */
  aux  =   SSD1306_SetDisplay           ( mySSD1306_I2C_parameters, SET_DISPLAY_ON_OFF_DISPLAY_OFF );
  
  /* Set MUX ratio: 64MUX  */
  aux  =   SSD1306_SetMultiplexRatio    ( mySSD1306_I2C_parameters, SET_MULTIPLEX_RATIO_64MUX );

  /* Set display offset: 0   */
  aux  =   SSD1306_SetDisplayOffset     ( mySSD1306_I2C_parameters, 0U );

  /* Set display start line: 0   */
  aux  =   SSD1306_SetDisplayStartLine  ( mySSD1306_I2C_parameters, 0U );

  /* Set segment re-map: Column address 0 is mapped to SEG0  */
  aux  =   SSD1306_SetSegmentReMap      ( mySSD1306_I2C_parameters, SET_SEGMENT_RE_MAP_COL_0_SEG0 );
  
  /* Set COM output scan direction: Normal mode. Scan from COM0 to COM[N �1]  */
  aux  =   SSD1306_SetCOM_OutputScanDirection ( mySSD1306_I2C_parameters, SET_SCAN_DIR_NORMAL_MODE );

  /* Set COM pins hardware configuration: Alternative COM configuration, Disable COM left/right re-map  */
  aux  =   SSD1306_SetCOM_PinsHardwareConfiguration ( mySSD1306_I2C_parameters, COM_PIN_CONFIGURATION_SEQUENCTIAL_COM_PIN, COM_LEFT_RIGHT_REMAP_DISABLED );

  /* Set constranst: 0x7F ( 127, middle point )  */
  mySSD1306_Data.contrast  =   0x7F;
  aux  =   SSD1306_SetContrastControl   ( mySSD1306_I2C_parameters, mySSD1306_Data );

  /* Disable entire display on   */
  aux  =   SSD1306_SetEntireDisplay     ( mySSD1306_I2C_parameters, ENTIRE_DISPLAY_ON_RESUME_TO_RAM_CONTENT );

  /* Set Display: Normal display   */
  aux  =   SSD1306_SetNormalInverseDisplay  ( mySSD1306_I2C_parameters, SET_DISPLAY_NORMAL_DISPLAY );

  /* Set Osc Frequency: Oscillator frequency = 0x08, Clock divide ratio = 0 ( Divide ratio= A[3:0] + 1 = 0 + 1 = 1 )   */
  aux  =   SSD1306_SetDisplayClockDivideRatio_OscFreq ( mySSD1306_I2C_parameters, 8U, 0U );

  /* Enable charge pump regulator: Enabled   */
  aux  =   SSD1306_SetChargePumpSetting ( mySSD1306_I2C_parameters, CHARGE_PUMP_ENABLE_CHARGE_PUMP_DURING_DISPLAY_ON );

  /* Turn on the display */
  aux  =   SSD1306_SetDisplay           ( mySSD1306_I2C_parameters, SET_DISPLAY_ON_OFF_DISPLAY_ON );
  
  

//  /* Set Display: Normal display   */
//  aux  =   SSD1306_SetNormalInverseDisplay  ( mySSD1306_I2C_parameters, SET_DISPLAY_INVERSE_DISPLAY );


  myState  =   0;                             // Reset the variable
  NRF_TIMER0->TASKS_START  =   1;             // Start Timer0

  //NRF_POWER->SYSTEMOFF = 1;
  NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
  while( 1 )
  {
    /* Enter System ON sleep mode   */
    __WFE();
    /* Make sure any pending events are cleared */
    __SEV();
    __WFE();



    if ( myState == 1 )
    {
      NRF_P0->OUTCLR  |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on

//      /* Get the day of the week */
//      aux  =   SSD1306_GetDayOfTheWeek ( mySSD1306_I2C_parameters, &mySSD1306_Data );

      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "%02x/%02x/%02x %d %02x:%02x.%02x\r\n", mySSD1306_Data.BCDDate, mySSD1306_Data.BCDMonth, mySSD1306_Data.BCDYear, mySSD1306_Data.DayOfTheWeek,
//                                                                          (uint8_t)( ( mySSD1306_Data.BCDTime & 0xFF0000 ) >> 16U ), (uint8_t)( ( mySSD1306_Data.BCDTime & 0x00FF00 ) >> 8U ),
//                                                                          (uint8_t)( mySSD1306_Data.BCDTime & 0x0000FF ) );

      NRF_UART0->TASKS_STOPRX  =   1UL;
      NRF_UART0->TASKS_STOPTX  =   1UL;
      myPtr                    =   &myMessage[0];

      NRF_UART0->TASKS_STARTTX =   1UL;
      NRF_UART0->TXD           =   *myPtr;

      
      /* Reset the variables   */
      myState          =   0;
      NRF_P0->OUTSET  |=   ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
    }
    //__NOP();
  }
}


/**
 * @}
 */
