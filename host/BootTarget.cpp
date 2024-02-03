#include "BootTarget.hpp"

#include <iostream>
#include "com.h"

BootTarget::BootTarget(const char* port) {
    ComInit();
}

BootTarget::~BootTarget() {
    ComDeInit();
}

void BootTarget::Connect() {
    ComTransmitPacket(MSG_ID_CONN, NULL, NULL);
    ComReceivePacket(&msg_id, msg_data, &msg_len, NULL);

    if (msg_id != MSG_ID_ACK)
        std::cerr << "Error: Failed to connect to target" << std::endl;
    
}