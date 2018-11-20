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
uint8_t UnTxErr[6]={'E', 'R', 'R', 'O', 'R', '\n'};
uint16_t UnTxCnt = 0;
uint8_t UnTxFlag = 0;

uint8_t UnRxBufIT[UN_BUF_SIZE]={0}; //buffer for receiving 1 byte (for unknown size of query)
uint8_t UnRxBuf[UN_BUF_SIZE]={0}; // buffer for received data
uint16_t UnRxCnt=0;
uint8_t UnRxFlag = 0;

uint8_t modbus_sm=0;

//stm32f1xx_it.c
//extern uint8_t flag_tim1;
//extern uint32_t htim1_cnt, htim1_max;

// slaveMODBUS.c
TConst( TPartitionDs8 ) UnRxTxBuf = { &UnTxBuf[0], sizeof(UnTxBuf) };
TVar( U16 ) UnRxTxSize;

//parserMODBUS.case
TConst( TPartitionU16s16 )  MODICON_DB = { &Reg16[0], (NREG16<<1)};

uint8_t gi=0, gj=0, res;  //test

void InitModbusDB(void)
{
    uint16_t i=0, j=0x0030;
    for(i=0; i<(MODICON_DB.Size); i++){
        MODICON_DB.ADR[i] = (uint16_t)((j<<8)|(j+1));
        j+=2;
    }
    return;
}

void InitModbus(void)
{
    receive_IT(UnRxBufIT, 1);
    UnRxFlag = 0;
    return;
}

void HandlerModbus(void)
{   
    switch(modbus_sm){
        case WAIT_QUERY:
            if (UnRxFlag){ // wait for 1 byte to receive
                // receive by bytes: from extern
                receive_IT(UnRxBufIT, 1);
                UnRxFlag = 0;
            }
                
//            if(flag_tim1){ // wait for timeout -- get frame (query)
//               modbus_sm = PARSE_QUERY;
//            }
            break;
            
        case PARSE_QUERY:         
            HAL_GPIO_TogglePin(LED_B1_GPIO_Port, LED_B1_Pin);           

            //copy rx_buffer
            memcpy(&UnTxBuf, &UnRxBuf, UnRxCnt);
            UnRxTxSize = UnRxCnt;
            UnRxCnt = 0;                            // temp
            memset(&UnRxBuf, 0xFF, UnRxTxSize);     // temp
            
            //parse
            if(MODBUStrasact()){
                //memcpy(&UnTxBuf, &UnTxErr, 6);
                UnRxTxSize = 6; //error case: not finished
            }

            modbus_sm = SEND_RESPONSE;
            break;
        
        case SEND_RESPONSE: 
            // break receiving (1 byte)
            abort_receiveIT();
            
            // transmit and receive echo
            UnTxFlag = 1;
            USARTN_RE_DE_TX;
            
            // receive bytes: echo-response
            receive_IT(UnRxBuf, UnRxTxSize);
            transmit_IT(UnTxBuf, UnRxTxSize);
            //HAL_UART_Transmit_DMA(HUART, UnTxBuf, UnRxTxSize);
            
            modbus_sm = WAIT_RESPONSE;
            break;
                
        case WAIT_RESPONSE:
            if (UnTxFlag != 1){   
            //HAL_Delay(1);   // (?)temp delay: add one more case for last symbol
            UnTxFlag = 0;
            USARTN_RE_DE_RX;

            // check echo-response (temp) 
            {
                UnRxBuf[0]+=0x10; 

                USARTN_RE_DE_TX;
                HAL_UART_Transmit(&huart1, UnRxBuf, UnRxTxSize, 1000);
                USARTN_RE_DE_RX;
                
                // clear rx buffer
                res = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
                while(res != 0){
                HAL_UART_Receive(&huart1, UnRxBuf, 1, 100);
                res = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
                }
            }

            //clear rx_buffer and counter
            memset(&UnRxBuf, 0, UnRxTxSize);
            UnRxCnt = 0;
            //flag_tim1 = 0;
            UnRxFlag = 1;
            
            modbus_sm = WAIT_QUERY;
            }
            break;
            
            
        default:
            break;
    }
       
}

int addToModbus(void)
{    
    if(!UnTxFlag){
        UnRxBuf[(UnRxCnt++)%UN_BUF_SIZE] = UnRxBufIT[0];
        UnRxFlag = 1;
    }
    return 0;
}


void endRxModbus(void)
{
    if(UnTxFlag){
        UnTxFlag = 2;
    }
    return;
}

void startParseModbus(void)
{
    if(UnRxCnt){
        modbus_sm = PARSE_QUERY;
    }
    return;
}



