/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */


#include "functions.h"

/**
 * @brief       void Conf_CLK  ( void )
 * @details     It configures the CLK and the MCO.
 *
 * 				- HSI ON
 * 				- SYSCLK = HSI/1 = 16MHz
 * 				- Rest CLK = SYSCLK = 16MHz
 * 				- MSI OFF
 * 				- MCO ENABLED
 * 					-- MCO = SYSCLK/1 = 16MHz
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version     3/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void Conf_CLK  ( void )
{
	// Enable HSI
	RCC->CR		|=	  RCC_CR_HSION;
	// Wait until HSI is stable
	while ( ( RCC->CR & RCC_CR_HSIRDY ) != RCC_CR_HSIRDY );					// [TODO] Dangerous!!! Insert a delay, the uC may get stuck
																			// if something goes wrong otherwise.
	// HSI -> SYSCLK
	RCC->CFGR	|=	 RCC_CFGR_SW_HSI;
	// Wait until it is stable
	while ( ( RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSI );				// [TODO] Dangerous!!! Insert a delay, the uC may get stuck
																			// if something goes wrong otherwise.
	// Stop MSI
	RCC->CR		&=	 ~RCC_CR_MSION;
	// Wait until MSI is off
	while ( ( RCC->CR & RCC_CR_MSIRDY ) == RCC_CR_MSIRDY );					// [TODO] Dangerous!!! Insert a delay, the uC may get stuck
																			// if something goes wrong otherwise.

	RCC->CFGR	&=	 0xF8FFFFFF;											// MCO output disabled, no clock on MCO
	RCC->CFGR	|=	 ( RCC_CFGR_MCOPRE_DIV1 | RCC_CFGR_MCOSEL_SYSCLK );		// MCO = SYSCLK/1 | MCO ENABLED
}



/**
 * @brief       void Conf_SYSTICK  ( uint32_t )
 * @details     It disables the SysTick.
 *
 * @param[in]    myticks:	Value of the SYSCLK..
 *
 * @param[out]   NaN.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void Conf_SYSTICK  ( uint32_t myticks )
{
	SysTick->CTRL	&=	 ~SysTick_CTRL_ENABLE_Msk;										// SysTick DISABLED


//	SysTick->LOAD	 =	 (uint32_t)(myticks - 1UL);										// Load the value
//	SysTick->VAL	 =	 0UL;															// Reset current Counter value
//
//	// Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value
//	NVIC_SetPriorityGrouping	( NVIC_PRIORITYGROUP_4 );
//	NVIC_SetPriority 			( SysTick_IRQn, ( 1UL << __NVIC_PRIO_BITS ) - 1UL );	// Set Priority for Systick Interrupt
//	NVIC_EnableIRQ				( SysTick_IRQn );										// Enable interrupt
//
//	SysTick->CTRL  	 = 	( SysTick_CTRL_CLKSOURCE_Msk |
//	                   	  SysTick_CTRL_TICKINT_Msk   |
//						  SysTick_CTRL_ENABLE_Msk );                    				// Enable SysTick IRQ and SysTick Timer

}



/**
 * @brief       void Conf_GPIO  ( void )
 * @details     It configures GPIOs.
 *
 * 				- LED1:		PA_5
 * 				- MCO:  	PA_8
 * 				- UART5:
 * 					-- TX:	PC_12
 * 					-- RX:	PD_2
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version		4/January/2018   UART5 pinout added
 * 				3/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void Conf_GPIO  ( void )
{
	// GPIOA, GPIOC and GPIOD Peripheral clock enable
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIODEN );


    // Configure LED1
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;					// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 						// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5_Msk;			// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;					// No pull-up, pull-down

    // Configure MCO
    GPIOA->MODER	|=	 GPIO_MODER_MODER8_1;					// Alternate function mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_8;						// Output push-pull
    GPIOA->OSPEEDR	|=	 GPIO_OSPEEDER_OSPEEDR8_0;				// Medium speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR8_Msk;					// No pull-up, pull-down
    GPIOA->AFR[1]	&=	~GPIO_AFRH_AFSEL8;						// Mask Alternate function AFIO0 on PA8
    GPIOA->AFR[1]	 =	 ( 0b0000 << GPIO_AFRH_AFSEL8_Pos );	// MCO: AF0 on PA8

    // Configure UART5 pinout
    // TX pin
    GPIOC->MODER	|=	 GPIO_MODER_MODER12_1;					// Alternate function mode
    GPIOC->OTYPER	&=	~GPIO_OTYPER_OT_12;						// Output push-pull
    GPIOC->OSPEEDR	|=	 GPIO_OSPEEDER_OSPEEDR12_0;				// Medium speed
    GPIOC->PUPDR	&=	~GPIO_PUPDR_PUPDR12_Msk;				// No pull-up, pull-down
    GPIOC->AFR[1]	&=	~GPIO_AFRH_AFSEL12;						// Mask Alternate function AFIO8 on PC_12
    GPIOC->AFR[1]	 =	 ( 0b1000 << GPIO_AFRH_AFSEL12_Pos );	// UART5_TX: AF8 on PC_12

    // RX pin
    GPIOD->MODER	|=	 GPIO_MODER_MODER2_1;					// Alternate function mode
    GPIOD->OTYPER	&=	~GPIO_OTYPER_OT_2;						// Output push-pull
    GPIOD->OSPEEDR	|=	 GPIO_OSPEEDER_OSPEEDR2_0;				// Medium speed
    GPIOD->PUPDR	&=	~GPIO_PUPDR_PUPDR2_Msk;					// No pull-up, pull-down
    GPIOD->AFR[0]	&=	~GPIO_AFRL_AFSEL2;						// Mask Alternate function AFIO8 on PD_2
    GPIOD->AFR[0]	 =	 ( 0b1000 << GPIO_AFRL_AFSEL2_Pos );	// UART5_RX: AF8 on PD_2
}


/**
 * @brief       void Conf_UART  ( uint32_t myCK, uint32_t myBaudRate )
 * @details     It configures the UARTs.
 *
 * 				- UART5 BaudRate = 115200, 8-bit, 1-bit STOP, NO Parity
 * 					-- Increase the tolerance ( oversampling by 16 ): OVER8 = 0 	[ p705 Reference Manual ]
 * 					-- Tx/Rx_baud = f_CK / ( 8�( 2 - OVER8 )�( USARTDIV ) ) 		[ p708 Reference Manual ]
 * 						--- f_CK = 16MHz
 * 						--- USARTDIV = 16MHz / ( 115200�( 8�( 2 - 0 ) ) ) ~ 8.6806
 * 							---- DIV_Mantissa = 8
 * 							---- DIV_Fraction = 16�0.6806 = 10.8896 ~ 11
 * 								----- USART_BRR = DIV_Mantissa, DIV_Fraction = 0x08B
 *
 * 				- Tx/Rx Interrupts ENABLED
 *
 * @param[in]    myCK: 			UART Clock ( f_CK ).
 * @param[in]    myBaudRate: 	UART baud rate.
 *
 * @param[out]   NaN.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version     4/January/2018   Interrupts enabled
 * 				3/January/2018   The ORIGIN
 * @pre         OVER8 is calculated automatically.
 * @warning     NaN
 */
