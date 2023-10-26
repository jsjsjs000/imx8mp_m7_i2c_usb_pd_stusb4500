#define STUSB4500_BCD_TYPEC_REV_LOW          0x06
#define STUSB4500_BCD_TYPEC_REV_HIGH         0x07
#define STUSB4500_BCD_USBPD_REV_LOW          0x08
#define STUSB4500_BCD_USBPD_REV_HIGH         0x09
#define STUSB4500_DEVICE_CAPAB_HIGH          0x0A
#define STUSB4500_ALERT_STATUS_1             0x0B
#define STUSB4500_ALERT_STATUS_1_MASK        0x0C
#define STUSB4500_PORT_STATUS_0              0x0D
#define STUSB4500_PORT_STATUS_1              0x0E
#define STUSB4500_TYPEC_MONITORING_STATUS_0  0x0F
#define STUSB4500_TYPEC_MONITORING_STATUS_1  0x10
#define STUSB4500_CC_STATUS                  0x11
#define STUSB4500_CC_HW_FAULT_STATUS_0       0x12
#define STUSB4500_CC_HW_FAULT_STATUS_1       0x13
#define STUSB4500_PD_TYPEC_STATUS            0x14
#define STUSB4500_TYPEC_STATUS               0x15
#define STUSB4500_PRT_STATUS                 0x16
#define STUSB4500_PD_COMMAND_CTRL            0x1A
#define STUSB4500_MONITORING_CTRL_0          0x20
#define STUSB4500_MONITORING_CTRL_2          0x22
#define STUSB4500_RESET_CTRL                 0x23
#define STUSB4500_VBUS_DISCHARGE_TIME_CTRL   0x25
#define STUSB4500_VBUS_DISCHARGE_CTRL        0x26
#define STUSB4500_VBUS_CTRL                  0x27
#define STUSB4500_PE_FSM                     0x29
#define STUSB4500_GPIO_SW_GPIO               0x2D
#define STUSB4500_Device_ID                  0x2F
#define STUSB4500_RX_HEADER_LOW              0x31
#define STUSB4500_RX_HEADER_HIGH             0x32
#define STUSB4500_RX_DATA_OBJ1_0             0x33
#define STUSB4500_RX_DATA_OBJ1_1             0x34
#define STUSB4500_RX_DATA_OBJ1_2             0x35
#define STUSB4500_RX_DATA_OBJ1_3             0x36
#define STUSB4500_RX_DATA_OBJ2_0             0x37
#define STUSB4500_RX_DATA_OBJ2_1             0x38
#define STUSB4500_RX_DATA_OBJ2_2             0x39
#define STUSB4500_RX_DATA_OBJ2_3             0x3A
#define STUSB4500_RX_DATA_OBJ3_0             0x3B
#define STUSB4500_RX_DATA_OBJ3_1             0x3C
#define STUSB4500_RX_DATA_OBJ3_2             0x3D
#define STUSB4500_RX_DATA_OBJ3_3             0x3E
#define STUSB4500_RX_DATA_OBJ4_0             0x3F
#define STUSB4500_RX_DATA_OBJ4_1             0x40
#define STUSB4500_RX_DATA_OBJ4_2             0x41
#define STUSB4500_RX_DATA_OBJ4_3             0x42
#define STUSB4500_RX_DATA_OBJ5_0             0x43
#define STUSB4500_RX_DATA_OBJ5_1             0x44
#define STUSB4500_RX_DATA_OBJ5_2             0x45
#define STUSB4500_RX_DATA_OBJ5_3             0x46
#define STUSB4500_RX_DATA_OBJ6_0             0x47
#define STUSB4500_RX_DATA_OBJ6_1             0x48
#define STUSB4500_RX_DATA_OBJ6_2             0x49
#define STUSB4500_RX_DATA_OBJ6_3             0x4A
#define STUSB4500_RX_DATA_OBJ7_0             0x4B
#define STUSB4500_RX_DATA_OBJ7_1             0x4C
#define STUSB4500_RX_DATA_OBJ7_2             0x4D
#define STUSB4500_RX_DATA_OBJ7_3             0x4E
#define STUSB4500_TX_HEADER_LOW              0x51
#define STUSB4500_TX_HEADER_HIGH             0x52
#define STUSB4500_DPM_PDO_NUMB               0x70
#define STUSB4500_DPM_SNK_PDO1_0             0x85
#define STUSB4500_DPM_SNK_PDO1_1             0x86
#define STUSB4500_DPM_SNK_PDO1_2             0x87
#define STUSB4500_DPM_SNK_PDO1_3             0x88
#define STUSB4500_DPM_SNK_PDO2_0             0x89
#define STUSB4500_DPM_SNK_PDO2_1             0x8A
#define STUSB4500_DPM_SNK_PDO2_2             0x8B
#define STUSB4500_DPM_SNK_PDO2_3             0x8C
#define STUSB4500_DPM_SNK_PDO3_0             0x8D
#define STUSB4500_DPM_SNK_PDO3_1             0x8E
#define STUSB4500_DPM_SNK_PDO3_2             0x8F
#define STUSB4500_DPM_SNK_PDO3_3             0x90
#define STUSB4500_RDO_REG_STATUS_0           0x91
#define STUSB4500_RDO_REG_STATUS_1           0x92
#define STUSB4500_RDO_REG_STATUS_2           0x93
#define STUSB4500_RDO_REG_STATUS_3           0x94

