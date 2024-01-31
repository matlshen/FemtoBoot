#ifndef BOOT_CONFIG_H_
#define BOOT_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define APP_ADDRESS             0x8004000U
#define FLASH_START_ADDRESS     0x0800000U
// FLASH_SIZE already defined in HAL
//#define FLASH_SIZE              0x00100000U
#define SRAM_START_ADDRESS      0x20000000U
#define SRAM_SIZE               0x00060000U

#define BOOT_TIMEOUT_MS         500U
#define COMMAND_TIMEOUT_MS      1000U

#define SYSTEM_CLOCK_MHZ        16U

// #define USE_CAN
//     #define CAN_RX_PIN      PB8
//     #define CAN_TX_PIN      PB9
//     #define CAN_BAUDRATE    500000
#define USE_UART
    #define UART_RX_PIN     PA3
    #define UART_TX_PIN     PA2
    #define UART_BAUDRATE   115200


/* Don't modify anything below this line */
#ifdef USE_CAN
    #include "can.h"
#endif

#ifdef USE_UART
    #include "uart.h"
#endif

#ifdef __cplusplus
}
#endif

#endif // BOOT_CONFIG_H_