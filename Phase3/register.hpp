#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <cstdint>

class Register {
public:
    constexpr void operator==(uint16_t value);
    constexpr void operator+=(uint16_t value);
    constexpr void operator-=(uint16_t value);
    constexpr operator uint16_t() const;
};

#endif