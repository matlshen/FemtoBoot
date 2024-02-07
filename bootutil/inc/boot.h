#ifndef BOOT_H_
#define BOOT_H_

#include <stdint.h>
#include <stddef.h>

#include "com.h"
#include "boot_types.h"
#include "timer.h"
#include "flash.h"
#include "crc32.h"

#ifdef __cplusplus
extern "C" {
#endif

void BootStateMachine(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_H_ */