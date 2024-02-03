cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Debug)

########################################################################
# Directory information
########################################################################
set(BOOTUTIL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bootutil)

########################################################################
# Includes
########################################################################
include_directories(
    Core/Inc
    ${BOOTUTIL_DIR}/inc
)

########################################################################
# Sources
########################################################################
file(GLOB PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.cpp
    ${BOOTUTIL_DIR}/src/*.c
)

########################################################################
# Executable build instructions
########################################################################
get_filename_component(SOURCE_DIR_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${SOURCE_DIR_NAME})

# Add executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${ASM_SOURCES})

enable_language(C CXX)


# Post-build commands for generating binary and hex files
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>)
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
#     COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
# )