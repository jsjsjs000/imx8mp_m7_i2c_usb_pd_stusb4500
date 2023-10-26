	SDK w /opt/MCUXpresso_SDK_2_14_0_MIMX8ML8xxxLZ/
Wygeneruj i pobierz SDK na:
# https://mcuxpresso.nxp.com/en/select
# https://www.nxp.com account: jsjsjs000@gmail.com, wCCR72B2aV@zZ8S
# Processors > i.MX > 8M Plus Quad > MIMX8ML8xxxLZ
# SDK v2.11.1, Build MCUXpresso SDK
# Download SDK > Download SDK archive including documentation
cd ~/Downloads
sudo mkdir -p /opt/MCUXpresso_SDK_2_14_0_MIMX8ML8xxxLZ
sudo tar -xf SDK_2_14_0_MIMX8ML8xxxLZ.tar.gz -C /opt/MCUXpresso_SDK_2_14_0_MIMX8ML8xxxLZ
cd /opt/MCUXpresso_SDK_2_14_0_MIMX8ML8xxxLZ
	# download phytec examples
sudo git clone https://git.phytec.de/phytec-mcux-boards -b SDK_2.13-phy

	Build prepare:
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi make cmake
export ARMGCC_DIR=/usr
echo $ARMGCC_DIR
echo export ARMGCC_DIR=/usr >> ~/.bashrc

	Enable peripherals in:
armgcc/config.cmake
	from:
/opt/MCUXpresso_SDK_2_14_0_MIMX8ML8xxxLZ/devices/MIMX8ML8/all_lib_device.cmake

	Build:
cd armgcc
	# Windows:
clean.bat
build_debug.bat
build_release.bat
	# Linux:
./clean.sh
./build_debug.sh
./build_release.sh
make # next builds
	# Visual Studio Code:
Ctrl+Shift+B - run Makefile

FreeRTOSConfig.h:
------------------------------------------------------------
#define configUSE_PREEMPTION                    1
#define configTICK_RATE_HZ                      ((TickType_t)1000)
------------------------------------------------------------

	Check stack overflow:
FreeRTOSConfig.h:
------------------------------------------------------------
configCHECK_FOR_STACK_OVERFLOW 1
------------------------------------------------------------
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
	PRINTF("\r\nError: stack overflow\r\n");
}
------------------------------------------------------------

	Advanced formating PRINTF() and floating points numbers in PRINTF() and sprintf():
armgcc/flags.cmake:
-------------------------- add ----------------------------
SET(CMAKE_ASM_FLAGS_DEBUG " \
		-Werror-implicit-function-declaration \
SET(CMAKE_C_FLAGS_DEBUG " \
		-Werror-implicit-function-declaration \
		-DPRINTF_FLOAT_ENABLE=1 \
		-DPRINTF_ADVANCED_ENABLE=1 \
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
		-Werror-implicit-function-declaration \
		-u _printf_float \

	# optional build only to assembler code:
# SET(CMAKE_C_FLAGS_DEBUG " \
# 		-fverbose-asm \
# 		-S \
------------------------------------------------------------

	Add user to dialout group - access to UART without root permission
sudo adduser $USER dialout
# logout

	Debug in UART1/2:
minicom -w -D /dev/ttyUSB0
minicom -w -D /dev/ttyUSB1
	Connect to Linux via ssh
ssh root@192.168.30.11

	Set TFTP server:
sudo nano /etc/xinetd.d/tftp
------------------------------------------------------------
	server_args = -s /home/p2119/jarsulk-pco/projects/SOD-5/Programs/m7/imx8mp_m7_i2c_usb_pd_stusb4500/armgcc/debug/
------------------------------------------------------------
sudo service xinetd restart

	Install AutoKey
sudo apt install autokey-gtk
	Configure shortcut Ctrl+Alt+Q
		Add new: TFTP in Terminal
			Command: tftp 0x48000000 imx8mp_m7_i2c_usb_pd_stusb4500.bin; cp.b 0x48000000 0x7e0000 0x20000; bootaux 0x7e0000
			Hotkey: Ctrl+Alt+Q
			Window Filter: gnome-terminal-server.Gnome-terminal
		Add new: minicom in Terminal
			Command: minicom -w -D /dev/ttyUSB
			Hotkey: Ctrl+Alt+M
			Window Filter: gnome-terminal-server.Gnome-terminal

	Download .bin file from TFTP server and run firmware on M7 core in U-boot:
tftp 0x48000000 imx8mp_m7_i2c_usb_pd_stusb4500.bin; cp.b 0x48000000 0x7e0000 0x20000; bootaux 0x7e0000
	or
# Press Ctrl+Alt+Q in minicom in Terminal

	Set autodownload M7 program by TFTP at startup in U-boot:
setenv boot_m7 'tftp 0x48000000 imx8mp_m7_i2c_usb_pd_stusb4500.bin; cp.b 0x48000000 0x7e0000 0x20000; bootaux 0x7e0000'
saveenv

	Set start program M7 from SD card
setenv boot_m7 'fatload mmc 1:1 0x48000000 imx8mp_m7_i2c_usb_pd_stusb4500.bin; cp.b 0x48000000 0x7e0000 0x20000; bootaux 0x7e0000'
saveenv

	Copy .bin program to SD card
cd ~/jarsulk-pco/projects/SOD-5/Programs/m7/sod5_switch_m7/armgcc
cp debug/sod5_switch_m7.bin /media/p2119/boot
sync; umount /media/p2119/boot

	Set U-boot to run M7 and hold in U-boot
setenv bootcmd run boot_m7
saveenv

	Set U-boot to run M7 and run Linux
setenv bootcmd 'run boot_m7; mmc dev ${mmcdev}; if mmc rescan; then env exists dofitboot || setenv dofitboot 0;env exists doraucboot || setenv doraucboot 0;run spiprobe; if test ${doraucboot} = 1; then run raucboot; elif run loadimage; then run mmcboot; else run netboot; fi; fi;'
saveenv

__NOP(); // No Operation
__WFI(); // Wait For Interrupt
__WFE(); // Wait For Event
__SEV(); // Send Event
