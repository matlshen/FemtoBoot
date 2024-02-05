#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>
#include <stddef.h>

#include "boot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

Boot_StatusTypeDef FlashErase(size_t address, size_t size);
Boot_StatusTypeDef FlashRead(size_t address, void *data, size_t size);
Boot_StatusTypeDef FlashWrite(size_t address, const void *data, size_t size);


#ifdef __cplusplus
}
#endif

#endif /* FLASH_H_ */