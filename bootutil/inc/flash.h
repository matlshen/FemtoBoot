#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>
#include <stddef.h>

#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif

boot_status_typedef FlashUnlock();
boot_status_typedef FlashErase(size_t address, size_t size);
boot_status_typedef FlashRead(size_t address, void *data, size_t size);
boot_status_typedef FlashWrite(size_t address, const void *data, size_t size);
boot_status_typedef FlashLock();


#ifdef __cplusplus
}
#endif

#endif /* FLASH_H_ */