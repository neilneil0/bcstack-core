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

#ifndef _BOARD_H_
#define _BOARD_H_

#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"

#define BOARD_NAME "stm32f429discovery"

#define BTUART                           USART1
#define BTUART_CLK_ENABLE()              __USART1_CLK_ENABLE();
#define BTUART_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define BTUART_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE() 

#define BTUART_FORCE_RESET()             __USART1_FORCE_RESET()
#define BTUART_RELEASE_RESET()           __USART1_RELEASE_RESET()

/* Definition for BTUART Pins */
#define BTUART_TX_PIN                    GPIO_PIN_9
#define BTUART_TX_GPIO_PORT              GPIOA  
#define BTUART_TX_AF                     GPIO_AF7_USART1
#define BTUART_RX_PIN                    GPIO_PIN_10
#define BTUART_RX_GPIO_PORT              GPIOA 
#define BTUART_RX_AF                     GPIO_AF7_USART1

/* Definition for BTUART's NVIC */
#define BTUART_IRQn                      USART1_IRQn
#define BTUART_IRQHandler                USART1_IRQHandler

#define DBGPORT                           USART2
#define DBGPORT_CLK_ENABLE()              __USART2_CLK_ENABLE()
#define DBGPORT_TX_GPIO_CLK_ENABLE()      __GPIOD_CLK_ENABLE() 

#define DBGPORT_FORCE_RESET()             __USART2_FORCE_RESET()
#define DBGPORT_RELEASE_RESET()           __USART2_RELEASE_RESET()

/* Definition for DBGPORT Pins */
#define DBGPORT_TX_PIN                    GPIO_PIN_5
#define DBGPORT_TX_GPIO_PORT              GPIOD
#define DBGPORT_TX_AF                     GPIO_AF7_USART2

/* Definition for DBGPORT's NVIC */
#define DBGPORT_IRQn                      USART2_IRQn
#define DBGPORT_IRQHandler                USART2_IRQHandler

#endif // _BOARD_H_
