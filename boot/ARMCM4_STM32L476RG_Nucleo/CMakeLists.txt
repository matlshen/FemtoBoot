cmake_minimum_required(VERSION 3.5)
########################################################################
# Toolchain file must go at the top
########################################################################
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../../common/arm-cm4.cmake)
# Choose between Debug and Release builds
set(CMAKE_BUILD_TYPE Debug)

########################################################################
# MCU information
# Edit this section based on the target platform
########################################################################
set(MCU_FAMILY STM32L4xx)
set(MCU_MODEL STM32L476xx)
set(MCU_PART STM32L476RGTx)

########################################################################
# Directory information
########################################################################
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
set(BOOTUTIL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../bootutil)

########################################################################
# Includes
########################################################################
include_directories(
    Core/Inc
    ${BOOTUTIL_DIR}/inc
    ${COMMON_DIR}/STM32L4xx_HAL_Driver/Inc
    ${COMMON_DIR}/STM32L4xx_HAL_Driver/Inc/Legacy
    ${COMMON_DIR}/CMSIS/Device/ST/STM32L4xx/Include
    ${COMMON_DIR}/CMSIS/Include
)

########################################################################
# Sources
########################################################################
file(GLOB PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.s
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c
    ${BOOTUTIL_DIR}/src/*.c
    ${COMMON_DIR}/STM32L4xx_HAL_Driver/Src/*.c
)
list(REMOVE_ITEM PROJECT_SOURCES ${COMMON_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_msp_template.c)
list(REMOVE_ITEM PROJECT_SOURCES ${COMMON_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_timebase_tim_template.c)

# ASM source files
set(ASM_SOURCES
    Core/Src/startup_stm32l476xx.s
)

########################################################################
# Executable build instructions
########################################################################
get_filename_component(SOURCE_DIR_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${SOURCE_DIR_NAME})

# Add executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${ASM_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE
    STM32L496xx
    USE_HAL_DRIVER
    USE_FULL_LL_DRIVER)

enable_language(ASM C)

# Linker script and libraries
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} \
    -specs=nano.specs \
    -T${CMAKE_CURRENT_SOURCE_DIR}/${MCU_PART}_FLASH.ld \
    -Wl,--gc-sections \
    -Wl,-Map=${PROJECT_NAME}.map,--cref \
    -Wl,--print-memory-usage"
)
target_link_libraries(${PROJECT_NAME} c m nosys)

# Post-build commands for generating binary and hex files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
)