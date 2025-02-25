/*
 * swtimer.c
 *
 *  Created on: Feb 25, 2025
 *      Author: zvxc3
 */



#include "swtimer.h"




typedef struct
{
  uint8_t Timer_En;       // 타이머 인에이블 신호
  uint8_t Timer_Mode;     // 타이머 모드
  uint32_t Timer_Ctn;     // 현재의 타이머 값
  uint32_t Timer_Init;    // 타이머 초기화될때의 카운트 값
  void (*TmrFnct)(void *);// 만료될때 실행될 함수
  void *TmrFnctArg;       // 함수로 전달할 인수들
} swtimer_t;



static volatile uint32_t sw_timer_counter = 0;
static volatile uint16_t sw_timer_handle_index = 0;
static swtimer_t swtimer_tbl[SW_TIMER_MAX_CH];



bool swtimerInit(void)
{
  bool ret = true;
  uint8_t i;

  static uint8_t excute = 0;

  if (excute == 1) // 이미 한번 실행했다면 정지
  {
    ret = false;
  }

  for (i=0; i<SW_TIMER_MAX_CH; i++)
  {
    swtimer_tbl[i].Timer_En = OFF;
    swtimer_tbl[i].Timer_Ctn = 0;
    swtimer_tbl[i].Timer_Init = 0;
    swtimer_tbl[i].TmrFnct = NULL;
  }

  excute = 1;

  return ret;
}


void swtimerISR(void)
{
  uint8_t i;

  sw_timer_counter++;

  for (i=0; i<SW_TIMER_MAX_CH && i<sw_timer_handle_index; i++) // 타이머 갯수 만큼
  {
    if (swtimer_tbl[i].Timer_En == ON)                         // 타이머가 활성화 되었다면
    {
      swtimer_tbl[i].Timer_Ctn--;                                 // 타이머 값 감소

      if (swtimer_tbl[i].Timer_Ctn == 0)                       // 타이머 오버플로어
      {
        if (swtimer_tbl[i].Timer_Mode == ONE_TIME)             // 한번만 실행하는 거라면
        {
          swtimer_tbl[i].Timer_En = OFF;                       // 타이머 OFF
        }

        swtimer_tbl[i].Timer_Ctn = swtimer_tbl[i].Timer_Init;  // 타이머 초기화

        (*swtimer_tbl[i].TmrFnct)(swtimer_tbl[i].TmrFnctArg);  // 함수 실행
      }
    }
  }
}

void swtimerSet(uint8_t ch, uint32_t TmrData, uint8_t TmrMode, void (*Fnct)(void *), void *arg)
{
  swtimer_tbl[ch].Timer_Mode = TmrMode;   // 모드 설정
  swtimer_tbl[ch].TmrFnct    = Fnct;      // 실행할 함수
  swtimer_tbl[ch].TmrFnctArg = arg;       // 매개변수
  swtimer_tbl[ch].Timer_Ctn  = TmrData;
  swtimer_tbl[ch].Timer_Init = TmrData;
}

void swtimerStart(uint8_t ch)
{
  if (ch < SW_TIMER_MAX_CH)
  {
    swtimer_tbl[ch].Timer_Ctn = swtimer_tbl[ch].Timer_Init;
    swtimer_tbl[ch].Timer_En  = ON;
  }
}


void swtimerStop(uint8_t ch)
{
  if (ch < SW_TIMER_MAX_CH)
  {
    swtimer_tbl[ch].Timer_En = OFF;
  }
}


void swtimerReset(uint8_t ch)
{
  swtimer_tbl[ch].Timer_En  = OFF;
  swtimer_tbl[ch].Timer_Ctn = swtimer_tbl[ch].Timer_Init;
}


swtimer_handle_t swtimerGetHandle(void)
{
  swtimer_handle_t chIndex = sw_timer_handle_index;

  sw_timer_handle_index++;

  return chIndex;
}

uint32_t swtimerGetCounter(void)
{
  return sw_timer_counter;
}
