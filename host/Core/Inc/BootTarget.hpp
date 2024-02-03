#include <stdint.h>
#include <stddef.h>
#include "boot_types.h"
#include "boot_config.h"

class BootTarget {
public:
    BootTarget(const char* port);
    ~BootTarget();

    void Connect();
    void Reset();
private:
    uint16_t msg_id;
    uint8_t msg_data[256];
    size_t msg_len;
};