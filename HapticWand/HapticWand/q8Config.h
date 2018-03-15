#ifndef Q8CONFIG_H
#define Q8CONFIG_H

#include <rtdm/rtdm.h>

/**
 * Communication struct
 */
struct Q8_Config{
    int iChannelNum;
    int iCardNum;
    int16_t wValueSigned;
    uint16_t uwValueUnsigned;//Analog output value
    unsigned int uiFuncIndex;
    uint8_t ubDacMode;
    uint8_t  ubEcountMode;/*encoder*/
    uint8_t ubEbcdMode;
    uint8_t ubEquadratureMode;
    uint8_t ubIndexEnable;
    uint8_t ubIndexPolarity;
    int32_t dwNvalue;//encoder counter value
    uint32_t udwDataDirection;/*digital I/0*/
    uint32_t udwDataRegister;
    int iClockSource;/*COUNTER*/
    uint32_t udwPeriod;
    uint32_t udwLow;
    uint32_t udwHigh;
    int iCntrlEn;
    uint8_t irq;
    int onlyDigitalData;
 };


typedef struct Q8_Config struct_Q8_Config;

#endif // Q8CONFIG_H
