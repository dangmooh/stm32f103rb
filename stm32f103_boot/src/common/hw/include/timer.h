/*
 * timer.h
 *
 *  Created on: Feb 25, 2025
 *      Author: zvxc3
 */

#ifndef SRC_COMMON_HW_INCLUDE_TIMER_H_
#define SRC_COMMON_HW_INCLUDE_TIMER_H_



#include "hw_def.h"


#ifdef _USE_HW_TIMER

#define TIMER_MAX       HW_TIMER_MAX
#define TIMER_MAX_CH    HW_TIMER_MAX_CH

void timerInit(void);
void timerStop(uint8_t ch);
void timerSetPeriod(uint8_t ch, uint32_t period_data);
void timerAttachInterrupt(uint8_t ch, void (*func)(void));
void timerDetachInterrupt(uint8_t ch);
void timerStart(uint8_t ch);

#endif


#endif /* SRC_COMMON_HW_INCLUDE_TIMER_H_ */
