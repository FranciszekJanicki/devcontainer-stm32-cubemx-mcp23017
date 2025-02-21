#include "main.h"
#include "i2c.h"
#include "system_clock.h"
#include "usart.h"

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_I2C1_Init();

    while (true) {
    }

    return 0;
}
