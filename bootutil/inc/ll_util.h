#ifndef LL_UTIL
#define LL_UTIL

#ifdef __cplusplus
extern "C" {
#endif

#include "boot_config.h"

void JumpToApp();
uint32_t VerifySP();
void ReinitializeHardware();


#ifdef __cplusplus
}
#endif

#endif /* LL_UTIL */