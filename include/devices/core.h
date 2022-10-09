#include <Arduino.h>

//软件重启
void systemReset() {
    __set_FAULTMASK(1);
    HAL_NVIC_SystemReset();
}
