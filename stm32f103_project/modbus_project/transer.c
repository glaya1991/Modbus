/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "transfer.h"
uint8_t msg_rx_1byte[1];
#define DELAU_US for(uint32_t i=0;i<50;i=i+2){i--;}

int transmitter_array(uint8_t *arr, uint16_t size)
{
    HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX);
    DELAU_US;
    HAL_UART_Transmit(&huart1, arr, size, 1000);
    DELAU_US;
    HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX);
    
    return 0;
}

int transmitter(uint8_t byte)
{
    uint8_t buf[1] = {byte};
    HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX);
    HAL_UART_Transmit(&huart1, &buf, 1, 100);
    HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX);
    return 0;
}

uint8_t receiver(void)
{
    //uint8_t buf[1];
    //HAL_UART_Receive(&huart1, &buf, 1, 1000);
    
    uint8_t byte = msg_rx_1byte[0];
    
    return byte;
}