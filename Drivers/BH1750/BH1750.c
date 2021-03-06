/**
 * @brief       BH1750.h
 * @details     Digital 16-bit Serial Output Type Ambient Light Sensor IC.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/August/2017
 * @version     2/August/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "BH1750.h"


/**
 * @brief       BH1750_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of BH1750_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        18/October/2017
 * @version     18/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint32_t  BH1750_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   BH1750_SUCCESS;
    else
        return   BH1750_FAILURE;
}



/**
 * @brief       BH1750_ResetDataRegister   ( I2C_parameters_t )
 * @details     Reseting the data register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   Status of BH1750_ResetDataRegister.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     Reset command is not acceptable in Power Down mode.
 */
uint32_t  BH1750_ResetDataRegister   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t     cmd[]               =   { BH1750_RESET };
    uint32_t    aux                 =    0;


    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_STOP_BIT );


    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}


/**
 * @brief       BH1750_PowerDown   ( I2C_parameters_t )
 * @details     BH1750 in low power mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   Status of BH1750_PowerDown.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint32_t  BH1750_PowerDown   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t     cmd[]               =   { BH1750_POWER_DOWN };
    uint32_t    aux                 =    0;


    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_STOP_BIT );


    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}


/**
 * @brief       uint32_t  BH1750_PowerOn   ( I2C_parameters_t )
 * @details     BH1750 is on and waiting for measurement command.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   Status of BH1750_PowerOn.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint32_t  BH1750_PowerOn   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t     cmd[]               =   { BH1750_POWER_ON };
    uint32_t    aux                 =    0;


    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_STOP_BIT );


    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}


 /**
 * @brief       uint32_t  BH1750_TriggerMeasurement   ( I2C_parameters_t , uint32_t )
 * @details     Trigger a new temperature measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    MODE:              ONE-SHOT or CONTINUOUSLY measurement ( Normal Mode or Mode2 ).
 *
 * @param[out]   Status of BH1750_TriggerMeasurement.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     The measuring time depends on the chosen resolution ( MODE ). The user
 *              must take this into account.
 */
uint32_t  BH1750_TriggerMeasurement    ( I2C_parameters_t myI2Cparameters, uint32_t MODE )
{
    uint8_t     cmd[]               =   { MODE };
    uint32_t    aux                 =    0;

    BH1750_Mode                     =    MODE;


    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_STOP_BIT );


    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}


 /**
 * @brief       uint32_t  BH1750_NewSensitivity     ( I2C_parameters_t , uint8_t )
 * @details     It configures the new sensitivity of the sensor. The sensitivity depends on which
 *              resolution mode is used:
 *
 *                  H-reslution mode  : Illuminance per 1 count ( lx / count ) = 1 / 1.2 *( 69 / X )
 *                  H-reslution mode2 : Illuminance per 1 count ( lx / count ) = 1 / 1.2 *( 69 / X ) / 2
 *
 *              So, by the default:
 *
 *                  H-reslution mode  : Sensitivity = 1 / 1.2 *( 69 / 69 )      ~  0.83
 *                  H-reslution mode2 : Sensitivity = 1 / 1.2 *( 69 / 69 ) / 2  ~  1.67
 *
 *
 *              Example ( H-reslution mode ):
 *
 *                  Minimum Sensitivity = 1 / 1.2 *( 69 / 31 )      ~  0.37
 *                  Maximum Sensitivity = 1 / 1.2 *( 69 / 254 )     ~  3.07
 *
 *
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    newSensitivity:    New sensitivity value.
 *
 * @param[out]   Status of BH1750_NewSensitivity.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     newSensitivity can ONLY be from 31 to 254.
 */
uint32_t  BH1750_NewSensitivity    ( I2C_parameters_t myI2Cparameters, uint8_t newSensitivity )
{
    uint8_t     cmd[]               =   { 0x40, 0x60 };                 // 0x40 ( MT High byte ), 0x60 ( MT Low byte )
    uint32_t    aux                 =    0;


    if ( ( newSensitivity > 30 ) && ( newSensitivity < 255 ) )
    {
        cmd[0]  |=    ( ( newSensitivity & 0xE0 ) >> 5 );
        cmd[1]  |=    ( newSensitivity & 0x1F );

        aux = i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );
    }
    else
        aux  =   BH1750_FAILURE;



    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}



/**
 * @brief       uint32_t  BH1750_ReadRawData   ( I2C_parameters_t , uint32_t* )
 * @details     Read a new raw temperature measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRawData:         Variable to store the raw data.
 *
 * @param[out]   Status of BH1750_ReadRawData.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     BH1750_TriggerMeasurement MUST be call before.
 */
uint32_t  BH1750_ReadRawData    ( I2C_parameters_t myI2Cparameters, uint8_t* myRawData )
{
    uint32_t    aux                 =    0;


    aux = i2c_read ( myI2Cparameters, &myRawData[0], 2 );


    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}


/**
 * @brief       BH1750_ReadLux   ( I2C_parameters_t , float* )
 * @details     It turns the raw data into a Lux data.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myLux:             Variable to store the Lux.
 *
 * @param[out]   Status of BH1750_ReadLux.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/August/2017
 * @version     18/October/2017    Adapted to the new I2C driver.
 *              5/August/2017      The ORIGIN
 * @pre         NaN
 * @warning     BH1750_TriggerMeasurement MUST be call before.
 */
uint32_t  BH1750_ReadLux    ( I2C_parameters_t myI2Cparameters, float* myLux )
{
    uint32_t    aux                 =    0;
    uint8_t     myRawData[]         =    { 0, 0};


    aux = BH1750_ReadRawData ( myI2Cparameters, &myRawData[0] );


    if ( ( BH1750_Mode == BH1750_CONTINUOUSLY_H_RESOLUTION_MODE ) || ( BH1750_Mode == BH1750_CONTINUOUSLY_L_RESOLUTION_MODE )  || ( BH1750_Mode == BH1750_ONE_TIME_H_RESOLUTION_MODE ) ||
         ( BH1750_Mode == BH1750_ONE_TIME_L_RESOLUTION_MODE ) )
    {
        *myLux   =   ( myRawData[0] << 8 ) | myRawData[1];
        *myLux   =   ( uint16_t )( *myLux / 1.2 );
    }
    else
    {
        *myLux   =   ( ( myRawData[0] << 8 ) | myRawData[1] ) >> 1;
        *myLux   =   ( uint16_t )( *myLux / 1.2 );

        if ( ( myRawData[1] & 0x01 ) == 0x01 )
          *myLux  +=   0.5;
    }



    if ( aux == I2C_SUCCESS )
       return   BH1750_SUCCESS;
    else
       return   BH1750_FAILURE;
}
