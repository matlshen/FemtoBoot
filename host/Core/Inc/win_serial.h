#ifndef SERIAL_H_
#define SERIAL_H_

#include "boot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* serial_port;

Boot_StatusTypeDef SerialInit(int baudrate);
Boot_StatusTypeDef SerialDeInit();
Boot_StatusTypeDef SerialTransmit(uint8_t *data, uint8_t length);
Boot_StatusTypeDef SerialReceive(uint8_t *data, uint8_t length);


#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H_ */