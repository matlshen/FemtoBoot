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

void ComTransmit(uint8_t *data, size_t length) {
    #ifdef USE_CAN
    CANTransmit(data, length);
    #endif

    #ifdef USE_UART
    UARTTransmit(data, length);
    #endif
}

void ComReceive(uint8_t *data, size_t length) {
    #ifdef USE_CAN
    CANReceive(data, length);
    #endif

    #ifdef USE_UART
    UARTReceive(data, length);
    #endif
}

void ComTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length) {
    ComTransmit((uint8_t *)&msg_id, 2);
    ComTransmit((uint8_t *)&length, 1);
    ComTransmit(data, length);
}

void ComReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length) {
    ComReceive((uint8_t *)msg_id, 2);
    ComReceive((uint8_t *)length, 1);
    ComReceive(data, *length);
}

void ComAck() {
    ComTransmitPacket(MSG_ID_ACK, NULL, 0);
}

void ComNack() {
    ComTransmitPacket(MSG_ID_NACK, NULL, 0);
}