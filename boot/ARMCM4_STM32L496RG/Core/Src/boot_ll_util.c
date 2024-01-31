#include "ll_util.h"

#include "stm32l4xx.h"

typedef void (*pFnResetHandler)(void);

void JumpToApp() {
    // Check that stack pointer is a valid address in SRAM
    if (!VerifySP()) {
        return;
    }

    // Deinit HAL
    HAL_DeInit();

    // Set vector table offset
    SCB->VTOR = APP_ADDRESS;

    // Update MSP
    __set_MSP(*(volatile uint32_t *)APP_ADDRESS);

    // Get reset handler address
    pFnResetHandler ResetHandler = (pFnResetHandler)(*(volatile uint32_t *)(APP_ADDRESS + 4));

    // Enable interrupts
    __enable_irq();

    // Call reset handler
    ResetHandler();
}

uint32_t VerifySP() {
    return *(volatile uint32_t *)APP_ADDRESS >= SRAM_START_ADDRESS && *(volatile uint32_t *)APP_ADDRESS < SRAM_START_ADDRESS + SRAM_SIZE;
}

void ReinitializeHardware() {
    // Reinitialize HAL
    HAL_Init();
}