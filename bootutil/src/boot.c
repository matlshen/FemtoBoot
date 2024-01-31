#include "boot.h"

// Array of valid commands
uint16_t valid_commands[NUM_COMMANDS] = {
    MSG_ID_CONN,
    MSG_ID_MEM_ERASE,
    MSG_ID_MEM_WRITE,
    MSG_ID_MEM_READ,
    MSG_ID_VERIFY,
    MSG_ID_RUN,
    MSG_ID_RESET,
};

boot_state_typedef boot_state = WAITING_FOR_COMMAND;

uint16_t rx_msg_id;
uint8_t rx_data[256];
size_t rx_length;

void BootStateMachine(void) {
    switch (boot_state) {
        case WAITING_FOR_COMMAND:
            ComReceivePacket(&rx_msg_id, rx_data, &rx_length);
            if (rx_msg_id == MSG_ID_CONN) {
                boot_state = WAITING_FOR_COMMAND;
                ComAck();
            } else {
                ComNack();
            }
            break;
        case SENDING_CONNECTION_PARAMS:
            ComAck();
            for (size_t i = 0; i < NUM_COMMANDS; i++) {
                ComTransmitPacket(MSG_ID_CONN, (uint8_t *)&valid_commands[i], 2);
            }
            ComAck();
            boot_state = WAITING_FOR_COMMAND;
            break;
        case MEM_ERASE:
            break;
        case MEM_READ:
            break;
        case MEM_WRITE:
            break;
        default:
            // Shouldn't get here
            break;
    }
}

