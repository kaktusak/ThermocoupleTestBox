/*
 * File:   eeprom.c
 * Author: ROBERT
 *
 * Created on March 4, 2017, 7:36 PM
 */

/******************************************************************************
 * Software License Agreement
 *
 * Copyright � 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED ìAS ISî WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/
#include <eeprom.h>
#include "pin_manager.h"

uint8_t EEPROM_Write(uint8_t address, uint8_t *pData, uint16_t nCount)
{
    I2C2_MESSAGE_STATUS status;
    uint8_t     writeBuffer[2];
    uint16_t    retryTimeOut, slaveTimeOut;
    uint16_t    counter;
    uint8_t     *pD;

    pD = pData;

    for (counter = 0; counter < nCount; counter++)
    {
        // build the write buffer 
        writeBuffer[0] = address;        // starting address of the EEPROM memory
        writeBuffer[1] = *pD;            // data to be saved

        retryTimeOut = 0;
        slaveTimeOut = 0;
        
        while(status != I2C2_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (2 is the count of bytes to write)
            I2C2_MasterWrite(writeBuffer,2,EEPROM_24LC01B_ADDRESS,&status);

            // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING)
            {
                // check for max retry and skip this byte
                if (slaveTimeOut == EEPROM_24LC01B_DEVICE_TIMEOUT)
                    return (0);
                else
                    slaveTimeOut++;
            }
            if (status == I2C2_MESSAGE_COMPLETE)
                break;
            
            // check for max retry and skip this byte
            if (retryTimeOut == EEPROM_24LC01B_RETRY_MAX)
                break;
            else
                retryTimeOut++;
        }
        // exit if the last transaction failed
        if (status == I2C2_MESSAGE_FAIL)
        {
            return(0);
            break;
        }
        __delay_ms(EEPROM_24LC01B_Delay);
        
        // increment data link if more than 1 byte is to be send
        pD++;
        address++;
    }
    return(1);
}

// Random read (any available address))
uint8_t EEPROM_Read(uint8_t address, uint8_t *pData, uint16_t nCount)
{
    I2C2_MESSAGE_STATUS status;
    uint8_t     writeBuffer[1];
    uint16_t    retryTimeOut, slaveTimeOut;
    uint16_t    counter;
    uint8_t     *pD;

    pD = pData;

    for (counter = 0; counter < nCount; counter++)
    {
        // starting address of the EEPROM memory
        writeBuffer[0] = address;                // high address

        retryTimeOut = 0;
        slaveTimeOut = 0;
        
        while(status != I2C2_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (2 is the count of bytes to write)
            I2C2_MasterWrite(writeBuffer,1,EEPROM_24LC01B_ADDRESS,&status);

            // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING)
            {
                // check for max retry and skip this byte
                if (slaveTimeOut == EEPROM_24LC01B_DEVICE_TIMEOUT)
                    return (0);
                else
                    slaveTimeOut++;
            }
            if (status == I2C2_MESSAGE_COMPLETE)
                break;

            // check for max retry and skip this byte
            if (retryTimeOut == EEPROM_24LC01B_RETRY_MAX)
                break;
            else
                retryTimeOut++;
        }
        
        // this portion will read the byte from the memory location.
        if (status == I2C2_MESSAGE_COMPLETE)
        {
            retryTimeOut = 0;
            slaveTimeOut = 0;

            while(status != I2C2_MESSAGE_FAIL)
            {
                // write one byte to EEPROM (1 is the count of bytes to write)
                I2C2_MasterRead(pD, 1, EEPROM_24LC01B_ADDRESS, &status);

                // wait for the message to be sent or status has changed.
                while(status == I2C2_MESSAGE_PENDING)
                {
                    // check for max retry and skip this byte
                    if (slaveTimeOut == EEPROM_24LC01B_DEVICE_TIMEOUT)
                        return (0);
                    else
                        slaveTimeOut++;
                }

                if (status == I2C2_MESSAGE_COMPLETE)
                    break;

                // check for max retry and skip this byte
                if (retryTimeOut == EEPROM_24LC01B_RETRY_MAX)
                    break;
                else
                    retryTimeOut++;
            }
        }

        // exit if the last transaction failed
        if (status == I2C2_MESSAGE_FAIL)
        {
            return(0);
            break;
        }
        
        // increment data links if more than one byte is to be read
        pD++;
        address++;

    }
    return(1);

}


