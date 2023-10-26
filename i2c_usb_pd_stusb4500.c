#include <fsl_common.h>
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include "common.h"
#include "i2c_task.h"
#include "i2c_usb_pd_stusb4500.h"
#include "i2c_usb_pd_stusb4500_print.h"

static bool i2c_usb_pd_stusb4500_read_register(uint8_t reg, uint8_t *received)
{
	uint8_t send[] = { reg };
	return i2c_task_read_data(send, sizeof(send), received, 1);
}

static bool i2c_usb_pd_stusb4500_read_2_registers(uint8_t reg, uint16_t *received)
{
	uint8_t send[] = { reg };
	uint8_t read[2];
	if (!i2c_task_read_data(send, sizeof(send), read, sizeof(uint16_t)))
		return false;

	*received = UINT16_FROM_LE_BYTES(read[0], read[1]);
	return true;
}

static bool i2c_usb_pd_stusb4500_read_4_registers(uint8_t reg, uint32_t *received)
{
	uint8_t send[] = { reg };
	uint8_t read[4];
	if (!i2c_task_read_data(send, sizeof(send), read, sizeof(uint32_t)))
		return false;

	*received = UINT32_FROM_LE_BYTES(read[0], read[1], read[2], read[3]);
	return true;
}

// static bool i2c_usb_pd_stusb4500_write_register(uint8_t reg, uint8_t value)
// {
// 	uint8_t data[] = { reg, value };
// 	return i2c_task_write_data(data, sizeof(data));
// }

bool i2c_usb_pd_stusb4500_read_type_c_release_supported_by_device(uint16_t *type_c_release_supported_by_device)
{
	return i2c_usb_pd_stusb4500_read_2_registers(STUSB4500_BCD_TYPEC_REV_LOW, type_c_release_supported_by_device);
}

bool i2c_usb_pd_stusb4500_read_power_delivery_release_supported_by_device(
		uint16_t *power_delivery_release_supported_by_device)
{
	return i2c_usb_pd_stusb4500_read_2_registers(STUSB4500_BCD_USBPD_REV_LOW,
			power_delivery_release_supported_by_device);
}

bool i2c_usb_pd_stusb4500_read_alert_status1(union stusb4500_alert_status1_t *alert_status1)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_BCD_USBPD_REV_LOW, &alert_status1->data);
}

bool i2c_usb_pd_stusb4500_read_port_status(union stusb4500_port_status_t *port_status)
{
	return i2c_usb_pd_stusb4500_read_2_registers(STUSB4500_PORT_STATUS_0, &port_status->data16);
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

bool i2c_usb_pd_stusb4500_read_pdo_registers(void)
{
	union stusb4500_pdo_t pdo = { .data32 = 0 };

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_DPM_SNK_PDO1_0, &pdo.data32))
		return false;

PRINTF("PDO1 = 0x%x\r\n", pdo.data32);
i2c_usb_pd_stusb4500_print_pdo_structure(&pdo);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_DPM_SNK_PDO2_0, &pdo.data32))
		return false;

PRINTF("PDO2 = 0x%x\r\n", pdo.data32);
i2c_usb_pd_stusb4500_print_pdo_structure(&pdo);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_DPM_SNK_PDO3_0, &pdo.data32))
		return false;

PRINTF("PDO3 = 0x%x\r\n", pdo.data32);
i2c_usb_pd_stusb4500_print_pdo_structure(&pdo);

	return true;
}

bool i2c_usb_pd_stusb4500_read_usb_pd_status(void)
{
	union stusb4500_usb_pd_status_t usb_pd_status = { .data32 = 0 };
	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RDO_REG_STATUS_0, &usb_pd_status.data32))
		return false;

PRINTF("PD status = 0x%x\r\n", usb_pd_status.data32);
i2c_usb_pd_stusb4500_print_usb_pd_status(&usb_pd_status);

	return true;
}

bool i2c_usb_pd_stusb4500_read_rx_data(void)
{
	union stusb4500_rx_data_t rx_data = { .data32 = 0 };

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ1_0, &rx_data.data32))
		return false;

// PRINTF("RX data obj 1 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ2_0, &rx_data.data32))
		return false;

// PRINTF("RX data obj 2 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ3_0, &rx_data.data32))
		return false;
// PRINTF("RX data obj 3 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ4_0, &rx_data.data32))
		return false;

// PRINTF("RX data obj 4 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ5_0, &rx_data.data32))
		return false;

// PRINTF("RX data obj 5 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ6_0, &rx_data.data32))
		return false;

// PRINTF("RX data obj 6 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ7_0, &rx_data.data32))
		return false;

// PRINTF("RX data obj 7 = 0x%x\r\n", rx_data.data32);
i2c_usb_pd_stusb4500_print_rx_data_structure(&rx_data);

	return true;
}

/*
	UM2650 The STUSB4500 software programming guide
	https://www.st.com/resource/en/user_manual/um2650-the-stusb4500-software-programing-guide-stmicroelectronics.pdf

	to do:
		- przy resecie I2C się zawiesza na zawsze
*/
