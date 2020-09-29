
#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CYCLE_PACK_MS   10

#define LIST_LEFT   4
#define MAX_LIST   (2 * LIST_LEFT + 1)


#define MAX_RPM (40000.0)
#define MIN_CYCLE_US   (6.0E7 / 7.0 / MAX_RPM)

#ifdef __cplusplus
}
#endif

#endif


