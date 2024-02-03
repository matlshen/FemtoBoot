#include "boot_config.h"

#include "stm32l4xx.h"

#ifdef USE_CAN

/*
 * STM32L496RG CAN pin configurations
 * CAN1:
 *  -RX: PA11, PB8
 *  -TX: PA12, PB9
 * CAN2:
 *  -RX: PB5, PB12
 *  -TX: PB6, PB13
*/
#if (CAN_RX_PIN == PA11) && (CAN_TX_PIN == PA12) || \
    (CAN_RX_PIN == PB8) && (CAN_TX_PIN == PB9)
    #define CANx CAN1
#elif (CAN_RX_PIN == PB5) && (CAN_TX_PIN == PB6) || \
        (CAN_RX_PIN == PB12) && (CAN_TX_PIN == PB13)
    #define CANx CAN2
#else
    #error "Invalid CAN pin configuration"
#endif
// TODO: Support more baudrates
// Target prescaled value = 8MHz for maximum 1Mbps
# if (CAN_BAUDRATE == 125000)
    #define CAN_PRESCALER 8
    #define CAN_T1 CAN_BS1_13TQ
    #define CAN_T2 CAN_BS2_2TQ
# elif (CAN_BAUDRATE == 250000)
    #define CAN_PRESCALER 4
    #define CAN_T1 CAN_BS1_13TQ
    #define CAN_T2 CAN_BS2_2TQ
# elif (CAN_BAUDRATE == 500000)
    #define CAN_PRESCALER 2
    #define CAN_T1 CAN_BS1_13TQ
    #define CAN_T2 CAN_BS2_2TQ
# elif (CAN_BAUDRATE == 1000000)
    #define CAN_PRESCALER 1
    #define CAN_T1 CAN_BS1_13TQ
    #define CAN_T2 CAN_BS2_2TQ
# else
    #error "Invalid CAN baudrate"
#endif

CAN_HandleTypeDef hcan;

void CANInit(void) {
    hcan.Instance = CANx;
    hcan.Init.Prescaler = CAN_PRESCALER;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_T1;
    hcan.Init.TimeSeg2 = CAN_T2;
    hcan.Init.TimeTriggeredMode = DISABLE;
    hcan.Init.AutoBusOff = DISABLE;
    hcan.Init.AutoWakeUp = DISABLE;
    hcan.Init.AutoRetransmission = ENABLE; // TODO: See if this is necessary
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_DeInit(&hcan) != HAL_OK) {
        // TODO: Error_Handler();
    }

    // Set filter to accept everything
    CAN_FilterTypeDef filter;
    filter.FilterBank = 0;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.FilterIdHigh = 0x0000;
    filter.FilterIdLow = 0x0000;
    filter.FilterMaskIdHigh = 0x0000;
    filter.FilterMaskIdLow = 0x0000;
    filter.FilterFIFOAssignment = CAN_RX_FIFO0;
    filter.FilterActivation = ENABLE;
    filter.SlaveStartFilterBank = 14;
    if (HAL_CAN_ConfigFilter(&hcan, &filter) != HAL_OK) {
        // TODO: Error_Handler();
    }
}

void CANTransmitPacket(uint16_t msg_id, uint8_t *data, size_t length) {
    CAN_TxHeaderTypeDef header = {0};
    header.StdId = msg_id;
    header.IDE = CAN_ID_STD;
    header.RTR = CAN_RTR_DATA;
    header.DLC = length;
    header.TransmitGlobalTime = DISABLE;

    uint32_t mailbox;
    if (HAL_CAN_AddTxMessage(&hcan, &header, data, &mailbox) != HAL_OK) {
        // TODO: Error_Handler();
    }
}

void CANReceivePacket(uint16_t *msg_id, uint8_t *data, size_t *length) {
    CAN_RxHeaderTypeDef header;

    // Check if rx mailbox has anything
    if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0) {
        *length = 0;
        return;
    }

    // If mailbox contains an rx message
    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &header, data) != HAL_OK) {
        // TODO: Error_Handler();
    }

    *msg_id = header.StdId;
    *length = header.DLC;
}


#endif // USE_CAN