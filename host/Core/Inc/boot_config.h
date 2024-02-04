#ifndef BOOT_CONFIG_H_
#define BOOT_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HOST

#define APP_ADDRESS             0x8004000U


#define FLASH_START_ADDRESS     0x0800000U
// FLASH_SIZE already defined in HAL
//#define FLASH_SIZE              0x00100000U
#define SRAM_START_ADDRESS      0x20000000U
#define SRAM_SIZE               0x00060000U

// Timeout for connection upon startup
#define BOOT_TIMEOUT_MS         500U
// Timeout for command reception after connection established
#define COMMAND_TIMEOUT_MS      100000U

#define SYSTEM_CLOCK_MHZ        16U

// #define USE_CAN
//     #define CAN_RX_PIN      PB8
//     #define CAN_TX_PIN      PB9
//     #define CAN_BAUDRATE    500000
// #define USE_UART
//     #define UART_RX_PIN_PA3
//     #define UART_TX_PIN_PA2
//     #define UART_BAUDRATE   115200
#define USE_PC_SERIAL
    #define SERIAL_BAUDRATE   115200

#ifdef __cplusplus
}
#endif

#endif // BOOT_CONFIG_H_