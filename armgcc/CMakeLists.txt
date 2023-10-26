# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
  message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()


# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(imx8mp_m7_i2c_usb_pd_stusb4500)

set(MCUX_BUILD_TYPES debug release ddr_debug ddr_release flash_debug flash_release)

set(MCUX_SDK_PROJECT_NAME imx8mp_m7_i2c_usb_pd_stusb4500.elf)

if (NOT DEFINED SdkRootDirPath)
	SET(SdkRootDirPath /opt/MCUXpresso_SDK_2_14_0_MIMX8ML8xxxLZ)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
	"${ProjDirPath}/../main.h"
	"${ProjDirPath}/../main.c"
	"${ProjDirPath}/../FreeRTOSConfig.h"
	"${ProjDirPath}/../board_cfg/pin_mux.c"
	"${ProjDirPath}/../board_cfg/pin_mux.h"
	"${ProjDirPath}/../board_cfg/board.c"
	"${ProjDirPath}/../board_cfg/board.h"
	"${ProjDirPath}/../board_cfg/clock_config.c"
	"${ProjDirPath}/../board_cfg/clock_config.h"
	"${ProjDirPath}/../board_cfg/fsl_iomuxc.h"
	"${ProjDirPath}/../board_cfg/empty_rsc_table.c"
	"${ProjDirPath}/../common.c"
	"${ProjDirPath}/../common.h"
	"${ProjDirPath}/../i2c_task.c"
	"${ProjDirPath}/../i2c_task.h"
	"${ProjDirPath}/../i2c_usb_pd_stusb4500.c"
	"${ProjDirPath}/../i2c_usb_pd_stusb4500.h"
	"${ProjDirPath}/../i2c_usb_pd_stusb4500_print.c"
	"${ProjDirPath}/../i2c_usb_pd_stusb4500_print.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
	${ProjDirPath}/..
)

set_source_files_properties("${ProjDirPath}/../FreeRTOSConfig.h" PROPERTIES COMPONENT_CONFIG_FILE "middleware_freertos-kernel_template")

include(${SdkRootDirPath}/devices/MIMX8ML8/all_lib_device.cmake)

# RPMsg modules
# include(middleware_multicore_rpmsg_lite.MIMX8ML8)
# include(middleware_multicore_rpmsg_lite_imx8mp_m7_freertos.MIMX8ML8)
# include(middleware_multicore_rpmsg_lite_freertos.MIMX8ML8)
# include(driver_mu.MIMX8ML8)
# include(driver_rdc.MIMX8ML8)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
	SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/imx8mp_m7_i2c_usb_pd_stusb4500.bin)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;${EXECUTABLE_OUTPUT_PATH}/imx8mp_m7_i2c_usb_pd_stusb4500.bin")

