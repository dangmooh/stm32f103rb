/*
 * ap.c
 *
 *  Created on: Feb 9, 2025
 *      Author: zvxc3
 */


#include "ap.h"





void apInit(void)
{
  uartOpen(_DEF_UART1, 57600);
  uartOpen(_DEF_UART2, 57600);
}

// gcc 계열에서 printf 함수를 사용하려면 syscallback 추가하면 된다.

void apMain(void) //main.c를 최소화하고 ap에서 모든 상위 작업을 진행한다.
{
  uint32_t pre_time;
  uint16_t target = 500;
  pre_time = millis();
  while(1)
  {
    if (millis() - pre_time >= target)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }
    if (buttonGetPressed(_DEF_BUTTON1) == true)
    {
      target = 200;
    }

    /*if (millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);

      //logPrintf("logPrintf test %d\n", (int)millis());
    }

    if (uartAvailable(_DEF_UART1) >0)
    {
      uint8_t rx_data;

      rx_data = uartRead(_DEF_UART1);

      if (rx_data == '1')
      {
        uint8_t buf[32];

        logPrintf("Read... \n");

        flashRead(0x8000000 + (120*1024), buf, 32); // 시작 주소 0x8000000 + (120*1024) 에서 32byte를 읽어온다.

        for (int i=0; i<32; i++)
        {
          logPrintf("0x%X : 0x%X\n", 0x8000000 + (120*1024) + i, buf[i]); // 32byte를 화면에 출력한다.
        }
      }

      if (rx_data == '2')
      {
        logPrintf("Erase... \n");

        if (flashErase(0x8000000 + (120*1024), 32) == true) // 시작 주소 0x8000000 + (120*1024) 에서 32byte를 지운다.
        {
          logPrintf("Erase OK \n");
        }
        else
        {
          logPrintf("Erase Fail \n");
        }
      }

      if (rx_data == '3')
      {
        uint8_t buf[32];

        for (int i=0; i<32; i++)
        {
          buf[i] = i;
        }

        logPrintf("Write... \n");

        if (flashWrite(0x8000000 + (120*1024), buf, 32) == true) // 시작 주소 0x8000000 + (120*1024) 에서 32byte를 쓴다.
        {
          logPrintf("Write OK \n");
        }
        else
        {
          logPrintf("Write Fail \n");
        }
      }

    }*/
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
