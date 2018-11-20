/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   transfer.h
 * Author: Елена
 *
 * Created on 31 октября 2018 г., 10:09
 */

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

#ifndef TRANSFER_H
#define TRANSFER_H

#define RS485_TX    1
#define RS485_RX    0 

#define USARTN_RE_DE_TX    HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX)
#define USARTN_RE_DE_RX    HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX)

#define HUART           &huart1
#define UN_BUF_SIZE     128

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart1;

int transmit_IT(uint8_t *arr, uint16_t size);
void receive_IT(uint8_t *arr, uint16_t size);
uint8_t get_received_byte(void);

int abort_receiveIT(void);

#ifdef __cplusplus
}
#endif

#endif /* TRANSFER_H */

