/*
 * BB_Comm_Task.c
 *
 *  Created on: Apr 15, 2019
 *      Author:  Author: Khalid AlAwadhi
 */
#include "BB_Comm_Task.h"

//Standard includes
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//TivaWare includes


//FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//My includes
#include "Global_Defines.h"
#include "Master_Functions.h"
#include "My_UART.h"

/* Global Variables */
extern QueueHandle_t xQueue_Msgs;


uint8_t BB_Comm_TaskInit()
{
    //Create task, if it fails return 1, else 0
    if( xTaskCreate(BB_Comm_Task,					/* The function that implements the task */
			   (const portCHAR *)"BB_Comm",			/* The text name assigned to the task - for debug only as it is not used by the kernel */
               ((configMINIMAL_STACK_SIZE) * 5),	/* The size of the stack to allocate to the task */
			   NULL,								/* The parameter passed to the task */
			   PRIORITY_BB_COMM_TASK, 				/* The priority assigned to the task */
			   NULL)								/* The task handle is not required, so NULL is passed */
    			!= pdTRUE
      )
      {
    	return 1;
      }

	return 0;
}



void BB_Comm_Task(void *pvParameters)
{
	/* Init UART1 - Used to talk to the BeagleBone via Bluetooth */
	Init_UARTx(UART1, SYSTEM_CLOCK, 9600, true);

	/* Create a queue capable of containing 50 messages */
	xQueue_Msgs = xQueueCreate( 50, sizeof( MsgStruct ) );

	if( xQueue_Msgs == NULL )
	{
		/* Queue was not created and must not be used. */
		Log_UART0(GetCurrentTime(), BB_Comm, "CRITICAL", "Could not create xQueue_Msgs! x_x");
	}
	else
	{
		Log_UART0(GetCurrentTime(), BB_Comm, "INFO", "Created xQueue_Msgs successfully!");
	}




	/* Variable that will store and decode received messages */
	struct MsgStruct RXMessage;

	while(1)
	{
		if( xQueue_Msgs != 0 )
		{
			/* Receive a message on the created queue.
			 * Block for 10 ticks if a message is not immediately available */
			if( xQueueReceive( xQueue_Msgs, &RXMessage, ( TickType_t ) 10 ) )
			{
				//HERE IS WHERE I NEED TO SEND DAT TO BB

			}
		}
	}
}