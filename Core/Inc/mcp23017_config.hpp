#ifndef MCP23017_CONFIG_HPP
#define MCP23017_CONFIG_HPP

#include <cstdint>

namespace MCP23017 {

    enum struct DevAddress : std::uint16_t {
        A2H_A1H_A0H = 0b0100111,
        A2H_A1H_A0L = 0b0100110,
        A2H_A1L_A0H = 0b0100101,
        A2L_A1H_A0H = 0b0100011,
        A2H_A1L_A0L = 0b0100100,
        A2L_A1H_A0L = 0b0100010,
        A2L_A1L_A0H = 0b0100001,
        A2L_A1L_A0L = 0b0100000,
    };

    enum struct Port : std::uint8_t {
        A = 0x00,
        B = 0x01,
    };

    enum struct PinNum : std::uint8_t {
        IO_7 = 0x07,
        IO_6 = 0x06,
        IO_5 = 0x05,
        IO_4 = 0x04,
        IO_3 = 0x03,
        IO_2 = 0x02,
        IO_1 = 0x01,
        IO_0 = 0x00,
    };

    enum struct Direction : std::uint8_t {
        INPUT = 0x01,
        OUTPUT = 0x00,
    };

    enum struct PinPolarity : std::uint8_t {
        INVERSE = 0x01,
        NORMAL = 0x00,
    };

    enum struct Bank : std::uint8_t {
        SEPARATE = 0x01,
        COMMON = 0x00,
    };

    enum struct Mirror : std::uint8_t {
        INT_PINS_CONNECTED = 0x01,
        INT_PINS_DISCONNECTED = 0x00,
    };

    enum struct SequentialOp : std::uint8_t {
        DISABLED = 0x01,
        ENABLED = 0x00,
    };

    enum struct SlewRate : std::uint8_t {
        DISABLED = 0x01,
        ENABLED = 0x00,
    };

    enum struct HAEnable : std::uint8_t {
        ENABLE = 0x01,
        DISABLE = 0x00,
    };

    enum struct OutputDrive : std::uint8_t {
        OPEN_DRAIN = 0x01,
        PUSH_PULL = 0x00,
    };

    enum struct PinState : std::uint8_t {
        LOGIC_HIGH = 0x01,
        LOGIC_LOW = 0x00,
    };

    enum struct IntEnable : std::uint8_t {
        ENABLED = 0x01,
        DISABLED = 0x00,
    };

    enum struct IntMode : std::uint8_t {
        FALLING = 0x01,
        RISING = 0x00,
    };

    enum struct IntControl : std::uint8_t {
        COMPARE_DEFAULT = 0x01,
        COMPARE_PREV = 0x00,
    };

    enum struct IntCapture : std::uint8_t {
        HIGH_ACTIVE = 0x01,
        LOW_ACTIVE = 0x00,
    };

    enum struct InputDrive : std::uint8_t {
        PULL_UP = 0x01,
        PULL_DOWN = 0x00,
    };

    enum struct IntFlag : std::uint8_t {
        OCCURED = 0x01,
        PENDING = 0x00,
    };

}; // namespace MCP23017

#endif // MCP23017_CONFIG_HPP