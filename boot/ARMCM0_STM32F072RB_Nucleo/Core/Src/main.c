#include "main.h"

#include "timer.h"
#include "com.h"
#include "uart.h"

void SystemClock_Config(void);

int main(void)
{
    LL_UtilHardwareInit();

    TimerInit();
    ComInit();

    uint16_t rx_msg_id;
    uint8_t rx_data[256];
    uint8_t rx_length;

		Boot_StatusTypeDef status = BOOT_OK;

    while (1) {
				status = ComReceivePacket(&rx_msg_id, rx_data, &rx_length, 5000);


				if (status == BOOT_OK)
		        ComTransmitPacket(rx_msg_id, rx_data, rx_length);
        //ComTransmit((uint8_t*)"Alive\r\n", 7, 10000);
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

}


void Error_Handler(void) {
    __disable_irq();
    while (1) {}
}