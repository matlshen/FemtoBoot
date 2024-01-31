#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void CANInit(void);
void CANTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length);
void CANReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length);


#ifdef __cplusplus
}
#endif

#endif /* CAN_H_ */