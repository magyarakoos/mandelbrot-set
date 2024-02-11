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

    
};