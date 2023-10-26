	/* Freescale includes. */
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include <fsl_gpio.h>
#include <fsl_i2c.h>
#include <fsl_i2c_freertos.h>

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
#include "common.h"
#include "i2c_task.h"
#include "i2c_usb_pd_stusb4500.h"
#include "i2c_usb_pd_stusb4500_print.h"

static uint8_t i2c_buffor[I2C_BUFFOR_SIZE];
static i2c_master_handle_t *i2c_master_handle;

static i2c_rtos_handle_t master_rtos_handle;
static i2c_master_config_t masterConfig;
static i2c_master_transfer_t masterXfer;
static uint32_t sourceClock;

void i2c_task_initialize(void)
{
	CLOCK_SetRootMux(I2C_STUSB4500_CLK_ROOT, I2C_STUSB4500_ROOT_MUX_SYS_PLL_DIV); /* Set I2C source to SysPLL1 Div5 160MHZ */
	CLOCK_SetRootDivider(I2C_STUSB4500_CLK_ROOT, 1U, 10U);                   /* Set root clock to 160MHZ / 10 = 16MHZ */
	NVIC_SetPriority(I2C_STUSB4500_IRQN, 3);

	/*
		masterConfig.baudRate_Bps = 100000U;
		masterConfig.enableStopHold = false;
		masterConfig.glitchFilterWidth = 0U;
		masterConfig.enableMaster = true;
	*/
	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUDRATE;
	sourceClock = I2C_STUSB4500_CLK_FREQ;

	status_t status = I2C_RTOS_Init(&master_rtos_handle, I2C_STUSB4500, &masterConfig, sourceClock);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during init, 0x%x\r\n", status);
	}

	i2c_master_handle = &master_rtos_handle.drv_handle;

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress   = I2C_STUSB4500_SLAVE_ADDR_7BIT;
	masterXfer.direction      = kI2C_Write;
	masterXfer.data           = i2c_buffor;
	masterXfer.dataSize       = 0;
	masterXfer.flags          = kI2C_TransferDefaultFlag;
}

void i2c_task_task(void *pvParameters)
{
	PRINTF("I2C task started.\r\n");
	vTaskDelay(pdMS_TO_TICKS(500));

	uint16_t type_c_release_supported_by_device;
	if (i2c_usb_pd_stusb4500_read_type_c_release_supported_by_device(&type_c_release_supported_by_device))
		PRINTF("Type-C release supported by device = %d\r\n", type_c_release_supported_by_device);
	else
		PRINTF("Can't read Type-C release supported by device.\r\n");

	uint16_t power_delivery_release_supported_by_device;
	if (i2c_usb_pd_stusb4500_read_power_delivery_release_supported_by_device(&power_delivery_release_supported_by_device))
		PRINTF("Power Delivery release supported by device = %d.%d\r\n",
				power_delivery_release_supported_by_device >> 8, power_delivery_release_supported_by_device & 0xff);
	else
		PRINTF("Can't read power delivery release supported by device.\r\n");

	union stusb4500_alert_status1_t alert_status1;
	if (i2c_usb_pd_stusb4500_read_alert_status1(&alert_status1))
		i2c_usb_pd_stusb4500_print_alert_status1(&alert_status1);
	else
		PRINTF("Can't read alert status1.\r\n");

	union stusb4500_port_status_t port_status;
	if (i2c_usb_pd_stusb4500_read_port_status(&port_status))
		i2c_usb_pd_stusb4500_print_port_status(&port_status);
	else
		PRINTF("Can't read port status.\r\n");

	// i2c_usb_pd_stusb4500_port_status1();
	// i2c_usb_pd_stusb4500_read_status();
	// i2c_usb_pd_stusb4500_read_pdo_registers();
	// i2c_usb_pd_stusb4500_read_usb_pd_status();
	// i2c_usb_pd_stusb4500_read_rx_data();

	while (true)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	vTaskSuspend(NULL);
}

bool i2c_task_read_data(uint8_t *send, size_t send_size, uint8_t *received, size_t received_size)
{
	memcpy(i2c_buffor, send, send_size);

		/* write to I2C */
	masterXfer.direction = kI2C_Write;
	masterXfer.dataSize = 1;

	status_t status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during write transaction, 0x%x\r\n", status);
		return false;
	}

		/* read from I2C */
	masterXfer.direction = kI2C_Read;
	masterXfer.dataSize = received_size;

	status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during read transaction, 0x%x\r\n", status);
		return false;
	}

	memcpy(received, i2c_buffor, received_size);
	// *received = i2c_buffor[0];

	return true;
}

bool i2c_task_write_data(uint8_t *data, size_t data_size)
{
	memcpy(i2c_buffor, data, data_size);

		/* write to I2C */
	masterXfer.direction = kI2C_Write;
	masterXfer.dataSize = data_size;

	status_t status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during write transaction, 0x%x\r\n", status);
		return false;
	}

	return true;
}
