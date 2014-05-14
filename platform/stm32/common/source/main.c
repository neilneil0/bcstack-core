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
#include "board.h"
#include "bluetooth.h"

#if BT_UART_LOOPBACK
void bt_uart_loopback(void);
#endif

void board_setup(void);
void Error_Handler(void);
#if (HAVE_SHELL)
void dbguart_open(void);
#endif

u8 bt_exit = 0;

int main(void)
{
    board_setup();

#if (HAVE_SHELL)
    dbguart_open();
    printf("welcome to bcstack\n");
    HAL_Delay(1000);
    printf("board = %s\n", BOARD_NAME);
#endif

#if BT_UART_LOOPBACK
    bt_uart_loopback();
#endif

    app_setup();

	while (bt_exit == 0) {
        app_loop();
	}
}

void Error_Handler(void)
{
    while(1);
}

void usleep(int ms)
{
    HAL_Delay(25);
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}
