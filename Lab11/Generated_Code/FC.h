/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : FC.h
**     Project     : Lab11
**     Processor   : MK22FN512VDC12
**     Component   : FreeCntr32
**     Version     : Component 02.070, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-10-10, 14:28, # CodeGen: 4
**     Abstract    :
**         This device "FreeCntr32" implements 32-bit Free Running Counter
**     Settings    :
**          Component name                                 : FC
**          Periodic interrupt source                      : FTM0_C0V
**          Counter                                        : FTM0_CNT
**          Interrupt service/event                        : Enabled
**            Interrupt                                    : INT_FTM0
**            Interrupt priority                           : medium priority
**          Resolution                                     : 1 ms
**          Same resolution in modes                       : yes
**          Component uses entire timer                    : no
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          Referenced components                          : 
**            RealTime_LDD                                 : RealTime_LDD
**     Contents    :
**         Reset     - byte FC_Reset(void);
**         GetTimeUS - byte FC_GetTimeUS(word *Time);
**         GetTimeMS - byte FC_GetTimeMS(word *Time);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file FC.h
** @version 01.00
** @brief
**         This device "FreeCntr32" implements 32-bit Free Running Counter
*/         
/*!
**  @addtogroup FC_module FC module documentation
**  @{
*/         

#ifndef __FC_H
#define __FC_H

/* MODULE FC. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "RealTimeLdd1.h"

#include "Cpu.h"



/*
** ===================================================================
**     Method      :  FC_Reset (component FreeCntr32)
*/
/*!
**     @brief
**         This method clears the counter.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
#define FC_Reset() (RealTimeLdd1_Reset(RealTimeLdd1_DeviceData))

/*
** ===================================================================
**     Method      :  FC_GetTimeUS (component FreeCntr32)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in microseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in microseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
#define FC_GetTimeUS(Time) (RealTimeLdd1_GetTimeUS(RealTimeLdd1_DeviceData, (uint16_t *)Time))

/*
** ===================================================================
**     Method      :  FC_GetTimeMS (component FreeCntr32)
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in milliseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in milliseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
#define FC_GetTimeMS(Time) (RealTimeLdd1_GetTimeMS(RealTimeLdd1_DeviceData, (uint16_t *)Time))

/* END FC. */

#endif 
/* ifndef __FC_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
