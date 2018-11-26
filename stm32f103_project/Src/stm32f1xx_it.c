/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
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
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

/* USER CODE BEGIN 0 */
#include "transfer.h"
#include "handlerModbus.h"
#include "Legacy/stm32_hal_legacy.h"
extern uint8_t UnTxBuf[UN_BUF_SIZE];
extern uint16_t UnTxCnt;
extern uint8_t UnTxFlag;

extern uint8_t UnRxBuf[UN_BUF_SIZE];
extern uint16_t UnRxCnt;
extern uint8_t UnIRQFlag;

//extern uint8_t u1rx_buf_[U1_BUF_SIZE];
//extern uint8_t u1rx_buf_1byte[1];

uint8_t flag_tim1=0;
uint32_t htim1_max = 0, htim1_cnt=0; 
uint32_t htim1_en_irq = 0;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM1 update interrupt.
*/
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
    
    // for TIM_Start_Base_IT()
//    1) 
//    htim1_cnt++;
//    if(htim1_cnt==htim1_max){
//        getFrame();
//    }
  //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 1);
   //HAL_GPIO_TogglePin(LED_G1_GPIO_Port, LED_G1_Pin);
 
  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
* @brief This function handles TIM1 capture compare interrupt.
*/
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */
    
    // for TIM_Start_OC_IT()
    
   //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 1);
  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

   //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
  /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
* @brief This function handles USART1 global interrupt.
*/
uint8_t irq_cnt = 0;
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
    //      for 115200 bit/s, symbol = 10bit:
    //          T_1symbol = 87 us 
    //          T_3.5symbol = 87*3.5 = 300 us
    //
    //      for 115200 bit/s, symbol = 12bit:
    //          T_1symbol = 104 us 
    //          T_3.5symbol = 104*3.5 = 365 us
    
    // 1) (old version)  
    //      if timer starts at the begin of program: 
    //      Update_IRQs occurs during all time (need to use htim_cnt, htim_cnt_max) 
    // TIM:     Tperiod = 5us, 
    //
    //          T_1symbol = 85 us (for 115200 bit/s)
    //          T_3.5symbol = 85*3.5 = 300 us
    //          cnt_3.5symbol = T_3.5symbol/Tperiod = 60
    
    // 2) Timer_OC (Output compare --> compare with "capture register"): // see tim.c --> Init!!!
    //          in void MX_TIM1_Init(void):
    //              htim1.Init.Period = 65535; 
    //          ToDo:
    //          0. first RX: Start Timer
    //          1. read current counter: __HAL_TIM_GET_COUNTER()
    //          2. shift compared value for T3.5sym from current: __HAL_TIM_SET_COMPARE(current counter + T3.5sym)
    //          IRQ: TIM1_CC_IRQHandler
    //          Callback: HAL_TIM_OC_DelayElapsedCallback()
    //
    // TIM:     Tstep= Prescaler*Tclk = 1us
    //          Tperiod = 65535 us (0xFFFF) 
    //          Tpulse = current + T_3.5symbol = current + 365 us
    
    // 3) Timer_Base (If cnt == period --> reset (update)): // see tim.c --> Init!!!
    //          in void MX_TIM1_Init(void):
    //              htim1.Init.Period = 365; 
    //          ToDo:
    //          0. first RX: Start Timer
    //          1. reset current counter: __HAL_TIM_SET_COUNTER(0)
    //          IRQ: TIM1_UP_IRQHandler
    //          Callback: HAL_TIM_PeriodElapsedCallback()
    //
    // TIM:     Tstep= Prescaler*Tclk = 1us
    //          Tperiod = T_3.5symbol = 365us
    
   
//  uint32_t isrflags   = (READ_REG(huart1.Instance->SR)); 
//  uint32_t cr1its   = (READ_REG(huart1.Instance->CR1));  
//  if(((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET)){
//      HAL_GPIO_TogglePin(LED_G1_GPIO_Port, LED_G1_Pin);
//  }
    

    
 HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 1);
 
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

      //1)
  //htim1_max = htim1_cnt+30;
  
  uint32_t curCnt;
  if(htim1_en_irq)
  {
      //2
//    __HAL_TIM_SET_COUNTER(&htim1, 0);
      //3
    curCnt = __HAL_TIM_GET_COUNTER(&htim1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint32_t)(curCnt+365));   
  }
  else
  {
        htim1_en_irq = 1;
      // 2)
//         HAL_TIM_Base_Start_IT(&htim1);
        // (!!!) if use MARCOS -- no first IRQ at 1 byte receive (!!!)
//              __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
//              __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);
              
//      __HAL_TIM_SET_COUNTER(&htim1, 0);
      // 3)
    curCnt = __HAL_TIM_GET_COUNTER(&htim1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint32_t)(curCnt+365));   
    HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_1);
  }
  
  //handleRx();

  HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
  
  irq_cnt++;
  
  //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1){
        endTx();
    }
    return;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        HAL_GPIO_WritePin(LED_B1_GPIO_Port, LED_B1_Pin, 1);
        handleRx();
        //endRx();
       HAL_GPIO_WritePin(LED_B1_GPIO_Port, LED_B1_Pin, 0);
    }
    return;
}


// Callbacks -- for DMA or IT only!!!
// for TIM_Base_Start_IT()
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 1);
    // 2)
    // (!!!) if use MARCOS -- no first IRQ at 1 byte receive (!!!)
    //__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_UPDATE);
    HAL_TIM_Base_Stop_IT(&htim1);
    htim1_en_irq = 0;
    getFrame();
    //HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
    return;  
}


// for TIM_OC_Start_IT()
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 1);
    // 3)
    // __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC4);
    HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_1);
    htim1_en_irq = 0;
    getFrame();
    HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, 0);
    return;  
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
