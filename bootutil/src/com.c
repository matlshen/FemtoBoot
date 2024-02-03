#include "com.h"

// Make sure only one protocol is used at a time
#if defined(USE_CAN) && defined(USE_UART)
    #error "Only one protocol can be used at a time"
#endif

#ifdef USE_PC_SERIAL
    #include "serial.h"
#endif

Boot_StatusTypeDef ComInit(void) {
    #ifdef USE_CAN
    CANInit();
    #endif

    #ifdef USE_UART
    return UARTInit();
    #endif

    #ifdef USE_PC_SERIAL
    return SerialInit(SERIAL_PORT, SERIAL_BAUDRATE);
    #endif
}

Boot_StatusTypeDef ComDeInit(void) {
    #ifdef USE_CAN
    CANDeinit();
    #endif

    #ifdef USE_UART
    return UARTDeinit();
    #endif

    #ifdef USE_PC_SERIAL
    return SerialDeinit();
    #endif
}

inline Boot_StatusTypeDef ComTransmitByte(uint8_t data, uint32_t timeout_ms) {
    #ifdef USE_CAN
    CANTransmit(data, length);
    #endif

    #ifdef USE_UART
    return UARTTransmitByte(data, timeout_ms);
    #endif

    #ifdef USE_PC_SERIAL
    return SerialTransmit(data);
    #endif
}

inline Boot_StatusTypeDef ComReceiveByte(uint8_t *data, uint32_t timeout_ms) {
    #ifdef USE_CAN
    CANReceive(data, length);
    #endif

    #ifdef USE_UART
    return UARTReceiveByte(data, timeout_ms);
    #endif

    #ifdef USE_PC_SERIAL
    return SerialReceive(data);
    #endif
}

Boot_StatusTypeDef ComTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length) {
    Boot_StatusTypeDef status = BOOT_OK;

    status = ComTransmitByte((uint8_t)msg_id, BYTE_TIMEOUT_MS);
    if (status != BOOT_OK)
        return status;
    status = ComTransmitByte((uint8_t)(msg_id >> 8), BYTE_TIMEOUT_MS);
    if (status != BOOT_OK)
        return status;

    status = ComTransmitByte((uint8_t)length, BYTE_TIMEOUT_MS);
    if (status != BOOT_OK)
        return status;

    for (size_t i = 0; i < length; i++) {
        status = ComTransmitByte(data[i], BYTE_TIMEOUT_MS);
        if (status != BOOT_OK)
            return status;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef ComReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length, uint32_t timeout_ms) {
    Boot_StatusTypeDef status = BOOT_OK;

    status = ComReceiveByte((uint8_t *)msg_id, timeout_ms); 
    if (status != BOOT_OK)
        return BOOT_TIMEOUT;
    status = ComReceiveByte(((uint8_t *)msg_id) + 1, BYTE_TIMEOUT_MS);
    if (status != BOOT_OK)
        return BOOT_FORMAT_ERROR;

    status = ComReceiveByte(((uint8_t *)length), BYTE_TIMEOUT_MS);
    if (status != BOOT_OK)
        return BOOT_FORMAT_ERROR;

    for (size_t i = 0; i < *length; i++) {
        status = ComReceiveByte(&data[i], BYTE_TIMEOUT_MS);
        if (status != BOOT_OK)
            return BOOT_FORMAT_ERROR;
    }

    return BOOT_OK;
}

inline Boot_StatusTypeDef ComAck() {
    return ComTransmitPacket(MSG_ID_ACK, NULL, 0);
}

inline Boot_StatusTypeDef ComNack() {
    return ComTransmitPacket(MSG_ID_NACK, NULL, 0);
}