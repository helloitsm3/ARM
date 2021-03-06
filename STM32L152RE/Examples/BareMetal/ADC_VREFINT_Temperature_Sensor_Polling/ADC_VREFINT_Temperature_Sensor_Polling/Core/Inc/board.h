/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): NUCLEO-L152RE.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     4/August/2018   UART5 pinout added
 * 				9/March/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   NUCLEO-L152RE LEDs PINOUT
 */
typedef enum
{
    LED_1         =   5              /*!<  NUCLEO-L152RE LED1: 		PA_5  		*/
} nucleol152re_led_pinout_t;


/**
  * @brief   NUCLEO-L152RE BUTTONs PINOUT
  */
typedef enum
{
	BUTTON_1      =   13             /*!<  NUCLEO-L152RE USER BUTTON: 	PC_13	*/
} nucleol152re_button_pinout_t;


/**
  * @brief   NUCLEO-L152RE UARTs PINOUT
  */
typedef enum
{
	UART5_RX      =   2,             /*!<  NUCLEO-L152RE BASIC UART5 RX: 	PD_2	*/
	UART5_TX      =   12             /*!<  NUCLEO-L152RE BASIC UART5 TX: 	PC_12	*/
} nucleol152re_uart_pinout_t;


/**
  * @brief   NUCLEO-L152RE USARTs PINOUT
  */
typedef enum
{
	UART2_RX      =   3,             /*!<  NUCLEO-L152RE BASIC USART2 RX: 	PA_3	*/
	UART2_TX      =   2              /*!<  NUCLEO-L152RE BASIC USART2 TX: 	PA_2	*/
} nucleol152re_usart_pinout_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
