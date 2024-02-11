#pragma once

struct Complex {
    long double real;
    long double i;

    constexpr Complex operator+(const Complex& c) const {
        return {
            real + c.real,
            i + c.i
        };
    }

    constexpr Complex& operator+=(const Complex& c) {
        return *this = *this + c;
    }

    constexpr Complex operator*(const Complex& c) {
        // (a + bi)^2 = (a2 − b2) + 2abi
        return {
            real * real - i * i,
            2 * real * i
        };
    }
};