#include "serial.h"

#include "windows.h"

HANDLE hSerial;

Boot_StatusTypeDef SerialInit(const char* port, int baudrate) {
    hSerial = CreateFile(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0
    );
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf("Error: Unable to open serial port\n");
        return BOOT_ERROR;
    } else {
        fprintf("Serial port opened successfully\n");
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf("Error: Unable to get serial port state\n");
        return BOOT_ERROR;
    }

    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf("Error: Cannot set device parameters\n");
        return BOOT_ERROR;
    }

    // Set timeout settings
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf("Error: Unable to set serial port timeouts\n");
        return BOOT_ERROR;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef SerialTransmitByte(uint8_t data) {
    if (!WriteFile(hSerial, data, 1, NULL, NULL)) {
        fprintf("Error: Unable to write to serial port\n");
        return BOOT_ERROR;
    }
    return BOOT_OK;
}

Boot_StatusTypeDef SerialReceiveByte(uint8_t *data) {
    if (!ReadFile(hSerial, data, 1, NULL, NULL)) {
        fprintf("Error: Unable to read from serial port\n");
        return BOOT_ERROR;
    }
    return BOOT_OK;
}

Boot_StatusTypeDef SerialDeInit() {
    if (CloseHandle(hSerial)) {
        fprintf("Serial port closed successfully\n");
        return BOOT_OK;
    } else {
        fprintf("Error: Unable to close serial port\n");
        return BOOT_ERROR;
    }
}