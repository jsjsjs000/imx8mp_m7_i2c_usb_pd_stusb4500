#include <fsl_common.h>
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include "common.h"
#include "i2c_task.h"
#include "i2c_usb_pd_stusb4500.h"
#include "i2c_usb_pd_stusb4500_print.h"

void i2c_usb_pd_stusb4500_print_alert_status1(union stusb4500_alert_status1_t *alert_status1)
{
	PRINTF("Alert status1:\r\n");
	PRINTF("  prt status al = %d\r\n", alert_status1->alert_status1.prt_status_al);
	PRINTF("  pd typec status al = %d\r\n", alert_status1->alert_status1.pd_typec_status_al);
	PRINTF("  cc hw fault status al = %d\r\n", alert_status1->alert_status1.cc_hw_fault_status_al);
	PRINTF("  typec monitoring status al = %d\r\n", alert_status1->alert_status1.typec_monitoring_status_al);
	PRINTF("  port status al = %d\r\n", alert_status1->alert_status1.port_status_al);
}


void i2c_usb_pd_stusb4500_print_port_status(union stusb4500_port_status_t *port_status)
{
	PRINTF("Port status:\r\n");
	PRINTF("  attach trans = %d\r\n", port_status->port_status.attach_trans);
	PRINTF("  attach = %d\r\n", port_status->port_status.attach);
	PRINTF("  data mode = %d\r\n", port_status->port_status.data_mode);
	PRINTF("  power mode = %d\r\n", port_status->port_status.power_mode);
	PRINTF("  attached device = %d\r\n", port_status->port_status.attached_device);
};




void i2c_usb_pd_stusb4500_print_pdo_structure(union stusb4500_pdo_t *pdo)
{
	PRINTF("%d mA\r\n", pdo->pdo.operational_current_10ma * 10);
	PRINTF("%d mV\r\n", pdo->pdo.voltage_50mv * 50);
}

void i2c_usb_pd_stusb4500_print_usb_pd_status(union stusb4500_usb_pd_status_t *usb_pd_status)
{
	PRINTF("max %d mA\r\n", usb_pd_status->usb_pd_status.maximum_operating_current_10ma * 10);
	PRINTF("operating %d mA\r\n", usb_pd_status->usb_pd_status.operating_current_10ma * 10);
}

void i2c_usb_pd_stusb4500_print_fixed_supply_pdo_source_t(union stusb4500_fixed_supply_pdo_source_t *pdo)
{
	PRINTF("  maximum current %d mA\r\n", pdo->fixed_supply_pdo_source.maximum_current_10ma * 10);
	PRINTF("  voltage %d mV\r\n", pdo->fixed_supply_pdo_source.voltage_50mv * 50);
}

void i2c_usb_pd_stusb4500_print_variable_supply_pdo_source_t(union stusb4500_variable_supply_pdo_source_t *pdo)
{
	PRINTF("  maximum current %d mA\r\n", pdo->variable_supply_pdo_source.maximum_current_10ma * 10);
	PRINTF("  minimum voltage %d mV\r\n", pdo->variable_supply_pdo_source.minimum_voltage_50mv * 50);
	PRINTF("  maximum voltage %d mV\r\n", pdo->variable_supply_pdo_source.maximum_voltage_50mv * 50);
}

void i2c_usb_pd_stusb4500_print_battery_supply_pdo_source_t(union stusb4500_battery_supply_pdo_source_t *pdo)
{
	PRINTF("  maximum allowable power %d mW\r\n", pdo->battery_supply_pdo_source.maximum_allowable_power_250mw * 250);
	PRINTF("  minimum voltage %d mV\r\n", pdo->battery_supply_pdo_source.minimum_voltage_50mv * 50);
	PRINTF("  maximum voltage %d mV\r\n", pdo->battery_supply_pdo_source.maximum_voltage_50mv * 50);
}

void i2c_usb_pd_stusb4500_print_rx_data_structure(union stusb4500_rx_data_t *rx_data)
{
	if (rx_data->type == STUSB4500_PDO_FIXED)
	{
		PRINTF("type fixed\r\n");
		i2c_usb_pd_stusb4500_print_fixed_supply_pdo_source_t(
				(union stusb4500_fixed_supply_pdo_source_t*)rx_data);
	}
	else if (rx_data->type == STUSB4500_PDO_BATTERY)
	{
		PRINTF("type battery\r\n");
		i2c_usb_pd_stusb4500_print_variable_supply_pdo_source_t(
				(union stusb4500_variable_supply_pdo_source_t*)rx_data);
	}
	else if (rx_data->type == STUSB4500_PDO_VARIABLE_SUPPLY)
	{
		PRINTF("type variable supply\r\n");
		i2c_usb_pd_stusb4500_print_battery_supply_pdo_source_t(
				(union stusb4500_battery_supply_pdo_source_t*)rx_data);
	}
	else if (rx_data->type == STUSB4500_PDO_RESERVED)
	{
		PRINTF("type reserved\r\n");
	}
}
