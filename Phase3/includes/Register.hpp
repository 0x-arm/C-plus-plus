#pragma once

#include <cstdint>
#include "Saturated.hpp"

class Register {

private:
    uint16_t data = 0;

public:
        constexpr void operator=(uint16_t value) {
            data = saturated(value);
        }

        constexpr void operator+=(uint16_t value) {
            data = saturated(data += value);
        }

        constexpr void operator-=(uint16_t value) {
            data = saturated(data -= value);
        }

        constexpr operator uint16_t() const {
            return data;
        }
};