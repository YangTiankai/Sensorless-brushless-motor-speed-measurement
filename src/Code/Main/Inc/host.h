
#ifndef __HOST_H
#define __HOST_H

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"

typedef struct
{
    uint8_t id;
    uint32_t ms;
    uint16_t us;
    uint8_t cycle_ms;
    uint16_t pulse0;
    uint16_t pulse1;
    uint16_t pulse2;
    uint16_t pulse3;
} state_t, *p_state_t;

void gen_state_string(p_state_t pstate, uint8_t buff[], uint16_t *plen);
void gen_state_pack(p_state_t pstate, uint8_t buff[], uint16_t *plen);

#ifdef __cplusplus
}
#endif

#endif /* __HOST_H */


