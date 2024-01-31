#include "com.h"

// Make sure only one protocol is used at a time
#if defined(USE_CAN) && defined(USE_UART)
    #error "Only one protocol can be used at a time"
#endif

void ComInit(void) {
    #ifdef USE_CAN
    CANInit();
    #endif

    #ifdef USE_UART
    UARTInit();
    #endif
}

void ComTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length) {
    #ifdef USE_CAN
    CANTransmitPacket(msg_id, data, length);
    #endif

    #ifdef USE_UART
    UARTTransmitPacket(msg_id, data, length);
    #endif
}

void ComReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length) {
    #ifdef USE_CAN
    CANReceivePacket(msg_id, data, length);
    #endif

    #ifdef USE_UART
    UARTReceivePacket(msg_id, data, length);
    #endif
}