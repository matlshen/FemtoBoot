#ifndef TIM_H_
#define TIM_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "boot_config.h"
#include "ll_util.h"

extern volatile uint32_t boot_time_ms;

void TimInit();
void TimUpdate();


#ifdef __cplusplus
}
#endif

#endif /* TIM_H_ */