#include "mcp23017.hpp"
#include "utility.hpp"
#include <bit>
#include <utility>

namespace MCP23017 {

    MCP23017::MCP23017(I2CDevice&& i2c_device,
                       PortConfig const& port_a_config,
                       PortConfig const& port_b_config) noexcept :
        bank_{static_cast<Bank>(port_a_config.iocon.bank && port_b_config.iocon.bank)},
        i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(port_a_config, port_b_config);
    }

    MCP23017::~MCP23017() noexcept
    {
        this->deinitialize();
    }

    PinState MCP23017::get_pin_state(Port const port, PinNum const pin_num) const noexcept
    {
        return (this->get_gpio_register(port, this->bank_) & (1U << std::to_underlying(pin_num))) > 0
                   ? PinState::LOGIC_HIGH
                   : PinState::LOGIC_LOW;
    }

    void MCP23017::set_pin_state(Port const port, PinNum const pin_num, PinState const pin_state) const noexcept
    {
        this->set_gpio_register(port,
                                this->bank_,
                                pin_state == PinState::LOGIC_HIGH
                                    ? this->get_gpio_register(port, this->bank_) | (1U << std::to_underlying(pin_num))
                                    : this->get_gpio_register(port, this->bank_) &
                                          ~(1U << std::to_underlying(pin_num)));
    }

    void MCP23017::toggle_pin(Port const port, PinNum const pin_num) const noexcept
    {
        this->set_gpio_register(port,
                                this->bank_,
                                this->get_gpio_register(port, this->bank_) ^ (1U << std::to_underlying(pin_num)));
    }

    void MCP23017::set_pin(Port const port, PinNum const pin_num) const noexcept
    {
        this->set_pin_state(port, pin_num, PinState::LOGIC_HIGH);
    }

    void MCP23017::reset_pin(Port const port, PinNum const pin_num) const noexcept
    {
        this->set_pin_state(port, pin_num, PinState::LOGIC_LOW);
    }

    void MCP23017::initialize_port(Port const port, PortConfig const& port_config) const noexcept
    {
        auto const bank = static_cast<Bank>(port_config.iocon.bank);
        this->set_iodir_register(port, bank, port_config.iodir);
        this->set_ipol_register(port, bank, port_config.ipol);
        this->set_gpinten_register(port, bank, port_config.gpinten);
        this->set_defval_register(port, bank, port_config.defval);
        this->set_intcon_register(port, bank, port_config.intcon);
        this->set_gppu_register(port, bank, port_config.gppu);
    }

    void MCP23017::initialize(PortConfig const& port_a_config, PortConfig const& port_b_config) noexcept
    {
        this->initialize_port(Port::A, port_a_config);
        this->initialize_port(Port::B, port_b_config);
        this->initialized_ = true;
    }

    void MCP23017::deinitialize() noexcept
    {
        this->initialized_ = false;
    }

    IODIR MCP23017::get_iodir_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<IODIR>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::IODIR)));
    }

    void MCP23017::set_iodir_register(Port const port, Bank const bank, IODIR const iodir) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::IODIR),
                                     std::bit_cast<std::uint8_t>(iodir));
    }

    IPOL MCP23017::get_ipol_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<IPOL>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::IPOL)));
    }

    void MCP23017::set_ipol_register(Port const port, Bank const bank, IPOL const ipol) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::IPOL), std::bit_cast<std::uint8_t>(ipol));
    }

    GPINTEN MCP23017::get_gpinten_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<GPINTEN>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::GPINTEN)));
    }

    void MCP23017::set_gpinten_register(Port const port, Bank const bank, GPINTEN const gpinten) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::GPINTEN),
                                     std::bit_cast<std::uint8_t>(gpinten));
    }

    DEFVAL MCP23017::get_defval_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<DEFVAL>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::DEFVAL)));
    }

    void MCP23017::set_defval_register(Port const port, Bank const bank, DEFVAL const defval) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::DEFVAL),
                                     std::bit_cast<std::uint8_t>(defval));
    }

    INTCON MCP23017::get_intcon_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<INTCON>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::INTCON)));
    }

    void MCP23017::set_intcon_register(Port const port, Bank const bank, INTCON const intcon) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::INTCON),
                                     std::bit_cast<std::uint8_t>(intcon));
    }

    IOCON MCP23017::get_iocon_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<IOCON>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::IOCON)));
    }

    void MCP23017::set_iocon_register(Port const port, Bank const bank, IOCON const iocon) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::IOCON),
                                     std::bit_cast<std::uint8_t>(iocon));
    }

    GPPU MCP23017::get_gppu_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<GPPU>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::GPPU)));
    }

    void MCP23017::set_gppu_register(Port const port, Bank const bank, GPPU const gppu) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::GPPU), std::bit_cast<std::uint8_t>(gppu));
    }

    INTF MCP23017::get_intf_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<INTF>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::INTF)));
    }

    INTCAP MCP23017::get_intcap_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<INTCAP>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::INTCAP)));
    }

    GPIO MCP23017::get_gpio_register(Port const port, Bank const bank) const noexcept
    {
        return std::bit_cast<GPIO>(this->i2c_device_.read_byte(port_bank_to_reg_address(port, bank, RA::GPIO)));
    }

    void MCP23017::set_gpio_register(Port const port, Bank const bank, GPIO const gpio) const noexcept
    {
        this->i2c_device_.write_byte(port_bank_to_reg_address(port, bank, RA::GPIO), std::bit_cast<std::uint8_t>(gpio));
    }

}; // namespace MCP23017