/*
 * swtimer.h
 *
 *  Created on: Feb 25, 2025
 *      Author: zvxc3
 */

#ifndef SRC_COMMON_HW_INCLUDE_SWTIMER_H_
#define SRC_COMMON_HW_INCLUDE_SWTIMER_H_



#include "hw_def.h"


#ifdef _USE_HW_SW_TIMER

#define SW_TIMER_MAX_CH      HW_SW_TIMER_MAX_CH


#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#ifndef NULL
#define NULL 0
#endif

#define ONE_TIME 1
#define LOOP_TIME 2


typedef int16_t swtimer_handle_t;



bool swtimerInit(void);
void swtimerSet(uint8_t ch, uint32_t TmrData, uint8_t TmrMode, void (*Fnct)(void *), void *arg);
void swtimerStart(uint8_t ch);
void swtimerStop(uint8_t ch);
void swtimerReset(uint8_t ch);
void swtimerISR(void);


int16_t swtimerGetHandle(void);
uint32_t swtimerGetCounter(void);


#endif


#endif /* SRC_COMMON_HW_INCLUDE_SWTIMER_H_ */
