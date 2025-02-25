/*
 * timer.c
 *
 *  Created on: Feb 25, 2025
 *      Author: zvxc3
 */



#include "timer.h"



typedef struct
{
  TIM_HandleTypeDef hTIM;
  TIM_OC_InitTypeDef sConfig[4];
  uint32_t freq;
  void (*p_func[4])(void);
} hwtimer_t;


typedef struct
{
  uint8_t number;
  uint8_t index;
  uint32_t active_channel;
} hwtimer_index_t;


static hwtimer_index_t hwtimer_index[TIMER_MAX_CH] = {
    { _DEF_TIMER1, _DEF_TIMER_CH1, HAL_TIM_ACTIVE_CHANNEL_1},
    { _DEF_TIMER1, _DEF_TIMER_CH2, HAL_TIM_ACTIVE_CHANNEL_2},
    { _DEF_TIMER1, _DEF_TIMER_CH3, HAL_TIM_ACTIVE_CHANNEL_3},
    { _DEF_TIMER1, _DEF_TIMER_CH4, HAL_TIM_ACTIVE_CHANNEL_4},
};


static hwtimer_t timer_tbl[TIMER_MAX];

void timerInit(void)
{
  timer_tbl[_DEF_TIMER1].freq = 1000;
  timer_tbl[_DEF_TIMER1].hTIM.Instance = TIM1;
  timer_tbl[_DEF_TIMER1].hTIM.Init.Prescaler = (uint32_t)((SystemCoreClock / 1) / timer_tbl[_DEF_TIMER1].freq ) - 1; // 1Khz
  timer_tbl[_DEF_TIMER1].hTIM.Init.ClockDivision = 0;
  timer_tbl[_DEF_TIMER1].hTIM.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer_tbl[_DEF_TIMER1].hTIM.Init.RepetitionCounter = 0;
  timer_tbl[_DEF_TIMER1].p_func[0] = NULL;
  timer_tbl[_DEF_TIMER1].p_func[1] = NULL;
  timer_tbl[_DEF_TIMER1].p_func[2] = NULL;
  timer_tbl[_DEF_TIMER1].p_func[3] = NULL;
}

void timerStop(uint8_t ch)
{
  hwtimer_t *p_timer;

  if( ch >= TIMER_MAX_CH ) return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  HAL_TIM_Base_DeInit(&p_timer->hTIM);
}

void timerSetPeriod(uint8_t ch, uint32_t period_data)
{
  hwtimer_t *p_timer;
  uint32_t period;


  if( ch >= TIMER_MAX_CH ) return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  if (p_timer->freq == 1000)
  {
    period = period_data/1000;

    if (period == 0)
    {
      period = 1;
    }
  }
  p_timer->hTIM.Init.Period = period - 1;
}

void timerAttachInterrupt(uint8_t ch, void (*func)(void))
{
  hwtimer_t *p_timer;

  if( ch >= TIMER_MAX_CH ) return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  timerStop(ch);
  p_timer->p_func[hwtimer_index[ch].index] = func;
}

void timerDetachInterrupt(uint8_t ch)
{
  hwtimer_t *p_timer;

  if( ch >= TIMER_MAX_CH ) return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];

  timerStop(ch);
  p_timer->p_func[hwtimer_index[ch].index] = NULL;
}

void timerStart(uint8_t ch)
{
  hwtimer_t *p_timer;
  uint32_t timer_sub_ch = 0;

  if( ch >= TIMER_MAX_CH ) return;

  p_timer = &timer_tbl[hwtimer_index[ch].number];


  switch(hwtimer_index[ch].index)
  {
  case _DEF_TIMER1:
  timer_sub_ch = TIM_CHANNEL_1;
  break;

  case _DEF_TIMER2:
  timer_sub_ch = TIM_CHANNEL_2;
  break;

  case _DEF_TIMER3:
  timer_sub_ch = TIM_CHANNEL_3;
  break;

  case _DEF_TIMER4:
  timer_sub_ch = TIM_CHANNEL_4;
  break;
  }

  HAL_TIM_OC_Init(&p_timer->hTIM);
  HAL_TIM_OC_ConfigChannel(&p_timer->hTIM, &p_timer->sConfig[hwtimer_index[ch].index], timer_sub_ch);
  HAL_TIM_OC_Start_IT(&p_timer->hTIM, timer_sub_ch);
}

void timerCallback(TIM_HandleTypeDef *htim)
{
uint8_t i;
uint32_t index;
hwtimer_t *p_timer;

for (i=0; i<TIMER_MAX_CH; i++)
{
p_timer = &timer_tbl[hwtimer_index[i].number];
index = hwtimer_index[i].index;

if (htim->Channel == hwtimer_index[i].active_channel)
{
if( p_timer->p_func[index] != NULL )
{
(*p_timer->p_func[index])();
}
}
}
}





void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
timerCallback(htim);
}

void TIM1_IRQHandler(void)
{
HAL_TIM_IRQHandler(&timer_tbl[_DEF_TIMER1].hTIM);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
if (htim->Instance == timer_tbl[_DEF_TIMER1].hTIM.Instance )
{
__HAL_RCC_TIM1_CLK_ENABLE();

HAL_NVIC_SetPriority(TIM1_UP_IRQn, 15, 0);
HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
if (htim->Instance == timer_tbl[_DEF_TIMER1].hTIM.Instance)
{
HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
}
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
if (htim->Instance == timer_tbl[_DEF_TIMER1].hTIM.Instance)
{
__HAL_RCC_TIM1_CLK_ENABLE();

HAL_NVIC_SetPriority(TIM1_UP_IRQn, 15, 0);
HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
}
}
