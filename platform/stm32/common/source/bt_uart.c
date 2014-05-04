/*
  Copyright 2013-2014 bcstack.org

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include "stm32f4xx_hal.h"
#include "bluetooth/host.h"

#define BTUART                           USART2
#define BTUART_CLK_ENABLE()              __USART2_CLK_ENABLE();
#define BTUART_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define BTUART_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE() 

#define BTUART_FORCE_RESET()             __USART2_FORCE_RESET()
#define BTUART_RELEASE_RESET()           __USART2_RELEASE_RESET()

/* Definition for BTUART Pins */
#define BTUART_TX_PIN                    GPIO_PIN_2
#define BTUART_TX_GPIO_PORT              GPIOA  
#define BTUART_TX_AF                     GPIO_AF7_USART2
#define BTUART_RX_PIN                    GPIO_PIN_3
#define BTUART_RX_GPIO_PORT              GPIOA 
#define BTUART_RX_AF                     GPIO_AF7_USART2

/* Definition for BTUART's NVIC */
#define BTUART_IRQn                      USART2_IRQn
#define BTUART_IRQHandler                USART2_IRQHandler

UART_HandleTypeDef btuart;
static __IO ITStatus ready = RESET;
static __IO ITStatus txbusy = RESET;

#define BT_UART_FIFO_SIZE 256

static struct{
    u8 buffer[BT_UART_FIFO_SIZE];
    u8 wrptr;
    u8 rdptr;
} rxfifo, txfifo;

void bt_uart_open(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    BTUART_TX_GPIO_CLK_ENABLE();
    BTUART_RX_GPIO_CLK_ENABLE();
    BTUART_CLK_ENABLE(); 
    GPIO_InitStruct.Pin       = BTUART_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = BTUART_TX_AF;
    HAL_GPIO_Init(BTUART_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BTUART_RX_PIN;
    GPIO_InitStruct.Alternate = BTUART_RX_AF;
    HAL_GPIO_Init(BTUART_RX_GPIO_PORT, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(BTUART_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(BTUART_IRQn);

    btuart.Instance        = BTUART;
    btuart.Init.BaudRate   = 921600;
    btuart.Init.WordLength = UART_WORDLENGTH_9B;
    btuart.Init.StopBits   = UART_STOPBITS_1;
    btuart.Init.Parity     = UART_PARITY_EVEN;
    btuart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    btuart.Init.Mode       = UART_MODE_TX_RX;
  
    if(HAL_UART_Init(&btuart) != HAL_OK)
    {
        while(1);
    }

    memset(&rxfifo, 0, sizeof(rxfifo));
    memset(&rxfifo, 0, sizeof(txfifo));
}

void bt_uart_close(void)
{
    BTUART_FORCE_RESET();
    BTUART_RELEASE_RESET();

    HAL_GPIO_DeInit(BTUART_TX_GPIO_PORT, BTUART_TX_PIN);
    HAL_GPIO_DeInit(BTUART_RX_GPIO_PORT, BTUART_RX_PIN);

    HAL_NVIC_DisableIRQ(BTUART_IRQn);
}

void bt_uart_write (u8 c)
{
    if (txfifo.wrptr + 1 != rxfifo.rdptr) {
        txfifo.buffer[txfifo.wrptr++] = c;
    }
    __HAL_UART_ENABLE_IT(&btuart, UART_IT_TXE);
}

u8 bt_uart_read(u8* c)
{
    if (ready == RESET) {
        ready = SET;
        __HAL_UART_ENABLE_IT(&btuart, UART_IT_PE);
        __HAL_UART_ENABLE_IT(&btuart, UART_IT_ERR);
        __HAL_UART_ENABLE_IT(&btuart, UART_IT_RXNE);
    }

    if (rxfifo.rdptr == rxfifo.wrptr) {
        return 0;
    } else {
        *c = rxfifo.buffer[rxfifo.rdptr++];
        return 1;
    }
}

void BTUART_IRQHandler(void)
{
  volatile uint32_t tmp1 = 0, tmp2 = 0;
  volatile u8 data;

  tmp1 = __HAL_UART_GET_FLAG(&btuart, UART_FLAG_PE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(&btuart, UART_IT_PE);  
  /* UART parity error interrupt occurred ------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(&btuart, UART_FLAG_PE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(&btuart, UART_FLAG_FE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(&btuart, UART_IT_ERR);
  /* UART frame error interrupt occurred -------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(&btuart, UART_FLAG_FE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(&btuart, UART_FLAG_NE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(&btuart, UART_IT_ERR);
  /* UART noise error interrupt occurred -------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(&btuart, UART_FLAG_NE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(&btuart, UART_FLAG_ORE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(&btuart, UART_IT_ERR);
  /* UART Over-Run interrupt occurred ----------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(&btuart, UART_FLAG_ORE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(&btuart, UART_FLAG_TXE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(&btuart, UART_IT_TXE);
  /* UART in mode Transmitter ------------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    if (txfifo.rdptr != txfifo.wrptr) {
        data = txfifo.buffer[txfifo.rdptr++];
        btuart.Instance->DR = data;
    } else {
        __HAL_UART_DISABLE_IT(&btuart, UART_IT_TXE);
    }
  }
  
  tmp1 = __HAL_UART_GET_FLAG(&btuart, UART_FLAG_RXNE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(&btuart, UART_IT_RXNE);
  // RX
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
      data = (uint8_t)(btuart.Instance->DR & (uint8_t)0x00FF);
      if (rxfifo.wrptr + 1 != rxfifo.rdptr) {
        rxfifo.buffer[rxfifo.wrptr++] = data;
      }
    __HAL_UART_CLEAR_FLAG(&btuart, UART_FLAG_RXNE);
  }
}
