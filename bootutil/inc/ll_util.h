#ifndef LL_UTIL_H_
#define LL_UTIL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "boot_config.h"

void InitializeHardware();
void DeinitializeHardware();
void JumpToApp();
uint32_t VerifySP();
void Reset();   // TODO


#ifdef __cplusplus
}
#endif

#endif /* LL_UTIL_H_ */