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
    using namespace Utility;

    auto i2c_device = I2CDevice{&hi2c1, std::to_underlying(DevAddress::A2H_A1H_A0H)};

    auto iodir = IODIR{.io7 = std::to_underlying(Direction::OUTPUT),
                       .io6 = std::to_underlying(Direction::OUTPUT),
                       .io5 = std::to_underlying(Direction::OUTPUT),
                       .io4 = std::to_underlying(Direction::OUTPUT),
                       .io3 = std::to_underlying(Direction::OUTPUT),
                       .io2 = std::to_underlying(Direction::OUTPUT),
                       .io1 = std::to_underlying(Direction::OUTPUT),
                       .io0 = std::to_underlying(Direction::OUTPUT)};

    auto ipol = IPOL{.ip7 = std::to_underlying(PinPolarity::NORMAL),
                     .ip6 = std::to_underlying(PinPolarity::NORMAL),
                     .ip5 = std::to_underlying(PinPolarity::NORMAL),
                     .ip4 = std::to_underlying(PinPolarity::NORMAL),
                     .ip3 = std::to_underlying(PinPolarity::NORMAL),
                     .ip2 = std::to_underlying(PinPolarity::NORMAL),
                     .ip1 = std::to_underlying(PinPolarity::NORMAL),
                     .ip0 = std::to_underlying(PinPolarity::NORMAL)};

    auto gpinten = GPINTEN{.gpint7 = false,
                           .gpint6 = false,
                           .gpint5 = false,
                           .gpint4 = false,
                           .gpint3 = false,
                           .gpint2 = false,
                           .gpint1 = false,
                           .gpint0 = false};

    auto defval = DEFVAL{.def7 = std::to_underlying(PinState::LOGIC_LOW),
                         .def6 = std::to_underlying(PinState::LOGIC_LOW),
                         .def5 = std::to_underlying(PinState::LOGIC_LOW),
                         .def4 = std::to_underlying(PinState::LOGIC_LOW),
                         .def3 = std::to_underlying(PinState::LOGIC_LOW),
                         .def2 = std::to_underlying(PinState::LOGIC_LOW),
                         .def1 = std::to_underlying(PinState::LOGIC_LOW),
                         .def0 = std::to_underlying(PinState::LOGIC_LOW)};

    auto intcon = INTCON{.ioc7 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc6 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc5 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc4 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc3 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc2 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc1 = std::to_underlying(IntControl::COMPARE_DEFAULT),
                         .ioc0 = std::to_underlying(IntControl::COMPARE_DEFAULT)};

    auto iocon = IOCON{.bank = std::to_underlying(Bank::COMMON),
                       .mirror = std::to_underlying(Mirror::INT_PINS_CONNECTED),
                       .seqop = std::to_underlying(SequentialOp::ENABLED),
                       .disslw = std::to_underlying(SlewRate::DISABLED),
                       .haen = std::to_underlying(HAEnable::DISABLE),
                       .odr = std::to_underlying(OutputDrive::PUSH_PULL),
                       .intpol = std::to_underlying(PinPolarity::INVERSE)};

    auto gppu = GPPU{.pu7 = std::to_underlying(InputDrive::PULL_UP),
                     .pu6 = std::to_underlying(InputDrive::PULL_UP),
                     .pu5 = std::to_underlying(InputDrive::PULL_UP),
                     .pu4 = std::to_underlying(InputDrive::PULL_UP),
                     .pu3 = std::to_underlying(InputDrive::PULL_UP),
                     .pu2 = std::to_underlying(InputDrive::PULL_UP),
                     .pu1 = std::to_underlying(InputDrive::PULL_UP),
                     .pu0 = std::to_underlying(InputDrive::PULL_UP)};

    auto port_a_config = PortConfig{.iodir = iodir,
                                    .ipol = ipol,
                                    .gpinten = gpinten,
                                    .defval = defval,
                                    .intcon = intcon,
                                    .iocon = iocon,
                                    .gppu = gppu};

    auto port_b_config = port_a_config;

    auto mcp23017 = MCP23017::MCP23017{std::move(i2c_device), port_a_config, port_b_config};

    while (true) {
        mcp23017.set_pin_state(Port::A, PinNum::IO_0, PinState::LOGIC_HIGH);
        mcp23017.set_pin_state(Port::A, PinNum::IO_1, PinState::LOGIC_LOW);
        mcp23017.set_pin_state(Port::A, PinNum::IO_2, PinState::LOGIC_HIGH);
        mcp23017.set_pin_state(Port::A, PinNum::IO_3, PinState::LOGIC_LOW);
        mcp23017.set_pin_state(Port::A, PinNum::IO_4, PinState::LOGIC_HIGH);
        mcp23017.set_pin_state(Port::A, PinNum::IO_5, PinState::LOGIC_LOW);
        mcp23017.set_pin_state(Port::A, PinNum::IO_6, PinState::LOGIC_HIGH);
        mcp23017.set_pin_state(Port::A, PinNum::IO_7, PinState::LOGIC_LOW);
    }

    return 0;
}
