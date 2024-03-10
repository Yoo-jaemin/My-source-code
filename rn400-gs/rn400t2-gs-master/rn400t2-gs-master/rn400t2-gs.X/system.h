/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include <stdbool.h>

#define MAIN_RETURN void

/*** System States **************************************************/
typedef enum
{
    SYSTEM_STATE_USB_START,
    SYSTEM_STATE_USB_SUSPEND,
    SYSTEM_STATE_USB_RESUME
} SYSTEM_STATE;

/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  SYSTEM_STATE - the state to initialize the system into
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize( SYSTEM_STATE state );

/*********************************************************************
* Function: void SYSTEM_Tasks(void)
*
* Overview: Runs system level tasks that keep the system running
*
* PreCondition: System has been initalized with SYSTEM_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
//void SYSTEM_Tasks(void);
//#define SYSTEM_Tasks()

// nakholee append
//Helper function to execute some blocking delay.
void DelayRoutine(unsigned int DelayAmount);
//Before resetting the microcontroller, we should shut down the USB module 
//gracefully, to make sure the host correctly recognizes that we detached
//from the bus.  Some USB hosts malfunction/fail to re-enumerate the device
//correctly if the USB device does not stay detached for a minimum amount of
//time before re-attaching to the USB bus.  For reliable operation, the USB
//device should stay detached for as long as a human would require to unplug and
//reattach a USB device (ex: 100ms+), to ensure the USB host software has a 
//chance to process the detach event and configure itself for a state ready for 
//a new attachment event.
void ResetDeviceCleanly(void);
// goto bootloader
void ResetBootloaderCleanly(void);

#endif //SYSTEM_H
