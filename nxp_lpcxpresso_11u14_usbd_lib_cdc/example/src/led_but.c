#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include <limits.h>

#define GPIO_PININT_INDEX		0 /* PININT index used for GPIO mapping */

void pushButtonIrqHandler()
{
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	uint32_t intStat = Chip_PININT_GetIntStatus(LPC_PININT);
	Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH0|PININTCH1);
//	if(butTaskHandle != NULL){
//		xTaskNotifyFromISR(butTaskHandle, intStat+0x20, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
//	}
	if(mainTaskHandle != NULL){
		xTaskNotifyFromISR(mainTaskHandle, 1<<(intStat+3), eSetBits, &xHigherPriorityTaskWoken);
	}
}

void FLEX_INT0_IRQHandler(void)
{
	pushButtonIrqHandler();
}

void FLEX_INT1_IRQHandler(void)
{
	pushButtonIrqHandler();
}


void vLedTask(void *pvParameters)
{

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 25);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 25,
			(IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGMODE_EN));

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 5);
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 5,
			(IOCON_FUNC0 | IOCON_MODE_PULLDOWN | IOCON_DIGMODE_EN));

	/* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PINT);
	/* Configure interrupt channel for the GPIO pin in SysCon block */
	Chip_SYSCTL_SetPinInterrupt(0, 1, 25);
	Chip_SYSCTL_SetPinInterrupt(1, 1, 5);

	/* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_SetPinModeEdge(LPC_PININT, PININTCH0|PININTCH1);
	Chip_PININT_EnableIntHigh(LPC_PININT, PININTCH0|PININTCH1);

	/* Enable interrupt in the NVIC */
	NVIC_EnableIRQ(PIN_INT0_IRQn);
	NVIC_EnableIRQ(PIN_INT1_IRQn);


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

	Chip_GPIO_SetPinOutHigh(LPC_GPIO, 1, 11);
	Chip_GPIO_SetPinOutLow(LPC_GPIO, 1, 10);
	//Chip_GPIO_SetPortOutLow(LPC_GPIO, 1, 9);

	//char str[40];
	uint32_t ulNotifiedValue;
	//char str[25];
	for(;;){
		if(xTaskNotifyWait( 0x00, ULONG_MAX, &ulNotifiedValue,  500) == pdTRUE){
//			sprintf(str, "al %d\r\n", ulNotifiedValue);
//			vcomPrintf(str);
		}

		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 11);
		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 10);
		//Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 9);
//		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 8);
//		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 5);

		//sprintf(str, "vLedTask > it %d \r\n", i);
//		TickType_t ticks = xTaskGetTickCount;
//		int secs = ticks/1000;
//		if( (secs%60) == 0 ){
//			snprintf(str, 40, "uptime > %d min \r\n", secs/60);
//			vcomPrintf(str);
//		}

		//Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, Chip_GPIO_GetPinState(LPC_GPIO, 1, 5));
		//Chip_GPIO_SetPinState(LPC_GPIO, 1, 8, Chip_GPIO_GetPinState(LPC_GPIO, 1, 25));

		//vTaskDelay(500);
	}
}
