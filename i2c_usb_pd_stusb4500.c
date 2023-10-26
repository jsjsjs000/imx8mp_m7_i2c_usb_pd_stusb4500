#include <fsl_common.h>
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include "i2c_task.h"
#include "i2c_usb_pd_stusb4500.h"

static bool i2c_usb_pd_stusb4500_read_register(uint8_t reg, uint8_t *received)
{
	uint8_t data[] = { reg };
	return i2c_task_read_data(data, sizeof(data), received, 1);
}

// static bool i2c_usb_pd_stusb4500_write_register(uint8_t reg, uint8_t value)
// {
// 	uint8_t data[] = { reg, value };
// 	return i2c_task_write_data(data, sizeof(data));
// }

bool i2c_usb_pd_stusb4500_port_status0(void)
{
	uint8_t data;
	if (i2c_usb_pd_stusb4500_read_register(STUSB4500_PORT_STATUS_0, &data))
		PRINTF("STUSB4500_PORT_STATUS_0 0x%x\r\n", data);
	else
		PRINTF("can't read register\r\n");

	return true;
}

bool i2c_usb_pd_stusb4500_port_status1(void)
{
	uint8_t data;
	if (i2c_usb_pd_stusb4500_read_register(STUSB4500_PORT_STATUS_1, &data))
		PRINTF("STUSB4500_PORT_STATUS_1 0x%x\r\n", data);
	else
		PRINTF("can't read register\r\n");

	return true;
}

bool i2c_usb_pd_stusb4500_read_status(void)
{
	uint8_t data;
	if (i2c_usb_pd_stusb4500_read_register(STUSB4500_CC_STATUS, &data))
		PRINTF("STUSB4500_CC_STATUS 0x%x\r\n", data);
	else
		PRINTF("can't read register\r\n");

	return true;
}

void i2c_usb_pd_stusb4500_print_pdo_structure(union i2c_usb_pd_stusb4500_pdo_t *pdo)
{
	PRINTF("%d mA\r\n", pdo->pdo.operational_current_mA_units * 10);
	PRINTF("%d mV\r\n", pdo->pdo.voltage_mV_units * 50);
}

void i2c_usb_pd_stusb4500_print_usb_pd_status(union i2c_usb_pd_stusb4500_usb_pd_status_t *usb_pd_status)
{
	PRINTF("max %d mA\r\n", usb_pd_status->usb_pd_status.maximum_operating_current_units * 10);
	PRINTF("operating %d mA\r\n", usb_pd_status->usb_pd_status.operating_current_units * 10);
}

bool i2c_usb_pd_stusb4500_read_pdo_registers(void)
{
	uint8_t data;
	union i2c_usb_pd_stusb4500_pdo_t pdo = { .data32 = 0 };
	for (int i = 0; i <= 3; i++)
	{
		if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_DPM_SNK_PDO1_0 + i, &data))
			return false;

		pdo.data32 |= data << (i * 8);
	}
PRINTF("PDO1 = 0x%x\r\n", pdo.data32);
i2c_usb_pd_stusb4500_print_pdo_structure(&pdo);

	pdo.data32 = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_DPM_SNK_PDO2_0 + i, &data))
			return false;

		pdo.data32 |= data << (i * 8);
	}
PRINTF("PDO2 = 0x%x\r\n", pdo.data32);
i2c_usb_pd_stusb4500_print_pdo_structure(&pdo);

	pdo.data32 = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_DPM_SNK_PDO3_0 + i, &data))
			return false;

		pdo.data32 |= data << (i * 8);
	}
PRINTF("PDO3 = 0x%x\r\n", pdo.data32);
i2c_usb_pd_stusb4500_print_pdo_structure(&pdo);

// $$ wpakować w 3 struktury 32 bity - strona 3
// PRINTF("pdo ok\r\n");

	return true;
}

bool i2c_usb_pd_stusb4500_read_usb_pd_status(void)
{
	uint8_t data;
	union i2c_usb_pd_stusb4500_usb_pd_status_t usb_pd_status = { .data32 = 0 };
	for (int i = 0; i <= 3; i++)
	{
		if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_RX_DATA_OBJ1_0 + i, &data))
			return false;

		usb_pd_status.data32 |= data << (i * 8);
	}
PRINTF("PD status 1 = 0x%x\r\n", usb_pd_status.data32);
i2c_usb_pd_stusb4500_print_usb_pd_status(&usb_pd_status);

	return true;
}

/*
	UM2650 The STUSB4500 software programming guide
	https://www.st.com/resource/en/user_manual/um2650-the-stusb4500-software-programing-guide-stmicroelectronics.pdf

	to do:
		- przy resecie I2C się zawiesza na zawsze
*/
