/*
 * hw.c
 *
 *  Created on: Feb 9, 2025
 *      Author: zvxc3
 */


#include "hw.h"





void hwInit(void)
{
  bspInit();
  rtcInit();

  resetInit();
  ledInit();
  uartInit();
  flashInit();
}
