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

  int16_t start_sector_num  = -1;               // 시작 sector를 찾기 위해서
  uint32_t sector_count     = 0;                // NbPage에 대응되는 값

  for (int i=0; i<FLASH_SECTOR_MAX; i++)
  {
    if (flashInSector(i, addr, length) == true) // 지워야하는 sector인지 확인
    {
      if (start_sector_num < 0)
      {
        start_sector_num = i;
      }
      sector_count++;
    }
  }

  if (sector_count > 0)
  {
    HAL_FLASH_Unlock();

    init.TypeErase  = FLASH_TYPEERASE_PAGES;
    init.Banks      = FLASH_BANK_1;
    init.PageAddress= flash_tbl[start_sector_num].addr;
    init.NbPages    = sector_count;

    status =  HAL_FLASHEx_Erase(&init, &page_error);
    if (status == HAL_OK)
    {
      ret = true;
    }

    HAL_FLASH_Lock();
  }


  return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length) // byte나 ward 단위로 쓴다.
{
  bool ret = true;
  HAL_StatusTypeDef status;

  if (addr%2 != 0) // aline된 주소만 받는걸로 간단하게 처리
  {
    return false;
  }

  HAL_FLASH_Unlock();

  for (int i=0; i <length; i+=2)
  {
    uint16_t data;

    data  = p_data[i+0] << 0;   // 첫 번째 byte를 쓰고
    data |= p_data[i+1] << 8;   // 두 번째 byte를 그 다음에 쓴다. 16bit data를 만든다.

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr + i, (uint64_t)data); // 최소 단위 16bit로 쓸 수 있다. 주소를 aline 해줘야 한다.

    if (status != HAL_OK)
    {
      ret = false;
    }
  }

  HAL_FLASH_Lock();

  return ret;
}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;

  uint8_t *p_byte = (uint8_t *)addr;

  for (int i=0; i<length; i++)
  {
    p_data[i] = p_byte[i];
  }

  return ret;
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
  flash_end    = addr + length - 1;

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
