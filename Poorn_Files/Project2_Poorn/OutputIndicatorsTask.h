/*
 * OutputIndicatorsTask.h
 *
 *  Created on: Apr 20, 2019
 *      Author: poorn
 */

#ifndef OUTPUTINDICATORSTASK_H_
#define OUTPUTINDICATORSTASK_H_

#define Servo_Polling_Timems       500

#define Servo_Host_Unknown           false

#if     Servo_Host_Unknown
    #define Output_Print   UARTprintf
#else
    #define Output_Print   cust_print
#endif

#define Output_DEBUG_PRINTF        true

// Standard Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "drivers/pinout.h"
#include "utils/uartstdio.h"

// Third Party Includes
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "inc/hw_adc.h"
#include "inc/hw_pwm.h"

// TivaWare includes
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/i2c.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/fpu.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"

#include "sensorlib/i2cm_drv.h"

// System clock rate, 120 MHz
#define SYSTEM_CLOCK    120000000U

#define Servo_PWM_Freq      50
#define Servo_PWM_Cycles    (uint32_t)((SYSTEM_CLOCK / 64) / Servo_PWM_Freq)

#define Servo_Open_Position     (uint32_t)(Servo_PWM_Cycles * 0.2)
#define Servo_Close_Position    (uint32_t)(Servo_PWM_Cycles * 0.075)

#define Servo_Door_Open_Timeoutms           10000

#define     SV_Enable_Pos       0
#define     SV_Enable_Mask      (1 << SV_Enable_Pos)

void Servo_PWM_Init(void);
void Servo_Door_Open(void);
void Servo_Door_Close(void);

#define     BZ_Enable_Pos       4
#define     BZ_Enable_Mask      (1 << SV_Enable_Pos)


void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);

#define     SJ_Enable_Pos       0
#define     SJ_Enable_Mask      (1 << SJ_Enable_Pos)

#define     SJ_DayTime_Pos      1
#define     SJ_DayTime_Mask     (3 << SJ_DayTime_Pos)
#define     SJ_Morning_Time     (0 << SJ_DayTime_Pos)
#define     SJ_Afternoon_Time   (1 << SJ_DayTime_Pos)
#define     SJ_Evening_Time     (2 << SJ_DayTime_Pos)
#define     SJ_Night_Time       (3 << SJ_DayTime_Pos)

#define     SJ_Person_ID_Pos    3
#define     SJ_Person_ID_Mask   (1 << SJ_Person_ID_Pos)
#define     SJ_Person_ID_Poorn  (0 << SJ_Person_ID_Pos)
#define     SJ_Person_ID_Khalid (1 << SJ_Person_ID_Pos)

// Set up a memorable token for "Word Pause"
#define WP 6    // 6 is 90ms pause

void SJ_Init(void);
void SJ_Select_Message(void);
void OutputIndicatorsTask(void *pvParameters);

#endif /* OUTPUTINDICATORSTASK_H_ */
