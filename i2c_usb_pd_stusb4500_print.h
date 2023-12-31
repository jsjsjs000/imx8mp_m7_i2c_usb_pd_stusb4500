extern void i2c_usb_pd_stusb4500_print_alert_status1(union stusb4500_alert_status1_t *alert_status1);
extern void i2c_usb_pd_stusb4500_print_port_status(union stusb4500_port_status_t *port_status);
extern void i2c_usb_pd_stusb4500_print_typec_monitoring_status(union stusb4500_typec_monitoring_status_t *mon_status);
extern void i2c_usb_pd_stusb4500_print_cc_status(union stusb4500_cc_status_t *cc_status);
extern void i2c_usb_pd_stusb4500_print_cc_hw_fault_status(union stusb4500_cc_hw_fault_status_t *cc_hw_fault_status);
extern void i2c_usb_pd_stusb4500_print_pd_typec_status(uint8_t *pd_typec_status);
extern void i2c_usb_pd_stusb4500_print_typec_status(union stusb4500_typec_status_t *typec_status);
extern void i2c_usb_pd_stusb4500_print_prt_status(union stusb4500_prt_status_t *prt_status);
extern void i2c_usb_pd_stusb4500_print_pd_command_ctrl_status(uint8_t *pd_command_ctrl_status);
extern void i2c_usb_pd_stusb4500_print_pe_fsm(enum stusb4500_pe_fsm *pe_fsm);
extern void i2c_usb_pd_stusb4500_print_gpio_sw(bool *gpio_sw);
extern void i2c_usb_pd_stusb4500_print_device_id(uint8_t *device_id);
extern void i2c_usb_pd_stusb4500_print_fixed_supply_pdo_source_t(union stusb4500_fixed_supply_pdo_source_t *pdo);
extern void i2c_usb_pd_stusb4500_print_variable_supply_pdo_source_t(union stusb4500_variable_supply_pdo_source_t *pdo);
extern void i2c_usb_pd_stusb4500_print_battery_supply_pdo_source_t(union stusb4500_battery_supply_pdo_source_t *pdo);
extern void i2c_usb_pd_stusb4500_print_rx_data_structure(uint8_t i, union stusb4500_rx_data_obj_t *rx_data);
extern void i2c_usb_pd_stusb4500_print_pdo_structure(uint8_t pdo_number, union stusb4500_pdo_t *pdo);
extern void i2c_usb_pd_stusb4500_print_usb_pd_status(union stusb4500_usb_pd_status_t *usb_pd_status);
