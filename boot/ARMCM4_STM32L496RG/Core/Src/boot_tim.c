#include "tim.h"
#include "stm32l4xx.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_bus.h"

uint32_t boot_time_ms = 0;
uint32_t timeout_ms = BOOT_TIMEOUT_MS;

void TimInit() {
    // Enable TIM2 clock
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    // Set prescaler to generate 1ms ticks
    LL_TIM_SetPrescaler(TIM2, __LL_TIM_CALC_PSC(SystemCoreClock, 1000));
    // Generate an update event to update prescaler value immediately
    LL_TIM_GenerateEvent_UPDATE(TIM2);

    // Set timer to count up
    LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);

    // Zero timer
    LL_TIM_SetCounter(TIM2, 0);

    // Enable TIM2 counter
    LL_TIM_EnableCounter(TIM2);
}

void TimUpdate() {
    // Read timer count
    boot_time_ms = TIM2->CNT;

    // Jump to app if timeout
    if (boot_time_ms > BOOT_TIMEOUT_MS) {
        JumpToApp();
        // If we get here, something went wrong launching app
        LL_TIM_SetCounter(TIM2, 0);
    }
}

void TimDelay(uint32_t delay_ms) {
    // Set timeout
    TimResetTimeout(delay_ms);

    // Wait for timeout
    while (boot_time_ms < timeout_ms) {
        TimUpdate();
    }
}

void TimResetTimeout(uint32_t timeout_ms) {
    // Set new timeout
    timeout_ms = boot_time_ms + timeout_ms;
}