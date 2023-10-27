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

bool i2c_usb_pd_stusb4500_read_typec_monitoring_status(union stusb4500_typec_monitoring_status_t *mon_status)
{
	return i2c_usb_pd_stusb4500_read_2_registers(STUSB4500_TYPEC_MONITORING_STATUS_0, &mon_status->data16);
}

bool i2c_usb_pd_stusb4500_read_cc_status(union stusb4500_cc_status_t *cc_status)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_CC_STATUS, &cc_status->data);
}

bool i2c_usb_pd_stusb4500_read_cc_hw_fault_status(union stusb4500_cc_hw_fault_status_t *cc_hw_fault_status)
{
	return i2c_usb_pd_stusb4500_read_2_registers(STUSB4500_CC_HW_FAULT_STATUS_0, &cc_hw_fault_status->data16);
}

bool i2c_usb_pd_stusb4500_read_pd_typec_status(uint8_t *pd_typec_status)
{
	uint8_t a;
	if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_PD_TYPEC_STATUS, &a))
		return false;
	
	*pd_typec_status = a & 0x0f;
	return true;
}

bool i2c_usb_pd_stusb4500_read_typec_status(union stusb4500_typec_status_t *typec_status)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_TYPEC_STATUS, &typec_status->data);
}

bool i2c_usb_pd_stusb4500_read_prt_status(union stusb4500_prt_status_t *prt_status)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_PRT_STATUS, &prt_status->data);
}

bool i2c_usb_pd_stusb4500_read_pd_command_ctrl_status(uint8_t *pd_command_ctrl_status)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_PD_COMMAND_CTRL, pd_command_ctrl_status);
}

bool i2c_usb_pd_stusb4500_read_pe_fsm(enum stusb4500_pe_fsm *pe_fsm)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_PE_FSM, pe_fsm);
}

bool i2c_usb_pd_stusb4500_read_gpio_sw(bool *gpio_sw)
{
	uint8_t a = 0;
	if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_GPIO_SW_GPIO, &a))
		return false;
	
	*gpio_sw = a & 0x1;
	return true;
}

bool i2c_usb_pd_stusb4500_read_device_id(uint8_t *device_id)
{
	return i2c_usb_pd_stusb4500_read_register(STUSB4500_DEVICE_ID, device_id);
}

bool i2c_usb_pd_stusb4500_read_rx_data_obj(union stusb4500_rx_data_obj_t **rx_data) /// 7 items
{
	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ1_0, &rx_data[0]->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ2_0, &rx_data[1]->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ3_0, &rx_data[2]->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ4_0, &rx_data[3]->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ5_0, &rx_data[4]->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ6_0, &rx_data[5]->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RX_DATA_OBJ7_0, &rx_data[6]->data32))
		return false;

	return true;
}

bool i2c_usb_pd_stusb4500_read_pdo_numb(uint8_t *pdo_numb)
{
	uint8_t a = 0;
	if (!i2c_usb_pd_stusb4500_read_register(STUSB4500_DPM_PDO_NUMB, &a))
		return false;

	*pdo_numb = a;
	return true;
}

bool i2c_usb_pd_stusb4500_read_pdo_registers(union stusb4500_pdo_t *pdo1, union stusb4500_pdo_t *pdo2,
		union stusb4500_pdo_t *pdo3)
{
	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_DPM_SNK_PDO1_0, &pdo1->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_DPM_SNK_PDO2_0, &pdo2->data32))
		return false;

	if (!i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_DPM_SNK_PDO3_0, &pdo3->data32))
		return false;

	return true;
}

bool i2c_usb_pd_stusb4500_read_usb_pd_status(union stusb4500_usb_pd_status_t *usb_pd_status)
{
	return i2c_usb_pd_stusb4500_read_4_registers(STUSB4500_RDO_REG_STATUS_0, &usb_pd_status->data32);
}

/*
	UM2650 The STUSB4500 software programming guide
	https://www.st.com/resource/en/user_manual/um2650-the-stusb4500-software-programing-guide-stmicroelectronics.pdf

	USB PD Power Negotiations
	https://www.ti.com/lit/an/slva842/slva842.pdf

	https://ww1.microchip.com/downloads/en/appnotes/00001953a.pdf
	https://www.st.com/content/dam/AME/2019/technology-tour-2019/chicago/presentations/T1S3_Schaumburg_USB-Type-C_G.Gosciniak.pdf
	https://blog.teledynelecroy.com/2016/01/a-look-at-usb-type-c-and-power-delivery.html
	https://blog.teledynelecroy.com/2016/05/usb-type-c-and-power-delivery-messaging.html
	https://www.embedded.com/usb-type-c-and-power-delivery-101-ports-and-connections
	https://www.embedded.com/usb-type-c-and-power-delivery-101-power-delivery-protocol

	to do:
		- przy resecie I2C się zawiesza na zawsze
*/
