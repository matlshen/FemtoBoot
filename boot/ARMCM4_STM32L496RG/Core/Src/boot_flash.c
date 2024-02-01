#include "flash.h"
#include "stm32l4xx.h"

// 2kB flash page size
#define FLASH_PAGE_SIZE 0x800U

// Buffer for flash writes
uint8_t flash_buffer[FLASH_PAGE_SIZE];


boot_status_typedef FlashUnlock() {
    return (boot_status_typedef)HAL_FLASH_Unlock();
}

boot_status_typedef FlashErase(size_t address, size_t size) {
    // Return if address does not align with page
    if (address % FLASH_PAGE_SIZE != 0) {
        return BOOT_ERROR;
    }

    // Return if size does not align with page
    if (size % FLASH_PAGE_SIZE != 0) {
        return BOOT_ERROR;
    }

    FLASH_EraseInitTypeDef erase_init;
    uint32_t error;
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Page = address;
    erase_init.NbPages = size;
    HAL_FLASHEx_Erase(&erase_init, &error);
}

boot_status_typedef FlashLock() {
    return (boot_status_typedef)HAL_FLASH_Lock();
}