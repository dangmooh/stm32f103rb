/*
 * hw_ef.h
 *
 *  Created on: Feb 9, 2025
 *      Author: zvxc3
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


//하드웨어 모듈들이 공통으로 사용하는 헤더
#include "def.h"
#include "bsp.h"


#define _USE_HW_RTC
#define _USE_HW_RESET
#define _USE_HW_FLASH

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       1

#define _USE_HW_LED //LED를 사용할 것이고
#define      HW_LED_MAX_CH          1 // led는 1개 사용한다

#define _USE_HW_SW_TIMER
#define      HW_SW_TIMER_MAX_CH      1

#endif /* SRC_HW_HW_DEF_H_ */
