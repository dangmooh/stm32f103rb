/*
 * led.h
 *
 *  Created on: Feb 10, 2025
 *      Author: zvxc3
 */

#ifndef SRC_COMMON_HW_INCLUDE_LED_H_
#define SRC_COMMON_HW_INCLUDE_LED_H_


#include "hw_def.h" // hw 관련된 헤더들은 hw 정의가 있는 hw_def를 포함해야한다.


#ifdef _USE_HW_LED //LED를 사용한다고 할때만 허용 : common을 모든 곳에서 공통으로 사용하기 위해서

#define LED_MAX_CH          HW_LED_MAX_CH // led를 몇개 사용할 것인지 hw_def에서 정의한다.

bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);


#endif

#endif /* SRC_COMMON_HW_INCLUDE_LED_H_ */
