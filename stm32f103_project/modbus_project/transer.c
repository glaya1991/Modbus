/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "transfer.h"

//uint8_t u1rx_buf_1byte[1];
uint8_t u1rx_buf_[U1_BUF_SIZE];
uint16_t u1rx_size_ = 0;
uint16_t u1rx_cnt_ = 0;

#define DELAU_US for(uint32_t i=0;i<50;i=i+2){i--;}

int transmit_IT(uint8_t *arr, uint16_t size)
{
    HAL_UART_Transmit_IT(HUART, arr, size);
    
    return 0;
}

void receive_IT(uint16_t size)
{
    u1rx_size_ = size;
    u1rx_cnt_ = 0;
    HAL_UART_Receive_IT(HUART, u1rx_buf_, u1rx_size_);
}

uint8_t get_received_byte(void)
{
    uint8_t byte = u1rx_buf_[(u1rx_cnt_++)];
    return byte;
}

int abort_receiveIT(void)
{
    HAL_UART_AbortReceive_IT(HUART);
    return 0;
}