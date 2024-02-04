#include "BootTarget.hpp"

#include <synchapi.h>
#include <iostream>
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

    uint32_t connection_period = BOOT_TIMEOUT_MS / 2;

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

            // If no response from target, try again on the next connection period
            Sleep(connection_period);
        }
    }

    std::cout << "Target timed out" << std::endl;

    return BOOT_ERROR;
}