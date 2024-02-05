#include "timer.h"
#include <windows.h>

uint32_t boot_time_ms;
uint32_t timeout_time_ms;

void TimerInit(void) {
    SYSTEMTIME st;
    GetSystemTime(&st);

    boot_time_ms = (uint32_t)st.wMilliseconds;
    timeout_time_ms = boot_time_ms + BL_TIMEOUT_MS;
}

Boot_StatusTypeDef TimerUpdate(void) {
    SYSTEMTIME st;
    GetSystemTime(&st);

    // Read timer count
    boot_time_ms = st.wMilliseconds;

    // Check if timeout expired
    if (boot_time_ms > timeout_time_ms) {
        return BOOT_TIMEOUT;
    }

    return BOOT_OK;
}

void TimerSetTimeout(uint32_t timeout_ms) {
    SYSTEMTIME st;
    GetSystemTime(&st);

    // Read timer count
    boot_time_ms = st.wMilliseconds;

    timeout_time_ms = boot_time_ms + timeout_ms;

    // If overflow, set to max
    if (timeout_time_ms < boot_time_ms) {
        timeout_time_ms = __UINT32_MAX__;
    }
}

void TimerDelay(uint32_t delay_ms) {
    Sleep(delay_ms);
}

void TimerDeInit(void) {
    // Nothing to do
}