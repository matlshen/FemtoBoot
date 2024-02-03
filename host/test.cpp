#include <iostream>
#include <string>
#include <windows.h>

HANDLE hSerial;

bool SetupSerialPort(const char* portName, DWORD baudrate) {
    hSerial = CreateFile(portName,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port" << std::endl;
        return false;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting device state" << std::endl;
        CloseHandle(hSerial);
        return false;
    }

    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting device parameters" << std::endl;
        CloseHandle(hSerial);
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    // Start serial program
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " COMx" << std::endl;
        return 1;
    }

    if (!SetupSerialPort(argv[1], CBR_9600)) {
        return 1;
    }

    std::cout << "Serial port opened successfully" << std::endl;
    std::cout << "Enter data to transmit ('q' to quit): ";

    std::string input;
    while (getline(std::cin, input)) {
        if (input == "q")
            break;
        WriteFile(hSerial, input.c_str(), input.size(), NULL, NULL);
    }

    CloseHandle(hSerial);
    return 0;
}