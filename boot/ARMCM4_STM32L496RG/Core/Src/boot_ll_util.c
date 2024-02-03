#include "ll_util.h"

#include "stm32l4xx.h"

typedef void (*pFnResetHandler)(void);

void InitializeHardware() {
    // Init HAL
    HAL_Init();
    // Disable interrupts
    __disable_irq();
}

void DeinitializeHardware() {
    // Deinit HAL
    HAL_DeInit();
}

void JumpToApp() {
    // Check that stack pointer is a valid address in SRAM
    if (!(*(volatile uint32_t *)APP_ADDRESS >= SRAM_START_ADDRESS && *(volatile uint32_t *)APP_ADDRESS < SRAM_START_ADDRESS + SRAM_SIZE)) {
        return;
    }

    // Get reset handler address
    pFnResetHandler ResetHandler = (pFnResetHandler)(*(volatile uint32_t *)(APP_ADDRESS + 4));

    // Deinitialize hardware
    DeinitializeHardware();

    // Set vector table offset
    SCB->VTOR = APP_ADDRESS;
    
    // Enable interrupts
    __enable_irq();

    // Update MSP
    __set_MSP(*(volatile uint32_t *)APP_ADDRESS);

    // Call reset handler
    ResetHandler();
}

inline void HardwareReset() {
    __NVIC_SystemReset();
}