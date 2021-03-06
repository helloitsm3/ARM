/**
 * @brief       PCF85063.h
 * @details     Tiny Real-Time Clock/calendar.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  PCF85063_ADDRESS     =   0b1010001                                  /*!<   I2C slave address byte                       */
} PCF85063_address_t;



/**
  * @brief   REGISTERS ORGANIZATION
  */
typedef enum
{
  /* CONTROL AND STATUS REGISTERS  */
  PCF85063_CONTROL_1  =   0x00,                                       /*!<  Control and status register 1                 */
  PCF85063_CONTROL_2  =   0x01,                                       /*!<  Control and status register 2                 */
  PCF85063_OFFSET     =   0x02,                                       /*!<  Offset register                               */
  PCF85063_RAM_BYTE   =   0x03,                                       /*!<  RAM byte register                             */

  /* TIME AND DATE REGISTERS  */
  PCF85063_SECONDS    =   0x04,                                       /*!<  Seconds register                              */
  PCF85063_MINUTES    =   0x05,                                       /*!<  Minutes register                              */
  PCF85063_HOURS      =   0x06,                                       /*!<  Hours register                                */
  PCF85063_DAYS       =   0x07,                                       /*!<  Days register                                 */
  PCF85063_WEEKDAYS   =   0x08,                                       /*!<  Weekdays register                             */
  PCF85063_MONTHS     =   0x09,                                       /*!<  Months register                               */
  PCF85063_YEARS      =   0x0A                                        /*!<  Years register                                */
} PCF85063_registers_organization_t;



/**
  * @brief   Register Control_1
  */
/* EXT_TEST <7>: EXTERNAL CLOCK TEST MODE
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_EXT_TEST_MASK                     =   ( 1U << 7U ),     /*!<  EXT_TEST mask                                   */
    CONTROL_1_EXT_TEST_NORMAL_MODE              =   ( 0U << 7U ),     /*!<  EXT_TEST: normal mode               [ Default ] */
    CONTROL_1_EXT_TEST_EXTERNAL_CLOCK_TEST_MODE =   ( 1U << 7U )      /*!<  EXT_TEST: external clock test mode              */
} PCF85063_control_1_ext_test_t;



/* STOP <5>: STOP BIT
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_STOP_MASK                         =   ( 1U << 5U ),     /*!<  STOP mask                                       */
    CONTROL_1_STOP_RTC_CLOCK_RUNS               =   ( 0U << 5U ),     /*!<  STOP: RTC clock runs                [ Default ] */
    CONTROL_1_STOP_RTC_CLOCK_STOPPED            =   ( 1U << 5U )      /*!<  STOP: RTC clock is stopped                      */
} PCF85063_control_1_stop_t;



/* SR <4>: SOFTWARE RESET 
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_SR_MASK                           =   ( 1U << 4U ),     /*!<  SR mask                                         */
    CONTROL_1_SR_NO_SOFTWARE_RESET              =   ( 0U << 4U ),     /*!<  SR: no software reset               [ Default ] */
    CONTROL_1_SR_SOFTWARE_RESET                 =   ( 1U << 4U )      /*!<  SR: initiate software reset                     */
} PCF85063_control_1_sr_t;



/* CIE <2>: CORRECTION INTERRUPT ENABLE 
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_CIE_MASK                              =   ( 1U << 2U ), /*!<  CIE mask                                                      */
    CONTROL_1_CIE_NO_CORRECTION_INTERRUPT_GENERATED =   ( 0U << 2U ), /*!<  CIE: no correction interrupt generated [ Default ]            */
    CONTROL_1_CIE_INTERRUPT_PULSES_GENERATED        =   ( 1U << 2U )  /*!<  CIE: interrupt pulses are generated at every correction cycle */
} PCF85063_control_1_cie_t;



/* 12_24 <1>: SOFTWARE RESET 
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_12_24_MASK                        =   ( 1U << 1U ),     /*!<  12_24 mask                                      */
    CONTROL_1_12_24_24_HOUR_MODE                =   ( 0U << 1U ),     /*!<  12_24: 24 hour mode is selected     [ Default ] */
    CONTROL_1_12_24_12_HOUR_MODE                =   ( 1U << 1U )      /*!<  12_24: 12 hour mode is selected                 */
} PCF85063_control_1_12_24_t;



