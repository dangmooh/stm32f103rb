/*
 * bsp.h
 *
 *  Created on: Feb 9, 2025
 *      Author: zvxc3
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_


#include "def.h"

#define _USE_LOG_PRINT   1

#if _USE_LOG_PRINT
#define logPrintf(fmt, ...)    printf(fmt, ##__VA_ARGS__)// 가변인자 매크로
#else
#define logPrintf(fmt, ...)
#endif



#include "stm32f1xx_hal.h"



void bspInit(void);

//공통으로 사용하는 함수 정의
void delay(uint32_t ms);
uint32_t millis(void);

void Error_Handler(void);


#endif /* SRC_BSP_BSP_H_ */