#define STUSB4500_PDO_FIXED                  0
#define STUSB4500_PDO_BATTERY                1
#define STUSB4500_PDO_VARIABLE_SUPPLY        2
#define STUSB4500_PDO_RESERVED               3

union stusb4500_alert_status1_t
{
	uint8_t data;
	struct
	{
		uint32_t reserved1:1;
		uint32_t prt_status_al:1;
		uint32_t reserved2:1;
		uint32_t pd_typec_status_al:1;
		uint32_t cc_hw_fault_status_al:1;
		uint32_t typec_monitoring_status_al:1;
		uint32_t port_status_al:1;
		uint32_t reserved3:1;
	} alert_status1;
};

union stusb4500_port_status_t
{
	uint16_t data16;
	struct
	{
		uint32_t attach_trans:1;
		uint32_t reserved1:7;
		uint32_t attach:1;
		uint32_t reserved2:1;
		uint32_t data_mode:1;
		uint32_t power_mode:1;
		uint32_t reserved3:1;
		uint32_t attached_device:3;
	} port_status;
};





union stusb4500_pdo_t
{
	uint32_t data32;
	struct
	{
		uint32_t operational_current_10ma:10;  /// * 10 mA
		uint32_t voltage_50mv:10;              /// * 50 mV
		uint32_t reserved:3;
		uint32_t fast_role_swap:2;
		uint32_t dual_role_data:1;
		uint32_t usb_communication_capable:1;
		uint32_t unconstrained_capable:1;
		uint32_t higher_capability:1;
		uint32_t dual_role_power:1;
		uint32_t fixed_supply:2;
	} pdo;
};

union stusb4500_fixed_supply_pdo_source_t
{
	uint32_t data32;
	struct
	{
		uint32_t maximum_current_10ma:10;      /// * 10 mA
		uint32_t voltage_50mv:10;              /// * 50 mV
		uint32_t peak_current:2;
		uint32_t reserved:3;
		uint32_t dual_role_data:1;
		uint32_t usb_communication_capable:1;
		uint32_t externally_powered:1;
		uint32_t usb_suspend_supported:1;
		uint32_t dual_role_power:1;
		uint32_t fixed_supply:2;
	} fixed_supply_pdo_source;
};

union stusb4500_variable_supply_pdo_source_t
{
	uint32_t data32;
	struct
	{
		uint32_t maximum_current_10ma:10;      /// * 10 mA
		uint32_t minimum_voltage_50mv:10;      /// * 50 mV
		uint32_t maximum_voltage_50mv:10;      /// * 50 mV
		uint32_t variable_supply:2;
	} variable_supply_pdo_source;
};

union stusb4500_battery_supply_pdo_source_t
{
	uint32_t data32;
	struct
	{
		uint32_t maximum_allowable_power_250mw:10;  /// * 250 mW
		uint32_t minimum_voltage_50mv:10;           /// * 50 mV
		uint32_t maximum_voltage_50mv:10;           /// * 50 mV
		uint32_t battery:2;
	} battery_supply_pdo_source;
};

union stusb4500_usb_pd_status_t
{
	uint32_t data32;
	struct
	{
		uint32_t maximum_operating_current_10ma:10;       /// * 10 mA
		uint32_t operating_current_10ma:10;               /// * 10 mA
		uint32_t reserved1:3;
		uint32_t uncheked_extended_messages_supported:1;
		uint32_t no_usb_suspend:1;
		uint32_t usb_communications_capable:1;
		uint32_t capability_mismatch:1;
		uint32_t giveback_flag:1;
		uint32_t object_position:3;
		uint32_t reserved2:1;
	} usb_pd_status;
};

union stusb4500_rx_data_t
{
	uint32_t data32;
	struct
	{
		uint32_t reserved:30;
		uint32_t type:2;
	};
};

extern bool i2c_usb_pd_stusb4500_read_type_c_release_supported_by_device(uint16_t *type_c_release_supported_by_device);
extern bool i2c_usb_pd_stusb4500_read_power_delivery_release_supported_by_device(
		uint16_t *power_delivery_release_supported_by_device);
extern bool i2c_usb_pd_stusb4500_read_alert_status1(union stusb4500_alert_status1_t *alert_status1);
extern bool i2c_usb_pd_stusb4500_read_port_status(union stusb4500_port_status_t *port_status);



// extern bool i2c_usb_pd_stusb4500_port_status0(void);
// extern bool i2c_usb_pd_stusb4500_port_status1(void);
extern bool i2c_usb_pd_stusb4500_read_status(void);
extern bool i2c_usb_pd_stusb4500_read_pdo_registers(void);
extern bool i2c_usb_pd_stusb4500_read_usb_pd_status(void);
extern bool i2c_usb_pd_stusb4500_read_rx_data(void);
