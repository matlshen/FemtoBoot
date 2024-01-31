#ifndef COM_TYPES_H_
#define COM_TYPES_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_COMMANDS        7

#define MSG_ID_CONN         0x50
#define MSG_ID_MEM_ERASE    0x51
#define MSG_ID_MEM_WRITE    0x52
#define MSG_ID_MEM_READ     0x53
#define MSG_ID_VERIFY       0x54
#define MSG_ID_RUN          0x55
#define MSG_ID_RESET        0x56
#define MSG_ID_ACK          0x57
#define MSG_ID_NACK         0x58

typedef enum {
    WAITING_FOR_COMMAND,
    SENDING_CONNECTION_PARAMS,
    MEM_ERASE,
    MEM_WRITE,
    MEM_READ,
    VERIFY,
    RUN,
} boot_state_typedef;


#ifdef __cplusplus
}
#endif

#endif /* COM_TYPES_H_ */