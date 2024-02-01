#include "timer.h"
#include "stm32l4xx.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_bus.h"

uint32_t boot_time_ms = 0;
uint32_t timeout_ms = BOOT_TIMEOUT_MS;

void TimerInit() {
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

void TimerUpdate() {
    // Read timer count
    boot_time_ms = TIM2->CNT;

    // Jump to app if timeout
    if (boot_time_ms > timeout_ms) {
        JumpToApp();
        // If we get here, something went wrong launching app
        LL_TIM_SetCounter(TIM2, 0);
    }
}

void TimerDelay(uint32_t delay_ms) {
    // Set timeout
    TimerTimeoutReset(delay_ms);

    // Wait for timeout
    while (boot_time_ms < timeout_ms) {
        TimerUpdate();
    }
}

void TimerTimeoutReset(uint32_t timeout_ms) {
    // Set new timeout
    timeout_ms = boot_time_ms + timeout_ms;
}

void TimerReset(void) {
    LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM2);
    LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM2);
    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);

    // Reset SysTick as well
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
}