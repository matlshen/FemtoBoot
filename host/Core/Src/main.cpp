#include <iostream>
#include <synchapi.h>
#include <string>
#include <fstream>
#include <vector>
#include "win_serial.h"
#include "BootTarget.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <binary>" << std::endl;
        return -1;
    }

    std::ifstream binary_file(argv[1], std::ios::binary);
    if (!binary_file.is_open()) {
        std::cout << "Failed to open file: " << argv[1] << std::endl;
        return -1;
    }

    // Get length of binary file
    binary_file.seekg(0, std::ios::end);
    int length = binary_file.tellg();
    std::cout << "File length: " << length << " bytes" << std::endl;


    // Read the first 8 bytes of the file
    std::vector<uint8_t> buffer(8);
    binary_file.seekg(0, std::ios::beg);
    binary_file.read(reinterpret_cast<char*>(buffer.data()), 8);

    std::cout << std::hex;
    for (int i = 0; i < 8; i++) {
        std::cout << (unsigned int)buffer[i] << " ";
    }


    return 0;






    Boot_StatusTypeDef status = BOOT_OK;

    BootTarget target;

    while (1) {
        status = target.Connect();

        // If connected to target successfully
        if (status != BOOT_OK) {
            return -1;
        }

        Sleep(5000);
    }

    return 0;
}