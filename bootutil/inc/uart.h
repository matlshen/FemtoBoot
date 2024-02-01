#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stddef.h>
#include "boot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

Boot_StatusTypeDef UARTInit(void);
Boot_StatusTypeDef UARTTransmitByte(uint8_t data, uint32_t timeout_ms);
Boot_StatusTypeDef UARTReceiveByte(uint8_t *data, uint32_t timeout_ms);


#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */