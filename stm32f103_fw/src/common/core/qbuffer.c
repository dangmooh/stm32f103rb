/*
 * qbuffer.c
 *
 *  Created on: Feb 16, 2025
 *      Author: zvxc3
 */


#include "qbuffer.h"


void qbufferInit(void)
{

}

bool qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t length)
{
  bool ret = true;


  p_node->in = 0;
  p_node->out = 0;
  p_node->len = length;
  p_node->p_buf = p_buf; // buff가 null인 경우 index만 관리한다. 실제 data를 관리하는게 아니라.

  return ret;
}

bool qbufferWrite(qbuffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  uint32_t next_in;

  for(int i=0; i<length; i++)
  {
    next_in = (p_node->in + 1) % p_node->len; // 다음 in index를 구해서 buf가 비어있는지 확인

    if(next_in != p_node->out)
    {
      if(p_node->p_buf != NULL) // buf가 NULL이 아니면 write 한다.
      {
        p_node->p_buf[p_node->in] = p_data[i];
      }
      p_node->in = next_in; // NULL인 경우에는 index만 관리한다.
    }
    else // buffer가 꽉차있으면 break
    {
      ret = false;
      break;
    }
  }


  return ret;
}

bool qbufferRead(qbuffer_t *p_node, uint8_t *p_data, uint32_t length)
{
  uint8_t ret;


  for(int i =0; i<length; i++)
  {
    if(p_node->p_buf != NULL) // buf가 NULL이 아니면 Read.
    {
      p_data[i] = p_node->p_buf[p_node->out];
    }

    if(p_node->out != p_node->in) // data가 있다면 out index 증가
    {
      p_node->out = (p_node->out + 1) % p_node->len;
    }
    else
    {
      ret = false;
      break;
    }
  }


  return ret;
}

uint32_t qbufferAvailable(qbuffer_t *p_node) // 현재 buffer에 있는 개수를 넘긴다.
{
  uint32_t ret;

  ret = (p_node->in - p_node->out) % p_node->len;

  return ret;
}

void qbufferFlush(qbuffer_t *p_node) // buffer 비우기 in과 out이 동일한 경우 비운다.
{
  p_node->in = 0;
  p_node->out = 0;
}
