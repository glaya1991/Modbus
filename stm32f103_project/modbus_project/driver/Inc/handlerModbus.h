/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   handlerModbus.h
 * Author: Елена
 *
 * Created on 15 ноября 2018 г., 13:41
 */

#include "slaveMODBUStrasact.h"

#ifndef HANDLERMODBUS_H
#define HANDLERMODBUS_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define WAIT_QUERY          0
#define PARSE_QUERY         1
#define SEND_RESPONSE       2    
#define WAIT_RESPONSE       3  
#define WAIT_ECHO           4
   
void InitModbusDB(void);

void InitModbus(void);
void HandlerModbus(void);

void getFrame(void);
int handleRx(void);
void endRx(void);
void endTx(void);



#ifdef __cplusplus
}
#endif

#endif /* HANDLERMODBUS_H */

