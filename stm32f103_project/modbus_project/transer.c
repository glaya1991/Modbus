/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "transfer.h"

//uint8_t u1rx_buf_1byte[1];
uint8_t UnRxBuf_[UN_BUF_SIZE];
uint16_t UnRxSize_ = 0;
uint16_t UnRxCnt_ = 0;

#define DELAU_US for(uint32_t i=0;i<50;i=i+2){i--;}

int transmit_IT(uint8_t *arr, uint16_t size)
{
    HAL_UART_Transmit_IT(HUART, arr, size);
    return 0;
}

void receive_IT(uint16_t size)
{
    UnRxSize_ = size;
    UnRxCnt_ = 0;
    HAL_UART_Receive_IT(HUART, UnRxBuf_, UnRxSize_);
    return;
}

uint8_t get_received_byte(void)
{
    uint8_t byte = UnRxBuf_[(UnRxCnt_++)];
    return byte;
}

int abort_receiveIT(void)
{
    HAL_UART_AbortReceive_IT(HUART);
    return 0;
}