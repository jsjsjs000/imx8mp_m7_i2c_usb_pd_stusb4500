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
	PRINTF("  prt status alart = %d\r\n", alert_status1->alert_status1.prt_status_al);
	PRINTF("  pd typec status alart = %d\r\n", alert_status1->alert_status1.pd_typec_status_al);
	PRINTF("  cc hw fault status alart = %d\r\n", alert_status1->alert_status1.cc_hw_fault_status_al);
	PRINTF("  typec monitoring status alart = %d\r\n", alert_status1->alert_status1.typec_monitoring_status_al);
	PRINTF("  port status alart = %d\r\n", alert_status1->alert_status1.port_status_al);
}


void i2c_usb_pd_stusb4500_print_port_status(union stusb4500_port_status_t *port_status)
{
	PRINTF("Port status:\r\n");
	PRINTF("  attach trans = %d\r\n", port_status->port_status.attach_trans);
	PRINTF("  attach = %d\r\n", port_status->port_status.attach);
	PRINTF("  data mode = %d\r\n", port_status->port_status.data_mode);
	PRINTF("  power mode = %d\r\n", port_status->port_status.power_mode);
	PRINTF("  attached device = ");
	switch (port_status->port_status.attached_device)
	{
		case stusb4500_none_att: PRINTF("stusb4500_none_att\r\n"); break;
		case stusb4500_snk_att:  PRINTF("stusb4500_snk_att\r\n"); break;
		case stusb4500_dbg_att:  PRINTF("stusb4500_dbg_att\r\n"); break;
		default:                 PRINTF("reserved\r\n");
	}
};

void i2c_usb_pd_stusb4500_print_typec_monitoring_status(union stusb4500_typec_monitoring_status_t *mon_status)
{
	PRINTF("Type-C monitoring status:\r\n");
	PRINTF("  vbus valid snk trans = %d\r\n", mon_status->mon_status.vbus_valid_snk_trans);
	PRINTF("  vbus vsafe0v trans = %d\r\n", mon_status->mon_status.vbus_vsafe0v_trans);
	PRINTF("  vbus ready trans = %d\r\n", mon_status->mon_status.vbus_ready_trans);
	PRINTF("  vbus low status = %d\r\n", mon_status->mon_status.vbus_low_status);
	PRINTF("  vbus high status = %d\r\n", mon_status->mon_status.vbus_high_status);
	PRINTF("  vbus valid snk = %d\r\n", mon_status->mon_status.vbus_valid_snk);
	PRINTF("  vbus vsafe0v = %d\r\n", mon_status->mon_status.vbus_vsafe0v);
	PRINTF("  vbus ready = %d\r\n", mon_status->mon_status.vbus_ready);
}

void i2c_usb_pd_stusb4500_print_cc_status(union stusb4500_cc_status_t *cc_status)
{
	PRINTF("CC status:\r\n");
	PRINTF("  CC1 state = ");
	switch (cc_status->cc_status.cc1_state)
	{
		case stusb4500_cc_state_snk_default:  PRINTF("default\r\n"); break;
		case stusb4500_cc_state_snk_power1_5: PRINTF("power 1.5\r\n"); break;
		case stusb4500_cc_state_snk_power3_0: PRINTF("power 3.0\r\n"); break;
		default:                              PRINTF("reserved\r\n");
	}
	PRINTF("  CC2 state = ");
	switch (cc_status->cc_status.cc2_state)
	{
		case stusb4500_cc_state_snk_default:  PRINTF("default\r\n"); break;
		case stusb4500_cc_state_snk_power1_5: PRINTF("power 1.5\r\n"); break;
		case stusb4500_cc_state_snk_power3_0: PRINTF("power 3.0\r\n"); break;
		default:                              PRINTF("reserved\r\n");
	}
	PRINTF("  connect result = %d\r\n", cc_status->cc_status.connect_result);
	PRINTF("  looking 4 connection = %d\r\n", cc_status->cc_status.looking_4_connection);
}