void Conf_UART  ( uint32_t myCK, uint32_t myBaudRate )
{
	float 		myCalculatedData	=	 0;
	uint32_t	myOVER8	 			=	 0;

	// UART5 Peripheral clock enable
	RCC->APB1ENR	|=	 RCC_APB1ENR_UART5EN;

	UART5->CR1	&=	~( USART_CR1_OVER8 | USART_CR1_UE | USART_CR1_M | 			// Oversampling by 16,  USART disabled, 1 Start bit, 8 Data bits n Stop bit
					   USART_CR1_PCE | USART_CR1_TE | USART_CR1_RE );			// Parity control disabled, Transmitter is disabled, Receiver is disabled

	UART5->CR2	&=	~( USART_CR2_STOP_1 | USART_CR2_STOP_0 | USART_CR2_CLKEN |	// 1 Stop bit, CK pin disabled,
					   USART_CR2_CPOL | USART_CR2_CPHA );						// CPOL = 0, CPHA = 0

	// Calculate Mantissa
	// Check if oversamplig by 16 is correct
	myCalculatedData	=	 myCK / ( myBaudRate * 8.0 * ( 2.0 - myOVER8 ) );

	if ( myCalculatedData < 1 )
	{
	// if not, change it to oversampling by 8
		myOVER8	 			=	 1;
		myCalculatedData	=	 myCK / ( myBaudRate * 8.0 * ( 2.0 - myOVER8 ) );
	}

	// Update oversampling
	if ( myOVER8 == 0 )
		myOVER8	 =	 16.0;
	else
		myOVER8	 =	 8.0;


	// BaudRate: Update Mantissa
	UART5->BRR	 =	 ( ( ( uint32_t )( myCalculatedData ) << USART_BRR_DIV_MANTISSA_Pos ) & USART_BRR_DIV_MANTISSA_Msk );

	// Calculate Fraction
	myCalculatedData	 =	 myCalculatedData - ( uint32_t )myCalculatedData;
	myCalculatedData	*=	 myOVER8;
	myCalculatedData	 =	 _ROUND32U ( myCalculatedData );

	// BaudRate: Update Fraction
	UART5->BRR	|=	 ( ( ( uint32_t )( myCalculatedData ) << USART_BRR_DIV_FRACTION_Pos ) & USART_BRR_DIV_FRACTION_Msk );


	// Enable Interrupt
	NVIC_SetPriority ( UART5_IRQn, 1 ); 									// Set Priority to 1
	NVIC_EnableIRQ   ( UART5_IRQn );  										// Enable UART5_IRQn interrupt in NVIC


	// Activate interrupts, and UART
	UART5->SR	&=	~( USART_SR_TXE | USART_SR_TC | USART_SR_RXNE );		// Clear flags
	UART5->CR1	|=	 ( USART_CR1_UE | USART_CR1_RE | USART_CR1_TCIE | 		// USART enabled, Receiver enabled, Transmission complete interrupt enabled
					   USART_CR1_RXNEIE );									// RXNE interrupt enable

	while ( ( UART5->SR & USART_SR_TC ) != USART_SR_TC );					// Wait until Idle frame is sent
																			// [TODO] Dangerous!!! Insert a delay, the uC may get stuck here otherwise.
	UART5->SR	&=	~( USART_SR_TC | USART_SR_RXNE );						// Clear flags

	UART5->CR1	|=	 ( USART_CR1_TCIE | USART_CR1_RXNEIE );					// Transmission complete interrupt enabled, RXNE interrupt enable
}
