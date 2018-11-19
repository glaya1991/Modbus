/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "stm32f1xx_hal.h"
#include "transfer.h"
#include <string.h>
#include "handlerModbus.h"

#define NREG16  32
uint16_t Reg16[NREG16]={0};

// RS485 Transfer (UART + USART1_RE_DE_Pin)
uint8_t UnTxBuf[UN_BUF_SIZE]={0};
uint16_t UnTxCnt=0;
uint8_t UnTxFlag = 0;

uint8_t UnRxBuf[UN_BUF_SIZE]={0};
uint16_t UnRxCnt=0;
uint8_t UnRxFlag = 0;

uint8_t modbus_sm=0;

//stm32f1xx_it.c
extern uint8_t flag_tim1;
//extern uint32_t htim1_cnt, htim1_max;

//extern uint8_t u1rx_buf_[U1_BUF_SIZE]={0};
//extern uint8_t u1rx_buf_1byte[1];

// slaveMODBUS.c
TConst( TPartitionDs8 ) UnRxTxBuf = { &UnTxBuf[0], sizeof(UnTxBuf) };
TVar( U16 ) UnRxTxSize;

//parserMODBUS.case
TConst( TPartitionU16s16 )  MODICON_DB = { &Reg16[0], (NREG16<<1)};

uint8_t i=0, j=0, res;

void InitModbusDB(void)
{
    uint16_t i=0, j=1;
    for(i=0; i<(MODICON_DB.Size); i++){
        MODICON_DB.ADR[i] = (uint16_t)((j<<8)|(j+1));
        j+=2;
    }
    
//    MODICON_DB.ADR[0]=0x1234;
//    MODICON_DB.ADR[1]=0x5678;
//    MODICON_DB.ADR[2]=0x9ABC;
//    MODICON_DB.ADR[3]=0xDEF1;
    
    return;
}

void HandlerModbus(void)
{
    
    switch(modbus_sm){
        case WAIT_QUERY:
            if (UnRxFlag)
            {
                receive_IT(1);
                //HAL_UART_Receive_IT(&huart1, u1rx_buf_, 1);
                UnRxFlag = 0;
            }
                
            if(flag_tim1)
                modbus_sm = PARSE_QUERY;
            
            break;
            
        case PARSE_QUERY:         
            HAL_GPIO_TogglePin(LED_B1_GPIO_Port, LED_B1_Pin);           
            //abort_receiveIT();
            
            //copy rx_buffer
            UnTxCnt = UnRxCnt;
            UnRxCnt = 0;
            
            memcpy(&UnTxBuf, &UnRxBuf, UnTxCnt);
            memset(&UnRxBuf, 0xFF, UnTxCnt);
            
            
            //UnRxTxSize = UnTxCnt;
            //MODBUStrasact();
            //UnTxCnt = UnRxTxSize;
            
            modbus_sm = SEND_RESPONSE;
            break;
        
        case SEND_RESPONSE:
            abort_receiveIT();
            
            UnTxFlag = 1;
            HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX);
            receive_IT(UnTxCnt);
            transmit_IT(UnTxBuf, UnTxCnt);
            while(UnTxFlag ==1);
            
            modbus_sm = WAIT_RESPONSE;
            break;
            
        case WAIT_RESPONSE:
            if (UnTxFlag != 1){
            HAL_Delay(10);
            HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX);
            UnTxFlag = 0;

            // test echo  
                for(i=0;i<UnTxCnt;i++){
                    UnRxBuf[i]+=0x1+j; 
                }
                //j++;

                HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_TX);
                HAL_UART_Transmit(&huart1, UnRxBuf, UnTxCnt, 1000);
                HAL_GPIO_WritePin(USART1_RE_DE_GPIO_Port, USART1_RE_DE_Pin, RS485_RX);
                res = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
                while(res != 0){
                HAL_UART_Receive(&huart1, UnRxBuf, 1, 1000);
                res = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
                }

            //clear rx_buffer and counter
            memset(&UnRxBuf, 0, UnTxCnt);
            UnRxCnt = 0;
            flag_tim1 = 0;
            UnRxFlag = 1;
            
            modbus_sm = WAIT_QUERY;
            }
            break;
            
            
        default:
            break;
    }
    
 
    
}

int AddToModbus(void)
{
//    uint8_t byte_recv = get_received_byte(); 
//    uint8_t byte_send = UnTxBuf[UnRxCnt];
    
//    if(byte_recv != byte_send){ 
//        UnRxCnt = 0;
//        modbus_sm = SEND_RESPONSE;
//        return -1;
//    }
    
    UnRxBuf[(UnRxCnt++)%UN_BUF_SIZE] = get_received_byte();//byte_recv;
    UnRxFlag = 1;
    
    return 0;
}

void endTxModbus(void)
{
    UnTxFlag = 2;
    return;
}

