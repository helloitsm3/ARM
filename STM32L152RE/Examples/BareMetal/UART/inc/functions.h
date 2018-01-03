/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version     3/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "stm32l1xx.h"
#include "variables.h"


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* FUNCTION PROTOTYPES */
void Conf_CLK  	   ( void );
void Conf_GPIO 	   ( void );
void Conf_SYSTICK  ( uint32_t myticks );
void Conf_TIMERS   ( uint32_t myCLK );
void Conf_UART	   ( uint32_t myCK, uint32_t myBaudRate );


#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
