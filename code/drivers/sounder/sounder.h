#ifndef SOUNDER_H
#define SOUNDER_H

#include "types/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sound the total system failure alarm
 *
 */
void sounder_play_system_failure(void);

/**
 * @brief Stop playing the alarm
 *
 */
void sounder_stop(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SOUNDER_H */