/* CAP_SEL <0>: INTERNAL OSCILLATOR CAPACITOR SELECTION 
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_CAP_SEL_MASK                      =   ( 1U << 0U ),     /*!<  CAP_SEL mask                                    */
    CONTROL_1_CAP_SEL_7_PF                      =   ( 0U << 0U ),     /*!<  CAP_SEL: 7 pF                       [ Default ] */
    CONTROL_1_CAP_SEL_12_5_PF                   =   ( 1U << 0U )      /*!<  CAP_SEL: 12.5 pF                                */
} PCF85063_control_1_cap_sel_t;



/**
  * @brief   Register Control_2
  */
/* MI <5>: MINUTE INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_MI_MASK                           =   ( 1U << 5U ),     /*!<  MI mask                                         */
    CONTROL_2_MI_MINUTE_INTERRUPT_DISABLED      =   ( 0U << 5U ),     /*!<  Minute interrupt disabled           [ Default ] */
    CONTROL_2_MI_MINUTE_INTERRUPT_ENABLED       =   ( 1U << 5U )      /*!<  Minute interrupt enabled                        */
} PCF85063_control_2_mi_t;



/* HMI <4>: HALF MINUTE INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_HMI_MASK                            =   ( 1U << 4U ),   /*!<  HMI mask                                        */
    CONTROL_2_HMI_HALF_MINUTE_INTERRUPT_DISABLED  =   ( 0U << 4U ),   /*!<  Half Minute interrupt disabled      [ Default ] */
    CONTROL_2_HMI_HALF_MINUTE_INTERRUPT_ENABLED   =   ( 1U << 4U )    /*!<  Half Minute interrupt enabled                   */
} PCF85063_control_2_hmi_t;



/* TF <3>: TIMER FLAG
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_TF_MASK                           =   ( 1U << 3U ),     /*!<  TF mask                                         */
    CONTROL_2_TF_TIMER_INTERRUPT_NOT_GENERATED  =   ( 0U << 3U ),     /*!<  No Timer interrupt generated        [ Default ] */
    CONTROL_2_TF_TIMER_INTERRUPT_GENERATED      =   ( 1U << 3U )      /*!<  Timer interrupt generated                       */
} PCF85063_control_2_tf_t;



/* COF <2:0>: CLKOUT CONTROL
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_COF_MASK                          =   ( 0b111 << 0U ),  /*!<  COF mask                                        */
    CONTROL_2_COF_CLKOUT_32768_HZ               =   ( 0b000 << 0U ),  /*!<  CLKOUT: 32768 Hz                    [ Default ] */
    CONTROL_2_COF_CLKOUT_16384_HZ               =   ( 0b001 << 0U ),  /*!<  CLKOUT: 16384 Hz                                */
    CONTROL_2_COF_CLKOUT_8192_HZ                =   ( 0b010 << 0U ),  /*!<  CLKOUT: 8192  Hz                                */
    CONTROL_2_COF_CLKOUT_4096_HZ                =   ( 0b011 << 0U ),  /*!<  CLKOUT: 4096  Hz                                */
    CONTROL_2_COF_CLKOUT_2048_HZ                =   ( 0b100 << 0U ),  /*!<  CLKOUT: 2048  Hz                                */
    CONTROL_2_COF_CLKOUT_1024_HZ                =   ( 0b101 << 0U ),  /*!<  CLKOUT: 1024  Hz                                */
    CONTROL_2_COF_CLKOUT_1_HZ                   =   ( 0b110 << 0U ),  /*!<  CLKOUT: 1     Hz                                */
    CONTROL_2_COF_CLKOUT_LOW                    =   ( 0b111 << 0U )   /*!<  CLKOUT: LOW                                     */
} PCF85063_control_2_cof_t;



/**
  * @brief   Register Offset
  */
/* MODE <7>: OFFSET MODE
 *    NOTE: N/A.
 */
typedef enum
{
    OFFSET_MODE_MASK                            =   ( 1U << 7U ),     /*!<  MODE mask                                                   */
    OFFSET_MODE_NORMAL_MODE                     =   ( 0U << 7U ),     /*!<  Normal mode: offset is made once every two hours[ Default ] */
    OFFSET_MODE_COURSE_MODE                     =   ( 1U << 7U )      /*!<  Course mode: offset is made every 4 minutes                 */
} PCF85063_offset_mode_t;



/**
  * @brief   Register RAM_byte
  */
/* B <7:0>: RAM CONTENT
 *    NOTE: N/A.
 */
typedef enum
{
    RAM_BYTE_B_MASK                             =   0xFF              /*!<  RAM_byte mask                                     */
} PCF85063_ram_byte_b_t;



/**
  * @brief   Register Seconds
  */
/* OS <7>: OSCILLATOR STOP
 *    NOTE: N/A.
 */
