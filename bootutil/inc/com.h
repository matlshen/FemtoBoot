#ifndef COM_H_
#define COM_H_

#include <stdint.h>

#include "boot_types.h"
#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif

Boot_StatusTypeDef ComInit(void);
Boot_StatusTypeDef ComDeInit(void);
Boot_StatusTypeDef ComTransmit(uint8_t *data, uint8_t length, uint32_t timeout_ms);
Boot_StatusTypeDef ComReceive(uint8_t *data, uint8_t length, uint32_t timeout_ms);
Boot_StatusTypeDef ComTransmitPacket(uint16_t msg_id, uint8_t *data, uint8_t length);
Boot_StatusTypeDef ComReceivePacket(uint16_t *msg_id, uint8_t *data, uint8_t *length, uint32_t timeout_ms);
Boot_StatusTypeDef ComAck();
Boot_StatusTypeDef ComNack();


#ifdef __cplusplus
}
#endif

#endif /* COM_H_ */