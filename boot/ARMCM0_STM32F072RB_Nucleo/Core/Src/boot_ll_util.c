#include "ll_util.h"

#include "stm32f0xx_hal.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_usart.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_tim.h"

void LL_UtilHardwareInit() {
    HAL_Init();

    // Configure system clock to 48 MHz
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
    while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1) {}

    LL_RCC_HSI48_Enable();

    /* Wait till HSI48 is ready */
    while(LL_RCC_HSI48_IsReady() != 1) {}
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI48);

    /* Wait till System clock is ready */
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI48) {}
    LL_SetSystemCoreClock(48000000);

    LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
}

void LL_UtilHardwareDeInit() {
    HAL_DeInit();
}

void LL_UtilTimerInit() {
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

uint32_t LL_UtilTimerGetTimeMs() {
    return TIM2->CNT;
}

void LL_UtilTimerDeInit() {
    LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM2);
    LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM2);
    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);

    // Reset SysTick as well
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
}