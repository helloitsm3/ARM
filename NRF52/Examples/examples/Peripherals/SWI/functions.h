/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "variables.h"

#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef __cplusplus
extern "C" {
#endif


/* FUNCTION PROTOTYPES */
void conf_LFCLK   ( void );
void conf_GPIO    ( void );
void conf_RTC0    ( void );
void conf_SWI     ( void );


#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */