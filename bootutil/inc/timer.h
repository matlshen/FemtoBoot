#ifndef TIM_H_
#define TIM_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "boot_config.h"
#include "ll_util.h"

extern uint32_t boot_time_ms;

void TimerInit(void);
void TimerUpdate(void);
void TimerDelay(uint32_t delay_ms);
void TimerTimeoutReset(uint32_t timeout_ms);
void TimerReset(void);


#ifdef __cplusplus
}
#endif

#endif /* TIM_H_ */