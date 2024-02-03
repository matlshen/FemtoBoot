#include "ll_util.h"

// Timer functions do nothing, they must exist for timer.c to compile,
// but they are not used in host program
void LL_UtilTimerInit() {}
uint32_t LL_UtilTimerGetTimeMs() { return 0; }
void LL_UtilTimerDeInit() {}

// Hardware functions do nothing, they must exist for boot_ll_util.c to compile,
void JumpToApp() {}
void HardwareReset() {}