/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "board.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


/**@brief Subroutine prototypes.
 */
extern void USART2_IRQHandler (void);


/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint8_t  myRX;
extern volatile uint8_t  *myPtr;



#endif /* INTERRUPTS_H_ */
