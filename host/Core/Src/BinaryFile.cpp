#include "BinaryFile.hpp"

#include <iostream>
#include "crc32.h"

BinaryFile::~BinaryFile() {
    binary_file_.close();
}

Boot_StatusTypeDef BinaryFile::Open(const char* filename) {
    // Open the file
    binary_file_.open(filename, std::ios::binary);
    if (!binary_file_.is_open()) {
        return BOOT_ERROR;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef BinaryFile::Length(size_t* length) {
    // Preserve the current position
    current_pos_ = binary_file_.tellg();

    // Get the length of the file
    binary_file_.seekg(0, std::ios::end);
    *length = binary_file_.tellg();

    // Restore the current position
    binary_file_.seekg(current_pos_);

    return BOOT_OK;
}

Boot_StatusTypeDef BinaryFile::Read(uint8_t* buffer, size_t length, uint32_t* crc) {
    // Read the file
    binary_file_.read(reinterpret_cast<char*>(buffer), length);
    if (binary_file_.gcount() != length)
        return BOOT_ERROR;

    // Get CRC of the file
    *crc = crc32(buffer, length, INITIAL_CRC);

    return BOOT_OK;
}