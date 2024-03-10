/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#ifndef BSP_POWER_H
#define BSP_POWER_H

/** Type defintions *********************************/
typedef enum
{
    POWER_SOURCE_NONE,
    POWER_SOURCE_USB,  // --> Calibration Mode
    POWER_SOURCE_MAINS, // --> I2C Slave Mode & MODEBUS-RTU(RS485) Mode
    POWER_SOURCE_ALL
} POWER_SOURCE;

#ifdef	__cplusplus
extern "C" {
#endif

    void POWER_Init(void);
    POWER_SOURCE POWER_SourceGet(void);
    void ACCESS_SourceSet(bool set);
    bool ACCESS_SourceGet(void);
    bool I2C_Bus_SourceGet(void);

#ifdef	__cplusplus
}
#endif

#endif //BSP_POWER_H
