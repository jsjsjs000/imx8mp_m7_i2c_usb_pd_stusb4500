#include <stdlib.h>
#include <string.h>

/* Freescale includes. */
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include <fsl_gpio.h>
#include <fsl_uart_freertos.h>
#include <fsl_uart.h>
#include <fsl_wdog.h>

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

/* Board config */
#include "board_cfg/board.h"
#include "board_cfg/clock_config.h"
#include "board_cfg/pin_mux.h"

#include "main.h"
#include "i2c_task.h"

static void gpio_init(void);
static void master_task(void *pvParameters);

void delay_ms(int ms)
{
	volatile int d = 0;
	for (int j = 0; j < ms * 75 * 1000; j++)
		d++;
}

void main(void)
{
	BOARD_InitMemory();
	BOARD_RdcInit();
	BOARD_InitBootPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	PRINTF("\r\nCortex-M7 started.\r\n");

	gpio_init();
	i2c_task_initialize();

	if (xTaskCreate(master_task, "Master_task", configMINIMAL_STACK_SIZE + TASK_STACK_SIZE, NULL,
			master_task_PRIORITY, NULL) != pdPASS)
	{
		PRINTF("Failed to create master task.\r\n");
		vTaskSuspend(NULL);
	}

	if (xTaskCreate(i2c_task_task, "I2C_task", TASK_STACK_SIZE, NULL,
			master_task_PRIORITY, NULL) != pdPASS)
	{
		PRINTF("Failed to create I2C task.\r\n");
		vTaskSuspend(NULL);
	}

	PRINTF("Start scheduler.\r\n");
	vTaskStartScheduler();
	PRINTF("\r\nError: exit from scheduler.\r\n");
	while (true) ;
}

/// FreeRTOSConfig.h:
/// configCHECK_FOR_STACK_OVERFLOW 1
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
	PRINTF("\r\nError: stack overflow\r\n");
}

static void gpio_init(void)
{
	// gpio_pin_config_t gpio_config =
	// {
	// 	.direction = kGPIO_DigitalInput,
	// 	.outputLogic = 1,
	// 	.interruptMode = kGPIO_IntFallingEdge,
	// };
	// GPIO_PinInit(GPIO_BUTTON1_PORT, GPIO_BUTTON1_PIN, &gpio_config);
	// GPIO_PinInit(GPIO_BUTTON2_PORT, GPIO_BUTTON2_PIN, &gpio_config);
	// GPIO_PinInit(GPIO_BUTTON3_PORT, GPIO_BUTTON3_PIN, &gpio_config);
	// GPIO_PinInit(GPIO_BUTTON4_PORT, GPIO_BUTTON4_PIN, &gpio_config);
	// GPIO_EnableInterrupts(GPIO_BUTTON4_PORT, 1 << GPIO_BUTTON4_PIN);
	// EnableIRQ(GPIO1_INT5_IRQn);
}


// void GPIO1_INT5_IRQHandler(void)
// {
// 	GPIO_ClearPinsInterruptFlags(GPIO_BUTTON4_PORT, 1 << GPIO_BUTTON4_PIN);

// 	UBaseType_t irq_status = taskENTER_CRITICAL_FROM_ISR();
// 	// taskEXIT_CRITICAL_FROM_ISR(irq_status);

// 	PRINTF("GPIO IRQ\r\n");
// }

// void GPIO1_Combined_0_15_IRQHandler(void)
//	GPIO_GetPinsInterruptFlags()

static void master_task(void *pvParameters)
{
	PRINTF("Master task started.\r\n");

	// int i = 0;
	// uint32_t ms, cycle;
	// uint8_t led_on;
	while (true)
	{
		// ms = xTaskGetTickCount() * 1000 / configTICK_RATE_HZ;
		// cycle = (ms / 100) % 20;
		// led_on = cycle == 0 || cycle == 2;
		// GPIO_PinWrite(GPIO_LED_PORT, GPIO_LED_PIN, led_on);

		// GPIO_PinWrite(GPIO_BUTTON4_PORT, GPIO_BUTTON4_PIN, 0);
		// vTaskDelay(pdMS_TO_TICKS(1));
		// GPIO_PinWrite(GPIO_BUTTON4_PORT, GPIO_BUTTON4_PIN, 1);
		// vTaskDelay(pdMS_TO_TICKS(1));

		// uint32_t irq = GPIO_PinRead(GPIO_BUTTON4_PORT, GPIO_BUTTON4_PIN);
		// PRINTF("tick %d\r\n", irq);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	vTaskSuspend(NULL);
}
