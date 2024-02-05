#include <iostream>
#include <synchapi.h>
#include <string>
#include <fstream>
#include <vector>
#include "crc32.h"
#include "win_serial.h"
#include "BootTarget.hpp"
#include "BinaryFile.hpp"


Boot_StatusTypeDef status = BOOT_OK;
BinaryFile binary;
BootTarget target;

int main(int argc, char* argv[])
{
    // Expecting a binary file as an argument
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <binary>" << std::endl;
        return -1;
    }

    // Attempt to open the binary file
    status = binary.Open(argv[1]);
    if (status != BOOT_OK) {
        std::cout << "Failed to open file: " << argv[1] << std::endl;
        return -1;
    }

    // Read the first 8 bytes of the file
    uint8_t buffer[8];
    uint32_t crc;
    status = binary.Read(buffer, 8, &crc);
    if (status != BOOT_OK) {
        std::cout << "Failed to read file" << std::endl;
        return -1;
    }
    // Print the length of the file
    size_t length;
    status = binary.Length(&length);
    if (status != BOOT_OK) {
        std::cout << "Failed to get file length" << std::endl;
        return -1;
    }

    
    std::cout << "File length: " << length << " bytes" << std::endl;
    // Print the first 8 bytes
    std::cout << "First 8 bytes: ";
    for (int i = 0; i < 8; i++) {
        std::cout << "0x" << std::hex << (unsigned int)buffer[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "CRC: 0x" << std::hex << crc << std::endl;



    // Connect to the target
    status = target.Connect();
    if (status != BOOT_OK) {
        std::cout << "Failed to connect to target" << std::endl;
        return -1;
    }

    // Read the first 8 bytes of the target's application Flash
    uint8_t target_buffer[8];
    status = target.ReadFlash(0x08004000, target_buffer, 8);
    if (status == BOOT_OK) {
        // Print the first 8 bytes
        std::cout << "First 8 bytes of target: ";
        for (int i = 0; i < 8; i++) {
            std::cout << "0x" << std::hex << (unsigned int)target_buffer[i] << " ";
        }
    }


    return 0;
}