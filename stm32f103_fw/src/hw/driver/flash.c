/*
 * flash.c
 *
 *  Created on: Feb 20, 2025
 *      Author: zvxc3
 */


#include "flash.h"



#define FLASH_SECTOR_MAX          128

typedef struct
{
  uint32_t addr;
  uint16_t length;
} flash_tbl_t;


static flash_tbl_t flash_tbl[FLASH_SECTOR_MAX];

static bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length);



bool flashInit(void)
{
  for (int i=0; i<FLASH_SECTOR_MAX; i++)
  {
    flash_tbl[i].addr = 0x8000000 + i*1024;
    flash_tbl[i].length = 1024;
  }

  return true;
}

bool flashErase(uint32_t addr, uint32_t length) // sector나 page 단위로 지우고
{
  bool ret = false;

  HAL_StatusTypeDef status;
  FLASH_EraseInitTypeDef init;
  uint32_t  page_error;


  status =  HAL_FLASHEx_Erase(&init, &page_error);

  return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length) // byte나 ward 단위로 쓴다.
{

}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length)
{

}

// 지우고자 하는 주소 영역을 줬을 때 포함되어 있는 섹터 영역을 찾기 위해서 처음부터 돌면서 그 섹터가 주소 영역에 포함되어 있는지 return 하는 함수
bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length) // 확인하고자 하는 sector 번호 및 지워야하는 addr, length
{
  bool ret = false;

  uint32_t sector_start;  // flash > sector : 검사하는 sector의 시작 및 end 주소 이것이 지워야하는 flash 영역에 포함되어 있는지 확인
  uint32_t sector_end;    // flash < sector : flash 영역의 시작 및 end 주소가 sector 영역에 포함되어 있는지 확인
  uint32_t flash_start;   // 지워야하는 flash 영역의 시작 주소
  uint32_t flash_end;

  sector_start = flash_tbl[sector_num].addr;
  sector_end   = flash_tbl[sector_num].addr + flash_tbl[sector_num].length - 1;
  flash_start  = addr;
  flaseh_start = addr + length - 1;

  if (sector_start >= flash_start && sector_start <= flash_end)
  {
    ret = true;
  }

  if (sector_end >= flash_start && sector_end <= flash_end)
  {
    ret = true;
  }

  if(flash_start >= sector_start && flash_start <= sector_end)
  {
    ret = true;
  }

  if(flash_end >= sector_start && flash_end <= sector_end)
  {
    ret = true;
  }

  return ret;
}