void i2c_usb_pd_stusb4500_print_cc_hw_fault_status(union stusb4500_cc_hw_fault_status_t *cc_hw_fault_status)
{
	PRINTF("HW fault status:\r\n");
	PRINTF("  vpu valid trans = %d\r\n", cc_hw_fault_status->cc_hw_fault_status.vpu_valid_trans);
	PRINTF("  vpu ovp fault trans = %d\r\n", cc_hw_fault_status->cc_hw_fault_status.vpu_ovp_fault_trans);
	PRINTF("  vbus disch fault = %d\r\n", cc_hw_fault_status->cc_hw_fault_status.vbus_disch_fault);
	PRINTF("  vpu valid = %d\r\n", cc_hw_fault_status->cc_hw_fault_status.vpu_valid);
	PRINTF("  vpu ovp fault  = %d\r\n", cc_hw_fault_status->cc_hw_fault_status.vpu_ovp_fault);
}

void i2c_usb_pd_stusb4500_print_pd_typec_status(uint8_t *pd_typec_status)
{
	PRINTF("PD type-C status = ");
	switch (*pd_typec_status)
	{
		case 0x0: PRINTF("cleared\r\n"); break;
		case 0x8: PRINTF("pd hard reset complete ack\r\n"); break;
		case 0xe: PRINTF("pd hard reset received ack\r\n"); break;
		case 0xf: PRINTF("pd hard reset send ack\r\n"); break;
		default:  PRINTF("reserved\r\n");
	}
}

void i2c_usb_pd_stusb4500_print_typec_status(union stusb4500_typec_status_t *typec_status)
{
	PRINTF("Type-C status:\r\n");
	switch (typec_status->typec_status.typec_fsm_state)
	{
		case 0x00: PRINTF("unattached snk\r\n"); break;
		case 0x01: PRINTF("attachwait snk\r\n"); break;
		case 0x02: PRINTF("attached snk\r\n"); break;
		case 0x03: PRINTF("debug accessory snk\r\n"); break;
		case 0x0c: PRINTF("try src\r\n"); break;
		case 0x0d: PRINTF("unattached accessory\r\n"); break;
		case 0x0e: PRINTF("attachwait accessory\r\n"); break;
		case 0x13: PRINTF("typec error recovery\r\n"); break;
	}
	PRINTF("  reverse = %d\r\n", typec_status->typec_status.reverse);
}

void i2c_usb_pd_stusb4500_print_prt_status(union stusb4500_prt_status_t *prt_status)
{

}

void i2c_usb_pd_stusb4500_print_pd_command_ctrl_status(uint8_t *pd_command_ctrl_status)
{

}

void i2c_usb_pd_stusb4500_print_vbus_ctrl(bool *vbus_ctrl)
{

}

void i2c_usb_pd_stusb4500_print_pe_fsm(enum stusb4500_pe_fsm *pe_fsm)
{

}

void i2c_usb_pd_stusb4500_print_gpio_sw(bool *gpio_sw)
{

}

void i2c_usb_pd_stusb4500_print_device_id(uint8_t *device_id)
{

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

void i2c_usb_pd_stusb4500_print_rx_data_structure(union stusb4500_rx_data_obj_t *rx_data)
{
	if (rx_data->type == stusb4500_pdo_type_fixed)
	{
		PRINTF("type fixed\r\n");
		i2c_usb_pd_stusb4500_print_fixed_supply_pdo_source_t(
				(union stusb4500_fixed_supply_pdo_source_t*)rx_data);
	}
	else if (rx_data->type == stusb4500_pdo_type_battery)
	{
		PRINTF("type battery\r\n");
		i2c_usb_pd_stusb4500_print_variable_supply_pdo_source_t(
				(union stusb4500_variable_supply_pdo_source_t*)rx_data);
	}
	else if (rx_data->type == stusb4500_pdo_type_variable_supply)
	{
		PRINTF("type variable supply\r\n");
		i2c_usb_pd_stusb4500_print_battery_supply_pdo_source_t(
				(union stusb4500_battery_supply_pdo_source_t*)rx_data);
	}
	else if (rx_data->type == stusb4500_pdo_type_reserved)
	{
		PRINTF("type reserved\r\n");
	}
}

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
