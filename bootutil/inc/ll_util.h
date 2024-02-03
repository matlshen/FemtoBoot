#ifndef LL_UTIL_H_
#define LL_UTIL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "boot_config.h"

void LL_UtilHardwareInit();
void LL_UtilHardwareDeInit();

void LL_UtilTimerInit();
uint32_t LL_UtilTimerGetTimeMs();
void LL_UtilTimerDeInit();

void JumpToApp();
void HardwareReset();


void InitializeHardware();
void DeinitializeHardware();


#ifdef __cplusplus
}
#endif

#endif /* LL_UTIL_H_ */