/*
 * ap.c
 *
 *  Created on: Feb 9, 2025
 *      Author: zvxc3
 */


#include "ap.h"





void apInit(void)
{

}

// gcc 계열에서 printf 함수를 사용하려면 syscallback 추가하면 된다.

void apMain(void) //main.c를 최소화하고 ap에서 모든 상위 작업을 진행한다.
{
  uint32_t pre_time;

  pre_time = millis();
  while(1)
  {
    if (millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);

      //logPrintf("logPrintf test %d\n", (int)millis());
    }
  }
}




/* reset count led blink example
   * uint32_t pre_time;
  uint32_t led_blink_time = 500;
  uint32_t pre_baud;

  pre_baud = uartGetBaud(_DEF_UART1);
  pre_time = millis();
  while(1)
  {
    if(millis() - pre_time >= led_blink_time)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);

    }
    if(uartGetBaud(_DEF_UART1) != pre_baud)
    {
      pre_baud = uartGetBaud(_DEF_UART1);
      uartPrintf(_DEF_UART1, "ChangedBaud : %d \n", uartGetBaud(_DEF_UART1));
    }

  }*/

  /*uint32_t pre_time;
  uint8_t rx_buf[128]; // usb와 uart의 전송할 데이터 버퍼
  uint32_t rx_len;

  pre_time = millis();
  while(1)
  {
    if(millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);

      uartPrintf(_DEF_UART2, "UART1 \n", millis());
    }
    if (uartAbailable(_DEF_UART2) > 0)
    {
      uint8_t rx_data;

      rx_data = uartRead(_DEF_UART2);
      uartPrintf(_DEF_UART2, "Uart1 Rx %c %X\n", rx_data, rx_data);
    }
    if (uartGetBaud(_DEF_UART1) != uartGetBaud(_DEF_UART2))
    {
      uartOpen(_DEF_UART2, uartGetBaud(_DEF_UART1));
    }

    // USB -> UART
    rx_len = uartAbailable(_DEF_UART1);
    if (rx_len > 128) // 버퍼가 꽉찬경우
    {
      rx_len = 128;
    }
    if (rx_len > 0)
    {
      for (int i=0; i<rx_len; i++)
      {
        rx_buf[i] = uartRead(_DEF_UART1);
      }
      uartWrite(_DEF_UART2, rx_buf, rx_len);
    }

    // UART -> USB
        rx_len = uartAbailable(_DEF_UART2);
        if (rx_len > 128) // 버퍼가 꽉찬경우
        {
          rx_len = 128;
        }
        if (rx_len > 0)
        {
          for (int i=0; i<rx_len; i++)
          {
            rx_buf[i] = uartRead(_DEF_UART2);
          }
          uartWrite(_DEF_UART1, rx_buf, rx_len);
        }
  }*/
