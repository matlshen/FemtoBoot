#pragma once

#include <stdint.h>
#include <stddef.h>
#include "boot_types.h"
#include "boot_config.h"

class BootTarget {
public:
    BootTarget();
    ~BootTarget();

    Boot_StatusTypeDef Connect();
    Boot_StatusTypeDef ReadFlash(uint32_t address, uint8_t* buffer, size_t length);
    Boot_StatusTypeDef EraseFlash(uint32_t address, size_t length);
    Boot_StatusTypeDef WriteFlash(uint32_t address, uint8_t* buffer, size_t length);
    void Reset();
private:
    uint16_t msg_id;
    uint8_t msg_data[256];
    uint8_t msg_len;
};