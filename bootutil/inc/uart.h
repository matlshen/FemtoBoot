#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void UARTInit(void);
void UARTTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length);
void UARTReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length);


#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */