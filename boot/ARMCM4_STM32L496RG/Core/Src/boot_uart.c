#include "boot_config.h"
#include "timer.h"

#include "stm32l4xx.h"
#include "stm32l4xx_ll_crs.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_gpio.h"

#ifdef USE_UART

/*
 * STM32L496RG CAN pin configurations
 * UART1:
 *  -RX: PA10, PB7
 *  -TX: PA9, PB6
 * UART2:
 *  -RX: PA3
 *  -TX: PA2
 * UART3:
 *  -RX: PB11, PC5
 *  -TX: PB10, PC4
 * UART4:
 *  -RX: PA1, PC11
 *  -TX: PA0, PC10
 * UART5:
 *  -RX: PD2
 *  -TX: PC12
*/
// TODO: Fix this later
#define UARTx USART2
#define LL_UARTx LL_APB1_GRP1_PERIPH_USART2


// TODO: Support other uart configurations
Boot_StatusTypeDef UARTInit(void) {
    LL_USART_InitTypeDef USART_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
    /**USART2 GPIO Configuration
     PA2   ------> USART2_TX
    PA3   ------> USART2_RX
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART2, &USART_InitStruct);
    LL_USART_Enable(USART2);

    // Disable rx to prevent buffer overrun
    LL_USART_DisableDirectionRx(UARTx);

    return BOOT_OK;
}

Boot_StatusTypeDef UARTTransmitByte(uint8_t data, uint32_t timeout_ms) {
    TimerUpdate();
    uint32_t timeout = boot_time_ms + timeout_ms;

    while (!LL_USART_IsActiveFlag_TXE(UARTx) && boot_time_ms < timeout)
        TimerUpdate();
    if (boot_time_ms >= timeout) {
        return BOOT_TIMEOUT;
    }

    LL_USART_TransmitData8(UARTx, data);

    return BOOT_OK;
}

Boot_StatusTypeDef UARTReceiveByte(uint8_t *data,  uint32_t timeout_ms) {
    // Enable rx
    LL_USART_EnableDirectionRx(UARTx);

    TimerUpdate();
    uint32_t timeout = boot_time_ms + timeout_ms;

    while (!LL_USART_IsActiveFlag_RXNE(UARTx) && boot_time_ms < timeout)
        TimerUpdate();
    if (boot_time_ms >= timeout) {
        return BOOT_TIMEOUT;
    }

    *data = LL_USART_ReceiveData8(UARTx);

    // Disable rx to prevent buffer overrun
    LL_USART_DisableDirectionRx(UARTx);

    return BOOT_OK;
}

#endif // USE_UART