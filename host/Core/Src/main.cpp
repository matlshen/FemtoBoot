#include <iostream>
#include <synchapi.h>
#include "com.h"

int main(int argc, char* argv[])
{
    Boot_StatusTypeDef status = BOOT_OK;

    status = ComInit();
    if (status != BOOT_OK) {
        return 1;
    }

    uint8_t data[20] = "Hello World!\r\n";
    uint8_t length = 14;

    uint16_t rx_msg_id;
    uint8_t rx_data[20];
    uint8_t rx_length;

    while (1) {
        ComTransmitPacket(0x2829, data, length);

        status = ComReceivePacket(&rx_msg_id, rx_data, &rx_length, 10000);

        if (status == BOOT_OK)
            std::cout << "Received: " << rx_data;
        else
            std::cout << "No data received" << std::endl;

        Sleep(1000);
    }

    return 0;
}