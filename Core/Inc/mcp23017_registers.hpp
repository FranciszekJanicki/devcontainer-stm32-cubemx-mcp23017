#ifndef MCP23017_REGISTERS_HPP
#define MCP23017_REGISTERS_HPP

#include "mcp23017_config.hpp"

#include <cstdint>

#define packed __attribute__((__packed__))

namespace MCP23017 {

    enum struct RA : std::uint8_t {
        IODIR = 0x00,
        IPOL = 0x01,
        GPINTEN = 0x02,
        DEFVAL = 0x03,
        INTCON = 0x04,
        IOCON = 0x05,
        GPPU = 0x06,
        INTF = 0x07,
        INTCAP = 0x08,
        GPIO = 0x09,
        OLAT = 0x0A,
    };

    [[nodiscard]] inline std::uint8_t separate_bank_port_to_reg_address(Port const port, RA const reg_address) noexcept
    {
        switch (port) {
            case Port::A:
                return std::to_underlying(reg_address);
            case Port::B:
                return std::to_underlying(reg_address) + 10U;
            default:
                return 0U;
        }
    }

    [[nodiscard]] inline std::uint8_t common_bank_port_to_reg_address(Port const port, RA const reg_address) noexcept
    {
        switch (port) {
            case Port::A:
                return std::to_underlying(reg_address);
            case Port::B:
                return std::to_underlying(reg_address) + 1U;
            default:
                return 0U;
        }
    }

    [[nodiscard]] inline std::uint8_t
    port_bank_to_reg_address(Port const port, Bank const bank, RA const reg_address) noexcept
    {
        switch (bank) {
            case Bank::SEPARATE:
                return separate_bank_port_to_reg_address(port, reg_address);
            case Bank::COMMON:
                return common_bank_port_to_reg_address(port, reg_address);
            default:
                return 0U;
        }
    }

    struct IODIR {
        bool io7 : 1;
        bool io6 : 1;
        bool io5 : 1;
        bool io4 : 1;
        bool io3 : 1;
        bool io2 : 1;
        bool io1 : 1;
        bool io0 : 1;
    } packed;

    struct IPOL {
        bool ip7 : 1;
        bool ip6 : 1;
        bool ip5 : 1;
        bool ip4 : 1;
        bool ip3 : 1;
        bool ip2 : 1;
        bool ip1 : 1;
        bool ip0 : 1;
    } packed;

    struct GPINTEN {
        bool gpint7 : 1;
        bool gpint6 : 1;
        bool gpint5 : 1;
        bool gpint4 : 1;
        bool gpint3 : 1;
        bool gpint2 : 1;
        bool gpint1 : 1;
        bool gpint0 : 1;
    } packed;

    struct DEFVAL {
        bool def7 : 1;
        bool def6 : 1;
        bool def5 : 1;
        bool def4 : 1;
        bool def3 : 1;
        bool def2 : 1;
        bool def1 : 1;
        bool def0 : 1;
    } packed;

    struct INTCON {
        bool ioc7 : 1;
        bool ioc6 : 1;
        bool ioc5 : 1;
        bool ioc4 : 1;
        bool ioc3 : 1;
        bool ioc2 : 1;
        bool ioc1 : 1;
        bool ioc0 : 1;
    } packed;

    struct IOCON {
        bool bank : 1;
        bool mirror : 1;
        bool seqop : 1;
        bool disslw : 1;
        bool haen : 1;
        bool odr : 1;
        bool intpol : 1;
        bool : 1;
    } packed;

    struct GPPU {
        bool pu7 : 1;
        bool pu6 : 1;
        bool pu5 : 1;
        bool pu4 : 1;
        bool pu3 : 1;
        bool pu2 : 1;
        bool pu1 : 1;
        bool pu0 : 1;
    } packed;

    struct INTF {
        bool int7 : 1;
        bool int6 : 1;
        bool int5 : 1;
        bool int4 : 1;
        bool int3 : 1;
        bool int2 : 1;
        bool int1 : 1;
        bool int0 : 1;
    } packed;

    struct INTCAP {
        bool icp7 : 1;
        bool icp6 : 1;
        bool icp5 : 1;
        bool icp4 : 1;
        bool icp3 : 1;
        bool icp2 : 1;
        bool icp1 : 1;
        bool icp0 : 1;
    } packed;

    struct GPIO {
        bool gp7 : 1;
        bool gp6 : 1;
        bool gp5 : 1;
        bool gp4 : 1;
        bool gp3 : 1;
        bool gp2 : 1;
        bool gp1 : 1;
        bool gp0 : 1;
    } packed;

}; // namespace MCP23017

#endif // MCP23017_REGISTERS_HPP