/**
  System Interrupts Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC24FJ128GA010
        Version           :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA0, high using LATA0.

  @Description
    Sets the GPIO pin, RA0, high using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 high (1)
    WATCHDOG_SetHigh();
    </code>

*/
#define WATCHDOG_SetHigh()          _LATA0 = 1
/**
  @Summary
    Sets the GPIO pin, RA0, low using LATA0.

  @Description
    Sets the GPIO pin, RA0, low using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 low (0)
    WATCHDOG_SetLow();
    </code>

*/
#define WATCHDOG_SetLow()           _LATA0 = 0
/**
  @Summary
    Toggles the GPIO pin, RA0, using LATA0.

  @Description
    Toggles the GPIO pin, RA0, using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA0
    WATCHDOG_Toggle();
    </code>

*/
#define WATCHDOG_Toggle()           _LATA0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA0.

  @Description
    Reads the value of the GPIO pin, RA0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA0
    postValue = WATCHDOG_GetValue();
    </code>

*/
#define WATCHDOG_GetValue()         _RA0
/**
  @Summary
    Configures the GPIO pin, RA0, as an input.

  @Description
    Configures the GPIO pin, RA0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an input
    WATCHDOG_SetDigitalInput();
    </code>

*/
#define WATCHDOG_SetDigitalInput()  _TRISA0 = 1
/**
  @Summary
    Configures the GPIO pin, RA0, as an output.

  @Description
    Configures the GPIO pin, RA0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an output
    WATCHDOG_SetDigitalOutput();
    </code>

*/
#define WATCHDOG_SetDigitalOutput() _TRISA0 = 0
/**
  @Summary
    Sets the GPIO pin, RA1, high using LATA1.

  @Description
    Sets the GPIO pin, RA1, high using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA1 high (1)
    WP_SetHigh();
    </code>

*/
#define WP_SetHigh()          _LATA1 = 1
/**
  @Summary
    Sets the GPIO pin, RA1, low using LATA1.

  @Description
    Sets the GPIO pin, RA1, low using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA1 low (0)
    WP_SetLow();
    </code>

*/
#define WP_SetLow()           _LATA1 = 0
/**
  @Summary
    Toggles the GPIO pin, RA1, using LATA1.

  @Description
    Toggles the GPIO pin, RA1, using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA1
    WP_Toggle();
    </code>

*/
#define WP_Toggle()           _LATA1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA1.

  @Description
    Reads the value of the GPIO pin, RA1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA1
    postValue = WP_GetValue();
    </code>

*/
#define WP_GetValue()         _RA1
/**
  @Summary
    Configures the GPIO pin, RA1, as an input.

  @Description
    Configures the GPIO pin, RA1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA1 as an input
    WP_SetDigitalInput();
    </code>

*/
#define WP_SetDigitalInput()  _TRISA1 = 1
/**
  @Summary
    Configures the GPIO pin, RA1, as an output.

  @Description
    Configures the GPIO pin, RA1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA1 as an output
    WP_SetDigitalOutput();
    </code>

*/
#define WP_SetDigitalOutput() _TRISA1 = 0
/**
  @Summary
    Sets the GPIO pin, RG0, high using LATG0.

  @Description
    Sets the GPIO pin, RG0, high using LATG0.

  @Preconditions
    The RG0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG0 high (1)
    IR_SetHigh();
    </code>

*/
#define IR_SetHigh()          _LATG0 = 1
/**
  @Summary
    Sets the GPIO pin, RG0, low using LATG0.

  @Description
    Sets the GPIO pin, RG0, low using LATG0.

  @Preconditions
    The RG0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG0 low (0)
    IR_SetLow();
    </code>

*/
#define IR_SetLow()           _LATG0 = 0
/**
  @Summary
    Toggles the GPIO pin, RG0, using LATG0.

  @Description
    Toggles the GPIO pin, RG0, using LATG0.

  @Preconditions
    The RG0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG0
    IR_Toggle();
    </code>

*/
#define IR_Toggle()           _LATG0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RG0.

  @Description
    Reads the value of the GPIO pin, RG0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG0
    postValue = IR_GetValue();
    </code>

*/
#define IR_GetValue()         _RG0
/**
  @Summary
    Configures the GPIO pin, RG0, as an input.

  @Description
    Configures the GPIO pin, RG0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG0 as an input
    IR_SetDigitalInput();
    </code>

*/
#define IR_SetDigitalInput()  _TRISG0 = 1
/**
  @Summary
    Configures the GPIO pin, RG0, as an output.

  @Description
    Configures the GPIO pin, RG0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG0 as an output
    IR_SetDigitalOutput();
    </code>

*/
#define IR_SetDigitalOutput() _TRISG0 = 0
/**
  @Summary
    Sets the GPIO pin, RG1, high using LATG1.

  @Description
    Sets the GPIO pin, RG1, high using LATG1.

  @Preconditions
    The RG1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG1 high (1)
    CAL_SetHigh();
    </code>

*/
#define CAL_SetHigh()          _LATG1 = 1
/**
  @Summary
    Sets the GPIO pin, RG1, low using LATG1.

  @Description
    Sets the GPIO pin, RG1, low using LATG1.

  @Preconditions
    The RG1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG1 low (0)
    CAL_SetLow();
    </code>

*/
#define CAL_SetLow()           _LATG1 = 0
/**
  @Summary
    Toggles the GPIO pin, RG1, using LATG1.

  @Description
    Toggles the GPIO pin, RG1, using LATG1.

  @Preconditions
    The RG1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG1
    CAL_Toggle();
    </code>

*/
#define CAL_Toggle()           _LATG1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RG1.

  @Description
    Reads the value of the GPIO pin, RG1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG1
    postValue = CAL_GetValue();
    </code>

*/
#define CAL_GetValue()         _RG1
/**
  @Summary
    Configures the GPIO pin, RG1, as an input.

  @Description
    Configures the GPIO pin, RG1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG1 as an input
    CAL_SetDigitalInput();
    </code>

*/
#define CAL_SetDigitalInput()  _TRISG1 = 1
/**
  @Summary
    Configures the GPIO pin, RG1, as an output.

  @Description
    Configures the GPIO pin, RG1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG1 as an output
    CAL_SetDigitalOutput();
    </code>

*/
#define CAL_SetDigitalOutput() _TRISG1 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ128GA010

  @Description
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize(void);

#endif