typedef enum
{
    SECONDS_OS_MASK                           =   ( 1U << 7U ),     /*!<  OS mask                                                                                         */
    SECONDS_OS_CLOCK_INTEGRITY_IS_GUARANTEED  =   ( 0U << 7U ),     /*!<  Clock integrity is guaranteed                                                                   */
    SECONDS_OS_CLOCK_INTEGRITY_NOT_GUARANTEED =   ( 1U << 7U )      /*!<  Clock integrity is not guaranteed, oscillator has stopped or has been interrupted  [ Default ]  */
} PCF85063_seconds_os_t;



/* SECONDS, TEN'S PLACE <6:4>: ACTUAL SECONDS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    SECONDS_SECONDS_TEN_PLACE_MASK            =   ( 0b111 << 4U )   /*!<  SECONDS TEN'S PLACE mask                              */
} PCF85063_seconds_ten_place_t;



/* SECONDS, UNIT PLACE <3:0>: ACTUAL SECONDS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    SECONDS_SECONDS_UNIT_PLACE_MASK           =   ( 0b1111 << 0U )  /*!<  SECONDS UNIT PLACE mask                               */
} PCF85063_seconds_unit_place_t;



/**
  * @brief   Register Minutes
  */
/* MINUTES, TEN'S PLACE <6:4>: ACTUAL MINUTES, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    MINUTES_MINUTES_TEN_PLACE_MASK            =   ( 0b111 << 4U )   /*!<  MINUTES TEN'S PLACE mask                              */
} PCF85063_minutes_ten_place_t;



/* MINUTES, UNIT PLACE <3:0>: ACTUAL MINUTES, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    MINUTES_MINUTES_UNIT_PLACE_MASK           =   ( 0b1111 << 0U )  /*!<  MINUTES UNIT PLACE mask                               */
} PCF85063_minutes_unit_place_t;



/**
  * @brief   Register HOURS
  */
/* AMPM <5>: AM/PM INDICATOR
 *    NOTE: ONLY FOR 12-HOUR MODE.
 */
typedef enum
{
    HOURS_AMPM_MASK                           =   ( 1U << 5U ),     /*!<  AMPM mask                                             */
    HOURS_AMPM_AM                             =   ( 0U << 5U ),     /*!<  AMPM: AM mode                                         */
    HOURS_AMPM_PM                             =   ( 1U << 5U )      /*!<  AMPM: PM mode                                         */
} PCF85063_hours_ampm_t;



/* HOURS, TEN'S PLACE <4>: ACTUAL HOURS, TEN'S PLACE
 *    NOTE: ONLY FOR 12-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
    HOURS_12_HOUR_MODE_TEN_PLACE_MASK         =   ( 1U << 4U )      /*!<  Hours TEN'S PLACE mask                                */
} PCF85063_12_hour_mode_ten_place_t;



/* HOURS, TEN'S PLACE <5:4>: ACTUAL HOURS, TEN'S PLACE
 *    NOTE: ONLY FOR 24-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
    HOURS_24_HOUR_MODE_TEN_PLACE_MASK         =   ( 0b11 << 4U )    /*!<  Hours TEN'S PLACE mask                                */
} PCF85063_24_hour_mode_ten_place_t;



/* HOURS, UNIT PLACE <3:0>: ACTUAL HOURS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    HOURS_HOURS_UNIT_PLACE_MASK               =   ( 0b1111 << 0U )  /*!<  HOURS UNIT PLACE mask                                 */
} PCF85063_hours_unit_place_t;



/**
  * @brief   Register Days
  */
/* DAYS, TEN'S PLACE <5:4>: ACTUAL DAYS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    DAYS_DAYS_TEN_PLACE_MASK                  =   ( 0b11 << 4U )    /*!<  DAYS TEN'S PLACE mask                                 */
} PCF85063_days_ten_place_t;



/* DAYS, UNIT PLACE <3:0>: ACTUAL DAYS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    DAYS_DAYS_UNIT_PLACE_MASK                 =   ( 0b1111 << 0U )  /*!<  DAYS UNIT PLACE mask                                  */
} PCF85063_days_unit_place_t;



/**
  * @brief   Register Weekdays
  */
/* WEEKDAYS <2:0>: ACTUAL WEEKDAY
 *    NOTE: N/A.
 */
