/*
 * reset.c
 *
 *  Created on: Feb 12, 2025
 *      Author: zvxc3
 */



#include "reset.h"
#include "rtc.h"


static uint32_t reset_count = 0;



bool resetInit(void)
{
  bool ret = true;


  // reset 핀이 눌렸다면
  if(RCC->CSR & (1<<26))
  {
    rtcBackupRegWrite(1, rtcBackupRegRead(1) + 1); // 자기 자신을 1 증가한다.
    delay(500); // 500ms 안에 누르면 rtcBackupReg가 증가한다.
    reset_count = rtcBackupRegRead(1);
  }

  rtcBackupRegWrite(1, 0); // 다음에도 0부터 시작을 위해 초기화, backupreg는 1부터 시작

  return ret;
}

uint32_t resetGetCount(void)
{
  return reset_count;
}
