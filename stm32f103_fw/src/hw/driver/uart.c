/*
 * uart.c
 *
 *  Created on: Feb 16, 2025
 *      Author: zvxc3
 */


#include "uart.h"
#include "qbuffer.h"


static bool is_open[UART_MAX_CH]; //static 해당 드라이버 c 에서만 사용하는 변수 및 다른 곳에서 같은 이름으로 사용해도 보호가능

static qbuffer_t qbuffer[UART_MAX_CH]; //

static uint8_t rx_buff[256]; // receive buffer
static uint8_t rx_data[UART_MAX_CH]; // receive data


UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;




bool uartInit(void)
{
  for(int i=0; i<UART_MAX_CH; i++)
  {
    is_open[i] = false;
  }

  return true;
}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;

  switch(ch)
  {
    case _DEF_UART1: // usb cdc
      is_open[ch] = true;
      ret = true;
      break;

    case _DEF_UART2:
          huart1.Instance         = USART1;
          huart1.Init.BaudRate    = baud;
          huart1.Init.WordLength  = UART_WORDLENGTH_8B;
          huart1.Init.StopBits    = UART_STOPBITS_1;
          huart1.Init.Parity      = UART_PARITY_NONE;
          huart1.Init.Mode        = UART_MODE_TX_RX;
          huart1.Init.HwFlowCtl   = UART_HWCONTROL_NONE;
          huart1.Init.OverSampling= UART_OVERSAMPLING_16;


          HAL_UART_DeInit(&huart1);// usb 터미널 쪽에서 baud를 바꾸는 경우 다시 uart를 재 오픈해야한다,

          qbufferCreate(&qbuffer[ch], &rx_buff[0], 256);

          /* DMA controller clock enable */
          __HAL_RCC_DMA1_CLK_ENABLE();

          /* DMA interrupt init */
          /* DMA1_Channel5_IRQn interrupt configuration */
          HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
          HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);


          if (HAL_UART_Init(&huart1) != HAL_OK)
          {
            ret = false;
          }
          else
          {
            ret = true;
            is_open[ch] = true;

            // DMA의 CNDTR 활성화 되면 read-only, 전송이 될 남아있는 데이터 갯수 = 초기에 설정한 값 현재는 256. normal이면 감소 후 0, circular 이면 reload
            // interrupt 방식은 1byte를 받으면 qbuff에 data를 write했지만 dma는 자동으로 buff에 써준다.
            if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)&rx_buff[0], 256) != HAL_OK) // circular 방식이라 자동으로 다시 순환
            {
              ret = false;
            }

            //설정하는 동안 data가 들어온 경우 data의 개수를 0으로 flush
            qbuffer[ch].in = qbuffer[ch].len - hdma_usart1_rx.Instance->CNDTR;
            qbuffer[ch].out = qbuffer[ch].in;

            /* interrupt 방식
             * if (HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data[_DEF_UART2], 1) != HAL_OK) // rx_data[_DEF_UART2]에 1byte를 받고 callback 함수 실행
              {
                ret = false;
              }*/
          }
          break;
  }

  return ret;
}
uint32_t uartAbailable(uint8_t ch) // recieve data가 존재하는지
{
  uint32_t ret = 0;
  switch(ch)
  {
    case _DEF_UART1:
      //ret = cdcAvailable();
      break;

    case _DEF_UART2:
      qbuffer[ch].in = (qbuffer[_DEF_UART2].len - hdma_usart1_rx.Instance->CNDTR); // CNDTR은 256에서 감소하므로 전체 size에서 빼 in_index를 설정해준다.
      ret = qbufferAvailable(&qbuffer[ch]);
      break;
  }

  return ret;
}

uint8_t uartRead(uint8_t ch) // buffer에서 읽어온다.
{
  uint8_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      //ret = cdcREad();
      break;

    case _DEF_UART2:
      qbufferRead(&qbuffer[_DEF_UART2], &ret, 1);
      break;
  }

  return ret;
}

uint32_t  uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length) // ch에 p_data의 length 만큼 작성한다.
{
  uint32_t ret = 0;
  HAL_StatusTypeDef status;


  switch(ch)
  {
    case _DEF_UART1:
      //ret = cdcWrite(p_data, length);
      break;

    case _DEF_UART2:
      status = HAL_UART_Transmit(&huart1, p_data, length, 100);
      if (status == HAL_OK)
      {
        ret = length;
      }
      break;
  }

  return ret;
}

uint32_t  uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256]; // 가변 인자의 string 처리
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args); // buf에 가변인자 string을 받아서 작성한다. printf는 표준 입출력에 작성하지만 vsn은 buf에 작성

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);

  return ret;
}

uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      //ret - cdcGetBaud();
      break;
    case _DEF_UART2:
      ret = huart1.Init.BaudRate ;

      break;
  }

  return ret;
}







void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {

  }
}

/*interrupt 방식은 interrupt가 너무 많이 걸려서 고속의 통신에서는 buffer가 덮어 씌여져 DMA 방식이 좋다.*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // weak 함수를 같은 파일을 다른 곳에서 정의하면 그 함수가 호출된다.
{
  if (huart->Instance == USART1)
  {
    qbufferWrite(&qbuffer[_DEF_UART2], &rx_data[_DEF_UART2], 1); // 수신된 1byte를 buffer에 write한다.

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data[_DEF_UART2], 1); // 호출되고 interrupt를 다 꺼버려서 다시 호출해 1byte를 받는다.

  }
}


void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA10     ------> USART1_RX
    PA9     ------> USART1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA10     ------> USART1_RX
    PA9     ------> USART1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10|GPIO_PIN_9);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}
