#ifndef SERIAL_H_
#define SERIAL_H_

#include "boot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

Boot_StatusTypeDef SerialInit(const char* port, int baudrate);
Boot_StatusTypeDef SerialDeInit();
Boot_StatusTypeDef SerialTransmit(uint8_t data);
Boot_StatusTypeDef SerialReceive(uint8_t *data);


#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H_ */