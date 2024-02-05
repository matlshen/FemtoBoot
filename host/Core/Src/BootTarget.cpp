#include "BootTarget.hpp"

#include <synchapi.h>
#include <iostream>
#include <string>
#include "com.h"

BootTarget::BootTarget() {
    std::cout << std::hex;
    ComInit();
}

BootTarget::~BootTarget() {
    ComDeInit();
}

Boot_StatusTypeDef BootTarget::Connect() {
    std::cout << "Connecting to target..." << std::endl;

    /* Try for 10 seconds to send connection requests to the target at intervals
    of BOOT_TIMEOUT_MS / 2. This guarantees that the target will receive the 
    connection request at least once within its boot window */

    uint32_t connection_period = BL_TIMEOUT_MS / 2;

    Boot_StatusTypeDef status = BOOT_OK;

    for (int i = 0; i < 10 * 1000 / connection_period; i++) {
        // Send connection request packet
        status = ComTransmitPacket(MSG_ID_CONN, NULL, 0);
        if (status != BOOT_OK) {
            std::cout << "Failed to send connection request" << std::endl;
            return BOOT_ERROR;
        }

        // Wait for ACK
        status = ComReceivePacket(&msg_id , msg_data, &msg_len, 0);
        if (status == BOOT_OK && msg_id == MSG_ID_ACK) {
            std::cout << "Connected to target" << std::endl;

            // Collect valid commands
            do {
                status = ComReceivePacket(&msg_id, msg_data, &msg_len, 0);
                if (status != BOOT_OK) {
                    std::cout << "Failed to receive packet" << std::endl;
                } else {
                    std::cout << "Received valid command ID: 0x" << msg_id << std::endl;
                }
            } while (msg_id != MSG_ID_ACK);
            std::cout << "Received ACK" << std::endl;

            // Connected successfully, return
            return BOOT_OK;
        }

        Sleep(connection_period);
    }

    std::cout << "Target timed out" << std::endl;

    return BOOT_ERROR;
}

Boot_StatusTypeDef BootTarget::ReadFlash(uint32_t address, uint8_t* buffer, size_t length) {
    std::cout << "Reading flash..." << std::endl;

    // Send read request packet
    uint8_t msg_data[12] = {0};
    memcpy(msg_data, &address, sizeof(address));
    memcpy(msg_data + 8, &length, 4);
    Boot_StatusTypeDef status = ComTransmitPacket(MSG_ID_MEM_READ, msg_data, 12);
    if (status != BOOT_OK) {
        std::cout << "Failed to send read request" << std::endl;
        return BOOT_ERROR;
    }

    // Wait for ACK
    status = ComReceivePacket(&msg_id, msg_data, &msg_len, 0);
    if (status != BOOT_OK || msg_id != MSG_ID_ACK) {
        std::cout << "Failed to receive ACK" << std::endl;
        return BOOT_ERROR;
    }
    std::cout << msg_id << std::endl;

    // Wait for data
    status = ComReceivePacket(&msg_id, buffer, (uint8_t*)&length, 0);
    if (status != BOOT_OK || msg_id != MSG_ID_MEM_READ) {
        std::cout << "Failed to receive data" << std::endl;
        return BOOT_ERROR;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef BootTarget::EraseFlash(uint32_t address, size_t length) {
    std::cout << "Erasing flash..." << std::endl;

    // Send erase request packet
    uint8_t msg_data[12] = {0};
    memcpy(msg_data, &address, sizeof(address));
    memcpy(msg_data + 8, &length, 4);
    Boot_StatusTypeDef status = ComTransmitPacket(MSG_ID_MEM_ERASE, msg_data, 12);
    if (status != BOOT_OK) {
        std::cout << "Failed to send erase request" << std::endl;
        return BOOT_ERROR;
    }

    // Wait for ACK
    status = ComReceivePacket(&msg_id, msg_data, &msg_len, 0);
    if (status != BOOT_OK || msg_id != MSG_ID_ACK) {
        std::cout << "Failed to receive ACK" << std::endl;
        return BOOT_ERROR;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef BootTarget::WriteFlash(uint32_t address, uint8_t* buffer, size_t length) {
    std::cout << "Writing flash..." << std::endl;

    // Send write request packet
    uint8_t msg_data[12] = {0};
    memcpy(msg_data, &address, sizeof(address));
    memcpy(msg_data + 8, &length, 4);
    Boot_StatusTypeDef status = ComTransmitPacket(MSG_ID_MEM_WRITE, msg_data, 12);
    if (status != BOOT_OK) {
        std::cout << "Failed to send write request" << std::endl;
        return BOOT_ERROR;
    }

    // Wait for ACK
    status = ComReceivePacket(&msg_id, msg_data, &msg_len, 0);
    if (status != BOOT_OK || msg_id != MSG_ID_ACK) {
        std::cout << "Failed to receive ACK" << std::endl;
        return BOOT_ERROR;
    }

    // Send data
    status = ComTransmitPacket(MSG_ID_MEM_WRITE, buffer, length);
    if (status != BOOT_OK) {
        std::cout << "Failed to send data" << std::endl;
        return BOOT_ERROR;
    }

    // Wait for ACK
    status = ComReceivePacket(&msg_id, msg_data, &msg_len, 0);
    if (status != BOOT_OK || msg_id != MSG_ID_ACK) {
        std::cout << "Failed to receive ACK" << std::endl;
        return BOOT_ERROR;
    }

    return BOOT_OK;
}