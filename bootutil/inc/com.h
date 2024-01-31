#ifndef COM_H_
#define COM_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void ComInit(void);
void ComTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length);
void ComReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length);


#ifdef __cplusplus
}
#endif

#endif /* COM_H_ */