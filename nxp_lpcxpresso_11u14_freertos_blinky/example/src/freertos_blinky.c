/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

//	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 18); //D0
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 19); //D1
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 17); //D2

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 11); //D4
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 10); //D3
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 9); //D2

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 8); //D1
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10); //D0

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 5); //D1
	//Chip_GPIO_SetPinState(LPC_GPIO, 1, 5, true); //D2

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 4);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 5);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 4, IOCON_FUNC0 | IOCON_STDI2C_EN);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 5, IOCON_FUNC0 | IOCON_STDI2C_EN);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 7);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 8);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 29);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 2);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 2, IOCON_FUNC0 | IOCON_MODE_INACT);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 27);

}

void relaySwitch(uint8_t rInd, bool state)
{
	uint8_t portNum[] = {0,0,0, 1, 1,1, 1, 1};
	uint8_t pinNum[]  = {7,9,8,29,27,5,25,24};

	Chip_GPIO_SetPinState(LPC_GPIO, portNum[rInd], pinNum[rInd], !state);


}

/* LED0 toggle thread */
static void vLEDTask0(void *pvParameters) {
	bool LedState = false;
	while (1) {
		Board_LED_Set(0, LedState);
		//Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, On);
		LedState = (bool) !LedState;

		for(int i=0; i<8; i++){
			//relaySwitch(i, LedState);
		}

		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 4);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 5);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 7);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 9);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 8);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 29);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 2);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 27);

		Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 17);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 17);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 18);


		vTaskDelay(configTICK_RATE_HZ/2);
	}
}

void setLed(int ledNum, bool state)
{
	int pinNum[] = {0, 8, 9, 10, 11};
	if((ledNum > 0) && (ledNum <5)){
		Chip_GPIO_SetPinState(LPC_GPIO, 1, pinNum[ledNum], state); //D2

	}

}

/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {
	bool LedState = false;
	int ledIndOn=1;
	while (1) {
//		Board_LED_Set(1, LedState);
		LedState = (bool) !LedState;


		for(int i=0; i<5; i++){
			setLed(i, (i==ledIndOn));
		}


		vTaskDelay(configTICK_RATE_HZ*2);
		ledIndOn++;
		if(ledIndOn>=5)
			ledIndOn=1;

		Chip_GPIO_SetPinState(LPC_GPIO, 0, 4, LedState);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 18, LedState);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 23, LedState);
	}
}

/* LED2 toggle thread */
static void vLEDTask2(void *pvParameters) {
	bool LedState = false;
	while (1) {
		Board_LED_Set(2, LedState);
		LedState = (bool) !LedState;


		for(int i=7; i>=0; i--){
			relaySwitch(i, true);
			vTaskDelay(configTICK_RATE_HZ/10);
		}

		vTaskDelay(configTICK_RATE_HZ);

		for(int i=0; i<8; i++){
			relaySwitch(i, false);
			vTaskDelay(configTICK_RATE_HZ/10);
		}
		vTaskDelay(configTICK_RATE_HZ);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	/* LED1 toggle thread */
//	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
//				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
//				(xTaskHandle *) NULL);

	/* LED2 toggle thread */
//	xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
//				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
//				(xTaskHandle *) NULL);

	/* LED0 toggle thread */
	xTaskCreate(vLEDTask0, (signed char *) "vTaskLed0",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
