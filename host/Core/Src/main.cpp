#include <iostream>
#include <synchapi.h>
#include <string>
#include "win_serial.h"
#include "BootTarget.hpp"

int main(int argc, char* argv[])
{
    Boot_StatusTypeDef status = BOOT_OK;

    BootTarget target;

    while (1) {
        status = target.Connect();

        // If connected to target successfully
        if (status != BOOT_OK) {
            return -1;
        }

        Sleep(5000);
    }

    return 0;
}