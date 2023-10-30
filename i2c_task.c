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

static void i2c_task_initialize_i2c(void);

void i2c_task_initialize(void)
{
	CLOCK_SetRootMux(I2C_STUSB4500_CLK_ROOT, I2C_STUSB4500_ROOT_MUX_SYS_PLL_DIV); /* Set I2C source to SysPLL1 Div5 160MHZ */
	CLOCK_SetRootDivider(I2C_STUSB4500_CLK_ROOT, 1U, 10U);                   /* Set root clock to 160MHZ / 10 = 16MHZ */
	NVIC_SetPriority(I2C_STUSB4500_IRQN, 3);

	i2c_task_initialize_i2c();
}

static void i2c_task_initialize_i2c(void)
{
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
	PRINTF("I2C task started.\r\n\r\n");
	vTaskDelay(pdMS_TO_TICKS(500));

		/// Read Type-C release supported by device
	uint16_t type_c_release_supported_by_device;
	if (i2c_usb_pd_stusb4500_read_type_c_release_supported_by_device(&type_c_release_supported_by_device))
		PRINTF("Type-C release supported by device = %d\r\n", type_c_release_supported_by_device);
	else
		PRINTF("Can't read Type-C release supported by device.\r\n");

		/// Read power delivery release supported by device
	uint16_t power_delivery_release_supported_by_device;
	if (i2c_usb_pd_stusb4500_read_power_delivery_release_supported_by_device(&power_delivery_release_supported_by_device))
		PRINTF("Power Delivery release supported by device = %d.%d\r\n",
				power_delivery_release_supported_by_device >> 8, power_delivery_release_supported_by_device & 0xff);
	else
		PRINTF("Can't read power delivery release supported by device.\r\n");

		/// Read alert status
	union stusb4500_alert_status1_t alert_status1;
	if (i2c_usb_pd_stusb4500_read_alert_status1(&alert_status1))
		i2c_usb_pd_stusb4500_print_alert_status1(&alert_status1);
	else
		PRINTF("Can't read alert status1.\r\n");

		/// Read port status
	union stusb4500_port_status_t port_status;
	if (i2c_usb_pd_stusb4500_read_port_status(&port_status))
		i2c_usb_pd_stusb4500_print_port_status(&port_status);
	else
		PRINTF("Can't read port status.\r\n");

		/// Read Type-C monitoring status
	union stusb4500_typec_monitoring_status_t typec_monitoring_status;
	if (i2c_usb_pd_stusb4500_read_typec_monitoring_status(&typec_monitoring_status))
		i2c_usb_pd_stusb4500_print_typec_monitoring_status(&typec_monitoring_status);
	else
		PRINTF("Can't read Type-C monitoring status.\r\n");

		/// Read CC status
	union stusb4500_cc_status_t cc_status;
	if (i2c_usb_pd_stusb4500_read_cc_status(&cc_status))
		i2c_usb_pd_stusb4500_print_cc_status(&cc_status);
	else
		PRINTF("Can't read CC status.\r\n");

		/// Read CC HW fault status
	union stusb4500_cc_hw_fault_status_t cc_hw_fault_status;
	if (i2c_usb_pd_stusb4500_read_cc_hw_fault_status(&cc_hw_fault_status))
		i2c_usb_pd_stusb4500_print_cc_hw_fault_status(&cc_hw_fault_status);
	else
		PRINTF("Can't read HW fault status.\r\n");

		/// Read PD Type-C status
	uint8_t pd_typec_status;
	if (i2c_usb_pd_stusb4500_read_pd_typec_status(&pd_typec_status))
		i2c_usb_pd_stusb4500_print_pd_typec_status(&pd_typec_status);
	else
		PRINTF("Can't read PD Type-C status.\r\n");

		/// Read Type-C status
	union stusb4500_typec_status_t typec_status;
	if (i2c_usb_pd_stusb4500_read_typec_status(&typec_status))
		i2c_usb_pd_stusb4500_print_typec_status(&typec_status);
	else
		PRINTF("Can't read Type-C status.\r\n");

		/// Read PRT status
	union stusb4500_prt_status_t prt_status;
	if (i2c_usb_pd_stusb4500_read_prt_status(&prt_status))
		i2c_usb_pd_stusb4500_print_prt_status(&prt_status);
	else
		PRINTF("Can't read PRT status.\r\n");

		/// Read PD command CTRL status
	uint8_t pd_command_ctrl_status;
	if (i2c_usb_pd_stusb4500_read_pd_command_ctrl_status(&pd_command_ctrl_status))
		i2c_usb_pd_stusb4500_print_pd_command_ctrl_status(&pd_command_ctrl_status);
	else
		PRINTF("Can't read command CTRL status.\r\n");

		/// Read PE FSM
	enum stusb4500_pe_fsm pe_fsm;
	if (i2c_usb_pd_stusb4500_read_pe_fsm(&pe_fsm))
		i2c_usb_pd_stusb4500_print_pe_fsm(&pe_fsm);
	else
		PRINTF("Can't read PE FSM.\r\n");

		/// Read GPIO SW
	bool gpio_sw;
	if (i2c_usb_pd_stusb4500_read_gpio_sw(&gpio_sw))
		i2c_usb_pd_stusb4500_print_gpio_sw(&gpio_sw);
	else
		PRINTF("Can't read GPIO SW.\r\n");

		/// Read device id
	uint8_t device_id;
	if (i2c_usb_pd_stusb4500_read_device_id(&device_id))
		i2c_usb_pd_stusb4500_print_device_id(&device_id);
	else
		PRINTF("Can't read device id.\r\n");

		/// Write PDO - 20V/5A - imposible current limitation, so change to 15V
	union stusb4500_pdo_t pdo =
	{
		.pdo.operational_current_10ma = 5000 / 10,  /// 5A
		.pdo.voltage_50mv = 20000 / 50,             /// 20V
		.pdo.fast_role_swap = 0,
		.pdo.dual_role_data = 0,
		.pdo.usb_communication_capable = 0,
		.pdo.unconstrained_power = 0,
		.pdo.higher_capability = 0,
		.pdo.dual_role_power = 0,
		.pdo.fixed_supply = stusb4500_pdo_type_fixed,
	};

	if (i2c_usb_pd_stusb4500_write_pdo_register(3, &pdo))
		PRINTF("Wrote PDO ok.\r\n");
	else
		PRINTF("Can't write PDO.\r\n");

		/// Reset and renegotiation PD
	if (i2c_usb_pd_stusb4500_write_reset())
		PRINTF("Send reset ok.\r\n");
	else
		PRINTF("Can't send reset.\r\n");

		/// Wait 1s after reset
	vTaskDelay(pdMS_TO_TICKS(1000));

		/// Read PDO numbers
	uint8_t pdo_numb;
	if (i2c_usb_pd_stusb4500_read_pdo_numb(&pdo_numb))
		PRINTF("PDO's count = %d\r\n", pdo_numb);
	else
		PRINTF("Can't read PDO number.\r\n");

		/// Read 3 PDO's
	union stusb4500_pdo_t pdo1, pdo2, pdo3;
	if (i2c_usb_pd_stusb4500_read_pdo_registers(&pdo1, &pdo2, &pdo3))
	{
		if (pdo_numb >= 1)
			i2c_usb_pd_stusb4500_print_pdo_structure(1, &pdo1);
		if (pdo_numb >= 2)
			i2c_usb_pd_stusb4500_print_pdo_structure(2, &pdo2);
		if (pdo_numb >= 3)
			i2c_usb_pd_stusb4500_print_pdo_structure(3, &pdo3);
	}
	else
		PRINTF("Can't read PDO's.\r\n");

		/// Read PD status
	union stusb4500_usb_pd_status_t usb_pd_status;
	bool usb_pd_status_ok = i2c_usb_pd_stusb4500_read_usb_pd_status(&usb_pd_status);
	if (usb_pd_status_ok)
		i2c_usb_pd_stusb4500_print_usb_pd_status(&usb_pd_status);
	else
		PRINTF("Can't read USB PD status.\r\n");

		/// Read RX data objects
	union stusb4500_rx_data_obj_t rx_data[7] = { 0 };
	bool rx_data_obj_ok = i2c_usb_pd_stusb4500_read_rx_data_obj(rx_data);
	if (rx_data_obj_ok)
	{
		for (int i = 0; i < 7; i++)
			i2c_usb_pd_stusb4500_print_rx_data_structure(i, &rx_data[i]);
	}
	else
		PRINTF("Can't read RX data object.\r\n");

		/// Display selected PDO
	if (usb_pd_status_ok && rx_data_obj_ok && usb_pd_status.usb_pd_status.object_position > 0)
	{
		PRINTF("\r\nSelected PDO:\r\n");
		uint8_t i = usb_pd_status.usb_pd_status.object_position - 1;
		i2c_usb_pd_stusb4500_print_rx_data_structure(i, &rx_data[i]);
	}
	else
		PRINTF("\r\nError: PDO is not selected.\r\n");

	while (true)
	{
		vTaskDelay(pdMS_TO_TICKS(500));

		union stusb4500_usb_pd_status_t usb_pd_status;
		bool usb_pd_status_ok = i2c_usb_pd_stusb4500_read_usb_pd_status(&usb_pd_status);
		if (usb_pd_status_ok)
			i2c_usb_pd_stusb4500_print_usb_pd_status(&usb_pd_status);
		else
			PRINTF("Can't read USB PD status.\r\n");
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
		vTaskDelay(pdMS_TO_TICKS(100));
		i2c_task_initialize_i2c();
		return false;
	}

		/* read from I2C */
	masterXfer.direction = kI2C_Read;
	masterXfer.dataSize = received_size;

	status = I2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
	if (status != kStatus_Success)
	{
		PRINTF("I2C master: error during read transaction, 0x%x\r\n", status);
		vTaskDelay(pdMS_TO_TICKS(100));
		i2c_task_initialize_i2c();
		return false;
	}

	memcpy(received, i2c_buffor, received_size);

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
		vTaskDelay(pdMS_TO_TICKS(100));
		i2c_task_initialize_i2c();
		return false;
	}

	return true;
}
