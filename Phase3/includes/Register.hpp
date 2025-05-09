#pragma once

#include <cstdint>

class Register {

private:
    uint16_t data = 0;

public:
        constexpr void operator=(uint16_t value) {
            data = value;
        }

        constexpr void operator+=(uint16_t value) {
            data += value;
        }

        constexpr void operator-=(uint16_t value) {
            data -= value;
        }

        constexpr operator uint16_t() const {
            return data;
        }
};