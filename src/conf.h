/*
 * conf.h
 *
 *  Created on: 11 jul 2015
 *      Author: andreas
 */
#include <avr/io.h>
#include "type.h"

#ifndef CONF_H_
#define CONF_H_

#define DEBUG_MODE 1

#define DISP_INTENSITY 4 /* Display intensity [0-15] */


/*************************************************
 * PIN CONFIGURATION
 *************************************************/
#define SELECT_BTN_CFG B,3
#define RESET_BTN_CFG  D,0
#define DISP_SCK_CFG   B,7
#define DISP_DATA_CFG  B,5
#define DISP_CS_CFG    B,4


#endif /* CONF_H_ */
