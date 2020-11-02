#include "sounder/sounder.h"
#include "board/board.h"

void sounder_alaram_system_failure(void)
{
  SOUNDER_PWM_START();
}

void sounder_stop(void)
{
  SOUNDER_PWM_STOP();
}
