
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "transfer.h"
#include "string.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t u1tx_buf[U1_BUF_SIZE<<2];
uint16_t u1tx_cnt, u1tx_cnt_irq;
uint8_t u1tx_flag=0;

uint8_t u1rx_buf[U1_BUF_SIZE];
uint16_t u1rx_cnt;
uint8_t u1rx_flag=0;

uint8_t u1rx_buf_echo[U1_BUF_SIZE]={0};

extern uint8_t msg_rx_1byte[1];

extern uint8_t flag_tim1;
uint32_t t0=0, t1=0, tcase=0;

extern uint32_t htim1_cnt, htim1_max;
extern uint8_t flag1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  uint8_t strTest[10] = "TEST103\r\n";
//  uint8_t strSize = strlen(strTest);
//  uint8_t test_cnt=0;
  uint8_t i;
  uint8_t res=0;
  
  HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
  //HAL_UART_Receive_IT(&huart1, msg_rx_1byte, 1);
  HAL_TIM_Base_Start_IT(&htim1);
  
  for(i=0; i<10;i++){
      u1tx_buf[i]=0x30+i;
  }
  
  

  while(1){
      u1tx_buf[0]=0x30+u1tx_cnt_irq;
      u1tx_cnt_irq =0;
      HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX);
      HAL_UART_TransmitReceive_IT(&huart1, (uint8_t *)u1tx_buf, (uint8_t *)u1rx_buf_echo, 4);
      HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX);
      HAL_Delay(5000);
  }
  
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
   
 

/*  RS485-TRANSFER              */      
    if(flag_tim1)
    {
        HAL_GPIO_TogglePin(LED_B1_GPIO_Port, LED_B1_Pin);

        HAL_UART_AbortReceive_IT(&huart1);

        //copy rx data
        u1tx_cnt = u1rx_cnt;
        u1tx_cnt_irq = 0;
        u1rx_cnt = 0;
        memcpy(&u1tx_buf, &u1rx_buf, u1tx_cnt);
        
        //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 1);
        //HAL_UART_Receive_IT(&huart1, u1rx_buf_echo, u1tx_cnt);
        //transmit_array((uint8_t *)u1tx_buf, u1tx_cnt);
        //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
        
        HAL_UART_Receive_IT(&huart1, u1rx_buf_echo, u1tx_cnt);
        HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX);
        HAL_UART_Transmit_DMA(&huart1, (uint8_t *)u1tx_buf, u1tx_cnt);
        HAL_Delay(10000);
        //while(u1tx_cnt_irq);
        
        
        u1tx_buf[0]=0x30+u1tx_cnt_irq;
        HAL_UART_Receive_IT(&huart1, u1rx_buf_echo, 1);
        HAL_UART_Transmit_DMA(&huart1, (uint8_t *)u1tx_buf, 1);
        HAL_Delay(2000);
        
        
        HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX);
        
        
        
        //clear stm32_rx_buffer  
        res = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
        while(res != 0){
        HAL_UART_Receive(&huart1, msg_rx_1byte, 1, 100);
        res = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
        }
               
        
        //clear rx_buffer and counter
        memset(&u1rx_buf, 0, u1tx_cnt); 
        u1rx_cnt = 0;
        flag_tim1 =0;
        //u1rx_flag = 1; 
    }
                 
    if(u1rx_flag)
    {
      receive_byte();
      u1rx_flag = 0; 
    }
   
    
  }
  
  
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
