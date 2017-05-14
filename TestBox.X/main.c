/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FJ128GA010
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "Uart_add.h"
#include "eeprom.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool INT_Flag = false;
bool INT_Flag_Clr = false;

// EEPROM data
//uint16_t testNumber;

// EEPROM test numbers address 
const uint16_t TestNumberAddress = 0x1;
const uint16_t ConstCurrAddress = 0x5;
const uint16_t vRefAddress = 0xD;
const uint16_t TC1GainPAddress = 0x15;
const uint16_t TC2GainPAddress = 0x1D;
const uint16_t TC3GainPAddress = 0x25;
const uint16_t TC1GainNAddress = 0x2D;
const uint16_t TC2GainNAddress = 0x35;
const uint16_t TC3GainNAddress = 0x3D;

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    WP_SetHigh();   
    __delay_ms(1000);
    
    // calculations and control constants declaration
    double TC1GainP = 32.245;
    double TC2GainP = 32.247;
    double TC3GainP = 32.249;
    double TC1GainN = 32.246;
    double TC2GainN = 32.248;
    double TC3GainN = 32.250;
    double ConstCurr = 0.0003000;
    double vRef = 0.00204800;
      
    WP_SetHigh();
    Clrscr();
    Home();
    
    char buffer[30];
    char errorYN[]=("\n>>Sorry, only 'Y' or 'N' are accepted\n");
    char error[]=("\n>>Sorry, something is wrong\n");
    char YN;
    
    // read constant current value
    unsigned long ConstCurrInt;          
    unsigned char ConstCurrIntArray[4];   
    EEPROM_Read(ConstCurrAddress, ConstCurrIntArray, 4);          
    ConstCurrInt = ((unsigned long)ConstCurrIntArray[0] << 24) + ((unsigned long)ConstCurrIntArray[1] << 16) + ((unsigned long)ConstCurrIntArray[2] << 8) + ConstCurrIntArray[3];
    ConstCurr = (float) ConstCurrInt / 1000000;
    
    //read ADC voltage reference value
    unsigned long vRefInt;          
    unsigned char vRefIntArray[4];   
    EEPROM_Read(vRefAddress, vRefIntArray, 4);          
    vRefInt = ((unsigned long)vRefIntArray[0] << 24) + ((unsigned long)vRefIntArray[1] << 16) + ((unsigned long)vRefIntArray[2] << 8) + vRefIntArray[3];
    vRef = (float) vRefInt / 1000000;
    
    // states of the calibration cycle
    enum CalStates{
        Start,
        CalStart,
        CurrentCal,
        RefCal,
        TC1Pos,
        TC1Neg,
        TC2Pos,
        TC2Neg,
        TC3Pos,
        TC3Neg,
        IR
    };
    
    // starting off state - all switches off, current direction positive
    enum CalStates state = Start;
    
    // Calibration mode on
    while (CAL_GetValue() == true)
    {     
        switch(state){
            
        // Calibration procedure welcome screen    
        case Start:           
            putsU2("Thermocouple Test Box Calibration");
            state = CalStart;
            break;
            
        // Calibration procedure start    
        case CalStart:                              
            if (INT_Flag == true)
            {               
                state = CurrentCal;
                putsU2("Test Current Calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
            }
            break;
            
        // Constant current source current value calibration    
        case CurrentCal:
            putsU2("Stored current source value is:");
            
            snprintf(buffer,30,"%.3f uA",(ConstCurr * 1000));
            putsU2(buffer);
            
            putsU2("Do you want to update current source value?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y") == 0)	 
            { 
                putsU2("Please enter new current source value");
                putsU2("In the format: 'xxx.xxx' and press 'enter'");
                getsU2(buffer, sizeof(buffer));
                
                //Add test for limits and only numbers allowed
                
                putsU2("You entered:");
                putsU2(buffer);
                putsU2("Save in the EEPORM?:Y/N");
                YN = getU2();              
                if (YN == 'Y')          	 
                {                
                    ConstCurr = atof(buffer);
                    ConstCurrInt = ConstCurr * 1000;

                    /*
                    snprintf(buffer,30,"%ld",ConstCurrInt);
                    putsU2("converted to integer:");
                    putsU2(buffer);
                    */

                    ConstCurrIntArray[0] = (ConstCurrInt >> 24) & 0xff;
                    ConstCurrIntArray[1] = (ConstCurrInt >> 16) & 0xff;
                    ConstCurrIntArray[2] = (ConstCurrInt >> 8) & 0xff;
                    ConstCurrIntArray[3] = ConstCurrInt & 0xff;

                    /*                       
                    ConstCurrInt = ((((unsigned long) ConstCurrIntArray[0]) << 24) | (((unsigned long) ConstCurrIntArray[1]) << 16) | (((unsigned long) ConstCurrIntArray[2]) << 8) | ConstCurrIntArray[3]);
                    snprintf(buffer,30,"%ld",ConstCurrInt);
                    putsU2("Split and reassembled:");
                    putsU2(buffer);
                    */

                    WP_SetLow();
                    __delay_ms(100);
                    EEPROM_Write(ConstCurrAddress, ConstCurrIntArray, 4);
                    __delay_ms(100);
                    WP_SetHigh();
                    putsU2("Saved!");
                }
                else if (YN == 'N') 
                {
                    putsU2("Not Saved!");
                    break;
                }
                else
                {
                    putsU2(errorYN);
                    break;
                }
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = RefCal;
                putsU2("ADC reference voltage Calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
                                   
        // ADC Voltage reference value calibration     
        case RefCal:
            
            putsU2("Stored voltage reference value is:");
            
            snprintf(buffer,30,"%.5f V",(vRef * 10));
            putsU2(buffer);
            
            putsU2("Do you want to update voltage reference?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter voltage reference value:");
                putsU2("In the format: 'x.xxxxx' and press 'enter'");
                getsU2(buffer, sizeof(buffer));
                
                //Add test for limits and only numbers allowed
                
                putsU2("You entered:");
                putsU2(buffer);
                
                vRef = atof(buffer);
                
                vRefInt = vRef * 100000;
                snprintf(buffer,30,"%ld",vRefInt);
                putsU2("converted to integer:");
                putsU2(buffer);
                
                vRefIntArray[0] = (vRefInt >> 24) & 0xff;
                vRefIntArray[1] = (vRefInt >> 16) & 0xff;
                vRefIntArray[2] = (vRefInt >> 8) & 0xff;
                vRefIntArray[3] = vRefInt & 0xff;
                                             
                ConstCurrInt = ((((unsigned long) vRefIntArray[0]) << 24) | (((unsigned long) vRefIntArray[1]) << 16) | (((unsigned long) vRefIntArray[2]) << 8) | vRefIntArray[3]);
                snprintf(buffer,30,"%ld",vRefInt);
                putsU2("Split and reassembled:");
                putsU2(buffer);
                
                WP_SetLow();
                __delay_ms(100);
                EEPROM_Write(vRefAddress, vRefIntArray, 4);
                __delay_ms(100);
                WP_SetHigh();
                           
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = TC1Pos;
                putsU2("TC1 test channel positive gain calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
        
        // TC1 channel positive gain calibration
        case TC1Pos:
            
            putsU2("Stored TC1 positive gain value is:");
            
            snprintf(buffer,30,"%.3f",(TC1GainP));
            putsU2(buffer);
            
            putsU2("Do you want to update TC1 positive gain?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter TC1 positive gain value:");
                getsU2(buffer, sizeof(buffer));
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = TC1Neg;
                putsU2("TC1 test channel negative gain calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
                       
        // TC1 channel negative gain calibration
        case TC1Neg:
            
            putsU2("Stored TC1 negative gain value is:");
            
            snprintf(buffer,30,"%.3f",(TC1GainN));
            putsU2(buffer);
            
            putsU2("Do you want to update TC1 negative gain?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter TC1 negative gain value:");
                getsU2(buffer, sizeof(buffer));
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = TC2Pos;
                putsU2("TC2 test channel positive gain calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
        
        // TC2 channel positive gain calibration
        case TC2Pos:
            
            putsU2("Stored TC2 positive gain value is:");
            
            snprintf(buffer,30,"%.3f",(TC2GainP));
            putsU2(buffer);
            
            putsU2("Do you want to update TC2 positive gain?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter TC2 positive gain value:");
                getsU2(buffer, sizeof(buffer));
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = TC2Neg;
                putsU2("TC2 test channel negative gain calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
                       
        // TC2 channel negative gain calibration
        case TC2Neg:
            
            putsU2("Stored TC2 negative gain value is:");
            
            snprintf(buffer,30,"%.3f",(TC2GainN));
            putsU2(buffer);
            
            putsU2("Do you want to update TC2 negative gain?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter TC2 negative gain value:");
                getsU2(buffer, sizeof(buffer));
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = TC3Pos;
                putsU2("TC3 test channel positive gain calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
        
        // TC3 channel positive gain calibration
        case TC3Pos:
            
            putsU2("Stored TC3 positive gain value is:");
            
            snprintf(buffer,30,"%.3f",(TC3GainP));
            putsU2(buffer);
            
            putsU2("Do you want to update TC3 positive gain?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter TC3 positive gain value:");
                getsU2(buffer, sizeof(buffer));
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = TC3Neg;
                putsU2("TC3 test channel negative gain calibration");
                
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
                       
        // TC3 channel negative gain calibration
        case TC3Neg:
            
            putsU2("Stored TC3 negative gain value is:");
            
            snprintf(buffer,30,"%.3f",(TC3GainN));
            putsU2(buffer);
            
            putsU2("Do you want to update TC3 negative gain?:Y/N");
            getsU2(buffer, sizeof(buffer));
            if (strcmp(buffer,"Y")==0)	 
            { 
                putsU2("Please enter TC3 negative gain value:");
                getsU2(buffer, sizeof(buffer));
            }
            else if (strcmp(buffer,"N")==0)
            { 
                putsU2("Please press test button:");
                
                while (INT_Flag == false)
                {
                }           
                state = IR;
                putsU2("Insulation resistance test check");
               
                INT_Flag = false;
                EX_INT0_InterruptEnable();
                break;
            }
            else
            {
                putsU2(errorYN);
                break;
            }
        
        // Insulation resistance test
        case IR:
            
            putsU2("Connect >1.1Gohm and press 'enter'");    
            //getsU2(s, sizeof(s));
            //if (strcmp(s,"\r") == 0)
            if (getU2() == '\r')          
            {
                if (IR_GetValue() == true)
                {
                    putsU2("High resistance detected");
                    putsU2("Connect <782Mohm and press 'enter'");
                }
                else
                {
                    putsU2("High resistance not detected!");
                }
            }
            else
            {
                putsU2(errorYN);
                break;
            }
            //getsU2(s, sizeof(s));
            //if (strcmp(s,"\r") == 0)
            if (getU2() == '\r') 
            {
                if (IR_GetValue() == false)
                {
                    putsU2("Low resistance detected");
                    putsU2("Please press test button:");
                }
                else
                {
                    putsU2("Low resistance not detected!");
                    putsU2("Please press test button:");
                }
            }
            else
            {
                putsU2(error);
                break;
            }
            while (INT_Flag == false)
            {
            }           
            state = Start;
            Clrscr();
            Home();
               
            INT_Flag = false;
            EX_INT0_InterruptEnable();
            break;
                       
        }//switch(CalStates)       
    }//if (CAL_GetValue() == true)
    
    while (1)
    {
        if (INT_Flag == true)
        {
            char buffer[30];
            uint8_t TestNumber[2];
            uint16_t tempData;
            
            char test[10];
            putsU2("Please provide input:");
            getsU2(test,10);

            __delay_ms(25);
           
            // read previous test number
            EEPROM_Read(TestNumberAddress, TestNumber, 2);
            tempData = (TestNumber[0] << 8) + TestNumber[1];
            
            snprintf(buffer,30,"Test No:%d",tempData);
            putsU2(buffer);
            
            // increment test number
            tempData++;
            TestNumber[0] = tempData >> 8;
            TestNumber[1] = (uint8_t) tempData;
            
            // Number of tests saved
            WP_SetLow();
            __delay_ms(50);
            EEPROM_Write(TestNumberAddress, TestNumber, 2);
            __delay_ms(50);
            WP_SetHigh();
            
            putsU2("Test number saved");
            
            INT_Flag = false;
            EX_INT0_InterruptEnable();
        }     
        if (INT_Flag_Clr == true)
        {
            putsU2("Clearing EEPROM");
            WP_SetLow();
            __delay_ms(50);
            uint8_t zeroData[] = {0x0, 0x0};
            EEPROM_Write(TestNumberAddress, zeroData, 2);
            __delay_ms(50);
            WP_SetHigh();
            
            putsU2("EEPROM cleared");
            
            INT_Flag_Clr = false;
            EX_INT2_InterruptEnable();
            
        }       
        // Add your application code
    }

    return -1;
}
/*
 End of File
*/