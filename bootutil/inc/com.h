#ifndef COM_H_
#define COM_H_

#include <stdint.h>
#include <stddef.h>

#include "boot_types.h"
#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BYTE_TIMEOUT_MS 500
#define MAX_TIMEOUT_MS  __UINT32_MAX__

Boot_StatusTypeDef ComInit(void);
Boot_StatusTypeDef ComDeInit(void);
Boot_StatusTypeDef ComTransmitByte(uint8_t data, uint32_t timeout_ms);
Boot_StatusTypeDef ComReceiveByte(uint8_t *data, uint32_t timeout_ms);
Boot_StatusTypeDef ComTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length);
Boot_StatusTypeDef ComReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length, uint32_t timeout_ms);
Boot_StatusTypeDef ComAck();
Boot_StatusTypeDef ComNack();


#ifdef __cplusplus
}
#endif

#endif /* COM_H_ */