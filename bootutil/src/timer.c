#include "timer.h"

#include "ll_util.h"

uint32_t boot_time_ms = 0;
uint32_t timeout_time_ms = BOOT_TIMEOUT_MS;

void TimerInit(void) {
    LL_UtilTimerInit();
}

Boot_StatusTypeDef TimerUpdate(void) {
    // Read timer count
    boot_time_ms = LL_UtilTimerGetTimeMs();

    // Check if timeout expired
    if (boot_time_ms > timeout_time_ms) {
        return BOOT_TIMEOUT;
    }

    return BOOT_OK;
}

void TimerSetTimeout(uint32_t timeout_ms) {
    // Read timer count
    boot_time_ms = LL_UtilTimerGetTimeMs();

    timeout_time_ms = boot_time_ms + timeout_ms;

    // If overflow, set to max
    if (timeout_time_ms < boot_time_ms) {
        timeout_time_ms = __UINT32_MAX__;
    }
}

void TimerDelay(uint32_t delay_ms) {
    // Preserve original timeout
    uint32_t timeout_store = timeout_time_ms;

    // Set timeout
    TimerSetTimeout(delay_ms);

    // Wait for timeout
    while (boot_time_ms < timeout_time_ms) {
        // Read timer count
        boot_time_ms = LL_UtilTimerGetTimeMs();
    }

    // Restore timeout
    timeout_time_ms = timeout_store;
}

void TimerDeInit(void) {
    LL_UtilTimerDeInit();
}