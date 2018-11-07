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

#define U1_BUF_SIZE     32
#define DEV_ADDR        0x12

#ifdef __cplusplus
extern "C" {
#endif

 extern UART_HandleTypeDef huart1;
    
uint8_t receiver(void);
int transmitter(uint8_t byte);
int transmitter_array(uint8_t *arr, uint16_t size);


#ifdef __cplusplus
}
#endif

#endif /* TRANSFER_H */

