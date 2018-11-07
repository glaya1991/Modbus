/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   crc.h
 * Author: Елена
 *
 * Created on 6 ноября 2018 г., 14:53
 */
#include <stdint.h>

#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned short CRC16_Modbus(uint8_t *puchMsg, uint16_t usDataLen);


#ifdef __cplusplus
}
#endif

#endif /* CRC_H */

