#pragma once

#include <fstream>
#include <stdint.h>
#include <stddef.h>
#include "boot_types.h"

class BinaryFile {
public:
    BinaryFile() = default;
    ~BinaryFile();
    Boot_StatusTypeDef Open(const char* filename);
    Boot_StatusTypeDef Length(size_t* length);
    Boot_StatusTypeDef Read(uint8_t* buffer, size_t length, uint32_t* crc);
private:
    std::ifstream binary_file_;
    std::streampos current_pos_;
};