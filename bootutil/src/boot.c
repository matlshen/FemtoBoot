#include "boot.h"

// Array of valid commands
uint16_t valid_commands[NUM_COMMANDS] = {
    MSG_ID_CONN,
    MSG_ID_CHANGE_SPEED,
    MSG_ID_MEM_ERASE,
    MSG_ID_MEM_READ,
    MSG_ID_MEM_WRITE,
    MSG_ID_VERIFY,
    MSG_ID_RUN,
    MSG_ID_RESET,
};

uint16_t rx_msg_id;
uint8_t rx_data[256];
size_t rx_length;

typedef enum {
    WAITING_FOR_COMMAND,
    CONN_REQ,
    CHANGE_SPEED,
    MEM_ERASE,
    MEM_READ,
    MEM_WRITE,
    VERIFY,
    RUN,
    RESET,
} boot_state_typedef;

static boot_state_typedef boot_state = WAITING_FOR_COMMAND;
static Boot_StatusTypeDef status;

void BootStateMachine(void) {
    switch (boot_state) {
        case WAITING_FOR_COMMAND:
            status = ComReceivePacket(&rx_msg_id, rx_data, &rx_length);
            if (status == BOOT_TIMEOUT) {
                // If timeout, go back to waiting for command
                boot_state = WAITING_FOR_COMMAND;
                break;
            }
            if (rx_msg_id == MSG_ID_CONN) {
                boot_state = CONN_REQ;
                ComAck();
            } else {
                ComNack();
            }
            break;
        case CONN_REQ:
            // Reset boot timeout
            TimerTimeoutReset(COMMAND_TIMEOUT_MS);
            for (size_t i = 0; i < NUM_COMMANDS; i++) {
                ComTransmitPacket(MSG_ID_CONN, (uint8_t *)&valid_commands[i], NUM_COMMANDS);
            }
            boot_state = WAITING_FOR_COMMAND;
            break;
        case MEM_ERASE:
            break;
        case MEM_READ:
            break;
        case MEM_WRITE:
            break;
        case VERIFY:
            break;
        case RUN:
            JumpToApp();
            // If jump fails, go back to waiting for command
            boot_state = WAITING_FOR_COMMAND;
            break;
        case RESET:
            HardwareReset();
        default:
            // Shouldn't get here
            ComNack();
            boot_state = WAITING_FOR_COMMAND;
            break;
    }
}

