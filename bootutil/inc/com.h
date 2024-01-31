#ifndef COM_H_
#define COM_H_

#include <stdint.h>
#include <stddef.h>

#include "com_types.h"
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif

void ComInit(void);
inline void ComTransmit(uint8_t *data, size_t length);
inline void ComReceive(uint8_t *data, size_t length);
void ComTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length);
void ComReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length);
void ComAck();
void ComNack();


#ifdef __cplusplus
}
#endif

#endif /* COM_H_ */