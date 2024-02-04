#include "win_serial.h"

#include <stdio.h>
#include <windows.h>

const char* serial_port = "\\\\.\\COM10";

HANDLE hSerial;

Boot_StatusTypeDef SerialInit(int baudrate) {
    hSerial = CreateFile(
        serial_port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0
    );
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to open serial port %s\n", serial_port);
        return BOOT_ERROR;
    } else {
        printf("Serial port opened successfully\n");
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error: Unable to get serial port state\n");
        return BOOT_ERROR;
    }

    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error: Cannot set device parameters\n");
        return BOOT_ERROR;
    }

    // Set timeout settings
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 100;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 100;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error: Unable to set serial port timeouts\n");
        return BOOT_ERROR;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef SerialDeInit() {
    if (CloseHandle(hSerial)) {
        //printf("Serial port closed successfully\n");
        return BOOT_OK;
    } else {
        //printf("Error: Unable to close serial port\n");
        return BOOT_ERROR;
    }

    // Shouldn't get here
    return BOOT_ERROR;
}

Boot_StatusTypeDef SerialTransmit(uint8_t *data, uint8_t length) {
    DWORD bytes_written;

    if (!WriteFile(hSerial, data, length, &bytes_written, NULL)) {
        //printf("Error: Unable to write to serial port\n");
        return BOOT_ERROR;
    }

    if (bytes_written != length) {
        //printf("Error: Unable to write all bytes to serial port\n");
        return BOOT_ERROR;
    }

    return BOOT_OK;
}

Boot_StatusTypeDef SerialReceive(uint8_t *data, uint8_t length) {
    DWORD bytes_read;

    if (!ReadFile(hSerial, data, length, &bytes_read, NULL)) {
        //printf("Error: Unable to read from serial port\n");
        return BOOT_ERROR;
    }

    if (bytes_read != length) {
        //printf("Error: Unable to read all bytes from serial port\n");
        return BOOT_ERROR;
    }

    return BOOT_OK;
}
