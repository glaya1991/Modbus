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

#define HUART           &huart1
#define U1_BUF_SIZE     64
#define DEV_ADDR        0x12

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart1;

int transmit_IT(uint8_t *arr, uint16_t size);
void receive_IT(uint16_t size);
uint8_t get_received_byte(void);

int abort_receiveIT(void);

#ifdef __cplusplus
}
#endif

#endif /* TRANSFER_H */

