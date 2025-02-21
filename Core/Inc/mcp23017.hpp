#ifndef MCP23017_HPP
#define MCP23017_HPP

#include "i2c_device.hpp"
#include "mcp23017_config.hpp"
#include "mcp23017_registers.hpp"

namespace MCP23017 {

    struct MCP23017 {
    public:
        using I2CDevice = Utility::I2CDevice;

        MCP23017() noexcept = default;
        MCP23017(I2CDevice&& i2c_device,
                 IODIR const iodir,
                 IPOL const ipol,
                 GPINTEN const gptinten,
                 DEFVAL const defval,
                 INTCON const intcon,
                 IOCON const iocon,
                 GPPU const gppu) noexcept;

        MCP23017(MCP23017 const& other) = delete;
        MCP23017(MCP23017&& other) noexcept = default;

        MCP23017& operator=(MCP23017 const& other) = delete;
        MCP23017& operator=(MCP23017&& other) noexcept = default;

        ~MCP23017() noexcept;

    private:
        I2CDevice i2c_device_{};
    };

}; // namespace MCP23017

#endif // MCP23017_HPP