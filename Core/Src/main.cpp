#include "main.h"
#include "i2c.h"
#include "i2c_device.hpp"
#include "mcp23017.hpp"
#include "system_clock.h"
#include "usart.h"

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_I2C1_Init();

    using namespace MCP23017;

    MCP23017::MCP23017 mcp23017{};

    while (true) {
    }

    return 0;
}
