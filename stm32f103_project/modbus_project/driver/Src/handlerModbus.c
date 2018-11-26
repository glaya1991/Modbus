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
uint8_t UnRxBufEcho[UN_BUF_SIZE]={0}; // buffer for received data
uint16_t UnRxCnt=0;
uint8_t UnRxFlag = 0;

uint8_t UnIRQFlag = 0;

uint8_t modbus_sm=0;
uint8_t ResponseFlag = 0;

//stm32f1xx_it.c
//extern uint8_t flag_tim1;
//extern uint32_t htim1_cnt, htim1_max;

// slaveMODBUS.c
TConst( TPartitionDs8 ) UnRxTxBuf = { &UnTxBuf[0], sizeof(UnTxBuf) };
TVar( U16 ) UnRxTxSize;

//parserMODBUS.case
TConst( TPartitionU16s16 )  MODICON_DB = { &Reg16[0], (NREG16<<1)};

uint8_t gi=0, gj=0, res;  //test

extern uint8_t irq_cnt;

void InitModbusDB(void)
{
    uint16_t i=0, j=0x0030;
    uint16_t N=(MODICON_DB.Size>>1);
    for(i=0; i<N; i++){
        MODICON_DB.ADR[i] = (uint16_t)((j<<8)|(j+1));
        j+=2;
    }
    return;
}

void InitModbus(void)
{
    receive_IT(UnRxBufIT, 1);
    UnIRQFlag = 0;
    return;
}

void HandlerModbus(void)
{   
    switch(modbus_sm){
        case WAIT_QUERY:
            if (UnIRQFlag){ // wait for 1 byte to receive
                // receive by bytes: from extern
                receive_IT(UnRxBufIT, 1);
                UnIRQFlag = 0;
            }
                
            if(UnRxFlag){ // wait for timeout -- get frame (query)
               UnRxFlag = 0;
                if(ResponseFlag)
                    modbus_sm = PARSE_RESPONSE;
                else
                    modbus_sm = PARSE_QUERY;
            }
            break;
            
        case PARSE_QUERY:                  
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
            
            //clear rx_buffer and counter
            memset(&UnRxBuf, 0, UnRxTxSize);
            UnRxCnt = 0;
            UnRxFlag = 0;
            ResponseFlag = 1;
            
            // receive bytes: echo-response
            receive_IT(UnRxBufIT, 1); //UnRxTxSize
            USARTN_RE_DE_TX;
            irq_cnt = 0;
            transmit_IT(UnTxBuf, UnRxTxSize);
            //HAL_UART_Transmit_DMA(HUART, UnTxBuf, UnRxTxSize);
            
            modbus_sm = WAIT_QUERY;  //WAIT_RESPONSE
            break;
        
        case PARSE_RESPONSE:
            ResponseFlag = 0;
            abort_receiveIT();
            
             // check echo-response (temp) 
            {
                UnRxBuf[0]+=0x10; 
                UnRxBuf[1]=irq_cnt; 

                USARTN_RE_DE_TX;
                HAL_UART_Transmit(&huart1, UnRxBuf, UnRxTxSize, 100);
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
            UnRxFlag = 0;
            UnIRQFlag = 1;
            irq_cnt =0;
            modbus_sm = WAIT_QUERY;
            
            break;
            
        /*   
        case WAIT_RESPONSE:
            if (UnTxFlag != 1){   
            //HAL_Delay(1);   // (?)temp delay: add one more case for last symbol
            UnTxFlag = 0;
            USARTN_RE_DE_RX;
            
            modbus_sm = WAIT_ECHO;
            }
            break;
        
        case WAIT_ECHO:
            if (UnRxFlag == 1){ 
                
            // check echo-response (temp) 
            {
                UnRxBuf[0]+=0x10; 
                UnRxBuf[1]=irq_cnt; 

                USARTN_RE_DE_TX;
                HAL_UART_Transmit(&huart1, UnRxBuf, UnRxTxSize, 100);
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
            UnRxFlag = 0;
            UnIRQFlag = 1;
            modbus_sm = WAIT_QUERY;
            }
            break;
         */
             
        default:
            break;
    }
       
}

int handleRx(void)
{    
    //if(!UnTxFlag){
        UnRxBuf[(UnRxCnt++)%UN_BUF_SIZE] = UnRxBufIT[0];
        UnIRQFlag = 1;
    //}
    return 0;
}


void endRx(void)
{
    
    return;
}

void endTx(void)
{
    //UnTxFlag = 2;
    UnTxFlag = 0;
    USARTN_RE_DE_RX;
    return;
}

void getFrame(void)
{
    if(UnRxCnt>1){
        UnRxFlag = 1;
    }
    return;
}