typedef enum
{
    WEEKDAYS_WEEKDAYS_MASK                    =   ( 0b111 << 0U ),  /*!<  WEEKDAYS mask                                          */
    WEEKDAYS_WEEKDAYS_SUNDAY                  =   ( 0b000 << 0U ),  /*!<  WEEKDAYS Sunday                                        */
    WEEKDAYS_WEEKDAYS_MONDAY                  =   ( 0b001 << 0U ),  /*!<  WEEKDAYS Monday                                        */
    WEEKDAYS_WEEKDAYS_TUESDAY                 =   ( 0b010 << 0U ),  /*!<  WEEKDAYS Tuesday                                       */
    WEEKDAYS_WEEKDAYS_WEDNESDAY               =   ( 0b011 << 0U ),  /*!<  WEEKDAYS Wednesday                                     */
    WEEKDAYS_WEEKDAYS_THURSDAY                =   ( 0b100 << 0U ),  /*!<  WEEKDAYS Thursday                                      */
    WEEKDAYS_WEEKDAYS_FRIDAY                  =   ( 0b101 << 0U ),  /*!<  WEEKDAYS Friday                                        */
    WEEKDAYS_WEEKDAYS_SATURDAY                =   ( 0b111 << 0U )   /*!<  WEEKDAYS Saturday                          [ Default ] */
} PCF85063_weekdays_weekdays_t;



/**
  * @brief   Register Months
  */
/* MONTHS <4:0>: ACTUAL MONTH
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
   MONTHS_MONTHS_MASK                        =   ( 0b11111 << 0U ),  /*!<  MONTHS mask                                            */
   MONTHS_MONTHS_JANUARY                     =   ( 0b00001 << 0U ),  /*!<  MONTHS January                             [ Default ] */
   MONTHS_MONTHS_FEBRUARY                    =   ( 0b00010 << 0U ),  /*!<  MONTHS February                                        */
   MONTHS_MONTHS_MARCH                       =   ( 0b00011 << 0U ),  /*!<  MONTHS March                                           */
   MONTHS_MONTHS_APRIL                       =   ( 0b00100 << 0U ),  /*!<  MONTHS April                                           */
   MONTHS_MONTHS_MAY                         =   ( 0b00101 << 0U ),  /*!<  MONTHS May                                             */
   MONTHS_MONTHS_JUNE                        =   ( 0b00110 << 0U ),  /*!<  MONTHS June                                            */
   MONTHS_MONTHS_JULY                        =   ( 0b00111 << 0U ),  /*!<  MONTHS July                                            */
   MONTHS_MONTHS_AUGUST                      =   ( 0b01000 << 0U ),  /*!<  MONTHS August                                          */
   MONTHS_MONTHS_SEPTEMBER                   =   ( 0b01001 << 0U ),  /*!<  MONTHS September                                       */
   MONTHS_MONTHS_OCTOBER                     =   ( 0b10000 << 0U ),  /*!<  MONTHS October                                         */
   MONTHS_MONTHS_NOVEMBER                    =   ( 0b10001 << 0U ),  /*!<  MONTHS November                                        */
   MONTHS_MONTHS_DECEMBER                    =   ( 0b10010 << 0U )   /*!<  MONTHS December                                        */
} PCF85063_months_months_t;



/**
  * @brief   Register Years
  */
/* YEARS, TEN'S PLACE <7:4>: ACTUAL YEARS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    YEARS_YEARS_TEN_PLACE_MASK                =   ( 0b1111 << 4U )   /*!<  YEARS TEN'S PLACE mask                                 */
} PCF85063_years_ten_place_t;



/* YEARS, UNIT PLACE <3:0>: ACTUAL YEARS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    YEARS_YEARS_UNIT_PLACE_MASK               =   ( 0b1111 << 0U )   /*!<  YEARS UNIT PLACE mask                                  */
} PCF85063_years_unit_place_t;





#ifndef PCF85063_VECTOR_STRUCT_H
#define PCF85063_VECTOR_STRUCT_H
typedef struct
{
    PCF85063_control_1_12_24_t    Time12H_24HMode;                    /*!<  Time mode: 12-hour or 24-hour mode                    */
    PCF85063_hours_ampm_t         TimeAM_PM_Mode;                     /*!<  AM/PM mode ( only for 12-hour mode )                  */

    uint32_t                      BCDtime;                            /*!<  Time ( HHMMSS ) in BCD format                         */
    uint8_t                       BCDday;                             /*!<  Day number in BCD format                              */
    PCF85063_weekdays_weekdays_t  weekday;                            /*!<  Weekday                                               */
    PCF85063_months_months_t      BCDmonth;                           /*!<  Month  in BCD format                                  */
    uint8_t                       BCDyear;                            /*!<  Year in BCD format                                    */

    int8_t                        ramByte;                            /*!<  RAM byte                                              */
    PCF85063_seconds_os_t         os;                                 /*!<  Oscillator flag                                       */
} PCF85063_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCF85063_SUCCESS     =       0,
    PCF85063_FAILURE     =       1
} PCF85063_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
PCF85063_status_t  PCF85063_Init                              ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the external clock test mode.
  */
