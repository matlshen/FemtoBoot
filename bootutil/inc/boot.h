#ifndef BOOT_H_
#define BOOT_H_

#include <stdint.h>
#include <stddef.h>

#include "com.h"
#include "com_types.h"
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif

void BootStateMachine(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_H_ */