#include "main.h"
#include "string.h"


void gen_state_string(p_state_t pstate, uint8_t buff[], uint16_t *plen)
{
    buff[0] = 0;

    sprintf
    (
        buff, "%.3f ms   %6d %6d %6d %6d\r\n", 
        pstate->ms + pstate->us / 1000.0,
        pstate->pulse0,
        pstate->pulse1,
        pstate->pulse2,
        pstate->pulse3
    );
    
    *plen = strlen(buff);
}

void gen_state_pack(p_state_t pstate, uint8_t buff[], uint16_t *plen)
{
    int cnt = 0;
    int i;
    uint8_t check = 0;

    buff[cnt++] = 0xff;
    buff[cnt++] = 0xff;
    buff[cnt++] = 0xff;
    buff[cnt++] = 0x00;

    buff[cnt++] = pstate->pulse0 & 0xff;
    buff[cnt++] = pstate->pulse0 >> 8;
    buff[cnt++] = pstate->pulse1 & 0xff;
    buff[cnt++] = pstate->pulse1 >> 8;
    buff[cnt++] = pstate->pulse2 & 0xff;
    buff[cnt++] = pstate->pulse2 >> 8;
    buff[cnt++] = pstate->pulse3 & 0xff;
    buff[cnt++] = pstate->pulse3 >> 8;
    
    for(i = 0; i <= cnt -1; i++)
    {
        check ^= buff[i];
    }

    buff[cnt++] = check;

    *plen = cnt;
}


