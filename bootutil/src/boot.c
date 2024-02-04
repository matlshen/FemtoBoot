#include "boot.h"

// Array of valid commands
uint16_t valid_commands[NUM_COMMANDS] = {
    MSG_ID_CONN,
    MSG_ID_CHANGE_SPEED,
    MSG_ID_MEM_ERASE,
    MSG_ID_MEM_READ,
    MSG_ID_MEM_WRITE,
    MSG_ID_VERIFY,
    MSG_ID_RUN, // TODO: Change msg id to not match ACK
    MSG_ID_RESET,
};

uint16_t rx_msg_id;
uint8_t rx_data[256];
uint8_t rx_length;

#ifdef TARGET

typedef enum {
    INIT,
    WAITING_FOR_CONNECTION,
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

static boot_state_typedef boot_state = WAITING_FOR_CONNECTION;
static Boot_StatusTypeDef status;

void BootStateMachine(void) {
    switch (boot_state) {
        case INIT:
            // Initialize necessary modules and wait for command from host
            // InitializeHardware();
            // TimerInit();
            // ComInit();
            boot_state = WAITING_FOR_CONNECTION;
            break;
        case WAITING_FOR_CONNECTION:
            // Wait for connection packet
            status = ComReceivePacket(&rx_msg_id, rx_data, &rx_length, BOOT_TIMEOUT_MS);
            // If packet times out, attempt to run application
            if (status == BOOT_TIMEOUT) {
                boot_state = RUN;
            }
            // For any other error, go back to waiting for connection
            else if (status != BOOT_OK) {
                ComNack();
            }
            // If packet received, check if it's a connection request
            else {
                // If packet received, check if it's a connection request
                if (rx_msg_id == MSG_ID_CONN) {
                    ComAck();
                    // Send list of valid commands
                    for (size_t i = 0; i < NUM_COMMANDS; i++) {
                        ComTransmitPacket(valid_commands[i], NULL, 0);
                    }
                    //ComAck();
                    boot_state = WAITING_FOR_COMMAND;
                } else {
                    ComNack();
                }
            }

            break;
        case WAITING_FOR_COMMAND:
            // Wait for command packet
            status = ComReceivePacket(&rx_msg_id, rx_data, &rx_length, BOOT_TIMEOUT_MS);
            if (status == BOOT_TIMEOUT) {
                boot_state = RUN;
                break;
            }
            else if (status == BOOT_OK) {
                switch (rx_msg_id) {
                    case MSG_ID_CHANGE_SPEED:
                        boot_state = CHANGE_SPEED;
                        break;
                    case MSG_ID_MEM_ERASE:
                        boot_state = MEM_ERASE;
                        break;
                    case MSG_ID_MEM_READ:
                        boot_state = MEM_READ;
                        break;
                    case MSG_ID_MEM_WRITE:
                        boot_state = MEM_WRITE;
                        break;
                    case MSG_ID_VERIFY:
                        boot_state = VERIFY;
                        break;
                    case MSG_ID_RUN:
                        boot_state = RUN;
                        break;
                    case MSG_ID_RESET:
                        boot_state = RESET;
                        break;
                    default:
                        ComNack();
                        boot_state = WAITING_FOR_COMMAND;
                        break;
                }
            }
            else {
                ComNack();
                boot_state = WAITING_FOR_COMMAND;
            }
            break;
        case CONN_REQ:
            // Send connection parameters
            for (size_t i = 0; i < NUM_COMMANDS; i++) {
                ComTransmitPacket(valid_commands[i], NULL, 0);
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
        case VERIFY:
            break;
        case RUN:
            JumpToApp();
            // If jump fails, go back to waiting for command
            boot_state = WAITING_FOR_COMMAND;
            break;
        case RESET:
            //HardwareReset();
            break;
        default:
            // Shouldn't get here
            ComNack();
            boot_state = WAITING_FOR_COMMAND;
            break;
    }
}

#endif

#ifdef HOST

typedef enum {
    INIT,
    CONNECTING,
    WAITING_FOR_COMMAND,
    CONN_REQ,
    CHANGE_SPEED,
    MEM_ERASE,
    MEM_READ,
    MEM_WRITE,
    VERIFY,
    RUN,
    RESET,
    DONE
} boot_state_typedef;

static boot_state_typedef boot_state = INIT;
static Boot_StatusTypeDef status;

void BootStateMachine(void) {
    switch (boot_state) {
        case INIT:
            LL_UtilHardwareInit();
            boot_state = CONNECTING;
            break;
        case CONNECTING:
            // Send connection request
            ComTransmitPacket(MSG_ID_CONN, NULL, 0);
            status = ComReceivePacket(&rx_msg_id, rx_data, &rx_length, BOOT_TIMEOUT_MS);
            if (status == BOOT_TIMEOUT) {
                boot_state = DONE;
            }
            else if (status == BOOT_OK) {
                if (rx_msg_id == MSG_ID_CONN) {
                    boot_state = WAITING_FOR_COMMAND;
                }
                else {
                    ComNack();
                }
            }
            else {
                ComNack();
            }
            break;
        case DONE:
            LL_UtilHardwareDeInit();
            break;
        default:
            break;
    }
}


#endif