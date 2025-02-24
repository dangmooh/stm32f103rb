/*
 * button.c
 *
 *  Created on: Feb 25, 2025
 *      Author: zvxc3
 */


#include "button.h"

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t      pin;
  GPIO_PinState on_state;
  GPIO_PinState off_state;
} button_tbl_t;


button_tbl_t button_tbl[BUTTON_MAX_CH] =
    {
        {GPIOC, GPIO_PIN_13, GPIO_PIN_RESET, GPIO_PIN_SET}
    };

void buttonInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();


  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // led 공통 설정 요소
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  for (int i =0; i<BUTTON_MAX_CH; i++)
  {
    GPIO_InitStruct.Pin = button_tbl[i].pin;
    HAL_GPIO_Init(button_tbl[i].port, &GPIO_InitStruct);
  }

}

bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;

  if(HAL_GPIO_ReadPin(button_tbl[ch].port, button_tbl[ch].pin) == GPIO_PIN_RESET)
  {
    ret = true;
  }

  return ret;
}
