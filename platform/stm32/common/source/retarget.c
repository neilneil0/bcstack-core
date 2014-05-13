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
#include "stm32f401_discovery.h"
#include "bluetooth.h"

#if !(HAVE_SHELL)
int fputc(int ch, FILE *f) 
{
    return ch;
}
#else // HAVE_SHELL

#define DBGPORT                           USART6
#define DBGPORT_CLK_ENABLE()              __USART6_CLK_ENABLE()
#define DBGPORT_TX_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE() 

#define DBGPORT_FORCE_RESET()             __USART6_FORCE_RESET()
#define DBGPORT_RELEASE_RESET()           __USART6_RELEASE_RESET()

/* Definition for DBGPORT Pins */
#define DBGPORT_TX_PIN                    GPIO_PIN_6
#define DBGPORT_TX_GPIO_PORT              GPIOC
#define DBGPORT_TX_AF                     GPIO_AF8_USART6

/* Definition for DBGPORT's NVIC */
#define DBGPORT_IRQn                      USART6_IRQn
#define DBGPORT_IRQHandler                USART6_IRQHandler

UART_HandleTypeDef dbgport;

//TODO: this is toooo big. make it smaller in final version
#define BT_UART_FIFO_SIZE 256

static struct{
    u8 buffer[BT_UART_FIFO_SIZE];
    u8 wrptr;
    u8 rdptr;
} txfifo;

void dbguart_open(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    DBGPORT_TX_GPIO_CLK_ENABLE();
    DBGPORT_CLK_ENABLE(); 
    GPIO_InitStruct.Pin       = DBGPORT_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = DBGPORT_TX_AF;
    HAL_GPIO_Init(DBGPORT_TX_GPIO_PORT, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(DBGPORT_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(DBGPORT_IRQn);

    dbgport.Instance        = DBGPORT;
    dbgport.Init.BaudRate   = 115200;
    dbgport.Init.WordLength = UART_WORDLENGTH_8B;
    dbgport.Init.StopBits   = UART_STOPBITS_1;
    dbgport.Init.Parity     = UART_PARITY_NONE;
    dbgport.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    dbgport.Init.Mode       = UART_MODE_TX;
  
    if(HAL_UART_Init(&dbgport) != HAL_OK)
    {
        while(1);
    }

    memset(&txfifo, 0, sizeof(txfifo));

#if 0 // test transmision
    while (1) {
        HAL_UART_Transmit(&dbgport, "hello", 5, 5000);
    }
#endif
}

int fputc(int ch, FILE *f)
{
    if (txfifo.wrptr + 1 != txfifo.rdptr) {
        txfifo.buffer[txfifo.wrptr++] = ch;
    }
    __HAL_UART_ENABLE_IT(&dbgport, UART_IT_TXE);
    return ch;
}

void DBGPORT_IRQHandler(void)
{
    volatile uint32_t tmp1 = 0, tmp2 = 0;
    volatile u8 data;
  
    tmp1 = __HAL_UART_GET_FLAG(&dbgport, UART_FLAG_TXE);
    tmp2 = __HAL_UART_GET_IT_SOURCE(&dbgport, UART_IT_TXE);
    /* UART in mode Transmitter ------------------------------------------------*/
    if((tmp1 != RESET) && (tmp2 != RESET))
    {
        if (txfifo.rdptr != txfifo.wrptr) {
            data = txfifo.buffer[txfifo.rdptr++];
            dbgport.Instance->DR = data;
        } else {
            __HAL_UART_DISABLE_IT(&dbgport, UART_IT_TXE);
        }
    }
}

#endif // HAVE_SHELL