PCF85063_status_t  PCF85063_SetTestMode                       ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_ext_test_t myEXT_TEST                      );

/** It sets the RTC clock mode.
  */
PCF85063_status_t  PCF85063_SetRTCMode                        ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_stop_t mySTOP                              );

/** It performs a software reset.
  */
PCF85063_status_t  PCF85063_SoftwareReset                     ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the correction interrupt mode.
  */
PCF85063_status_t  PCF85063_SetCorrectionInterruptMode        ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_cie_t myCIE                                );

/** It sets 12 or 24 hour mode.
  */
PCF85063_status_t  PCF85063_Set12_24_HourMode                 ( I2C_parameters_t myI2Cparameters, PCF85063_data_t my12_24                                       );

/** It sets the internal oscillator capacitor.
  */
PCF85063_status_t  PCF85063_SetInternalOscillatorCapacitor    ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_cap_sel_t myCAP_SEL                        );

/** It enables/disables minute/half minute interrupt.
  */
PCF85063_status_t  PCF85063_SetMinuteInterrupts               ( I2C_parameters_t myI2Cparameters, PCF85063_control_2_mi_t myMI, PCF85063_control_2_hmi_t myHMI  );

/** It gets the status of the timer flag.
  */
PCF85063_status_t  PCF85063_GetTimerFlag                      ( I2C_parameters_t myI2Cparameters, PCF85063_control_2_tf_t* myTF                                 );

/** It resets the status of the timer flag.
  */
PCF85063_status_t  PCF85063_ClearTimerFlag                    ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the clock output frequency.
  */
PCF85063_status_t  PCF85063_SetClockOutputFrequency           ( I2C_parameters_t myI2Cparameters, PCF85063_control_2_cof_t myCOF                                );

/** It sets the offset.
  */
PCF85063_status_t  PCF85063_SetOffset                         ( I2C_parameters_t myI2Cparameters, PCF85063_offset_mode_t myMODE, int8_t myOFFSET                );

/** It writes into the RAM byte register.
  */
PCF85063_status_t  PCF85063_WriteByteRAM                      ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myData                                        );

/** It reads the RAM byte register.
  */
PCF85063_status_t  PCF85063_ReadByteRAM                       ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myData                                       );

/** It checks oscillator clock integrity flag.
  */
PCF85063_status_t  PCF85063_CheckOscillatorClockIntegrityFlag ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myOS                                         );

/** It clears oscillator clock integrity flag.
  */
PCF85063_status_t  PCF85063_ClearOscillatorClockIntegrityFlag ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the AM/PM indicator ( only for 12-hour mode ).
  */
PCF85063_status_t  PCF85063_SetAM_PM_Indicator                ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myAM_PM_Indicator                             );

/** It gets the AM/PM indicator ( only for 12-hour mode ).
  */
PCF85063_status_t  PCF85063_GetAM_PM_Indicator                ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myAM_PM_Indicator                            );

/** It gets the day ( BCD format ).
  */
PCF85063_status_t  PCF85063_GetDay                            ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualDay                                  );

/** It sets the day ( BCD format ).
  */
PCF85063_status_t  PCF85063_SetDay                            ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewDay                                      );

/** It gets the weekday.
  */
PCF85063_status_t  PCF85063_GetWeekday                        ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualWeekday                              );

/** It sets the weekday.
  */
PCF85063_status_t  PCF85063_SetWeekday                        ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewWeekday                                  );

/** It gets the month ( BCD format ).
  */
PCF85063_status_t  PCF85063_GetMonth                          ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualMonth                                );

/** It sets the month ( BCD format ).
  */
PCF85063_status_t  PCF85063_SetMonth                          ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewMonth                                    );

/** It gets the time ( BCD format ).
  */
PCF85063_status_t  PCF85063_GetTime                           ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualTime                                 );

/** It sets the time ( BCD format ).
  */
PCF85063_status_t  PCF85063_SetTime                           ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewTime                                     );

/** It gets the year ( BCD format ).
  */
PCF85063_status_t  PCF85063_GetYear                           ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualYear                                 );

/** It sets the year ( BCD format ).
  */
PCF85063_status_t  PCF85063_SetYear                           ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewYear                                     );
