#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>
using BigFloat = boost::multiprecision::cpp_dec_float_50;

struct Complex {
    BigFloat real;
    BigFloat i;

    constexpr Complex operator+(const Complex& c) const {
        return {
            real + c.real,
            i + c.i
        };
    }

    constexpr Complex& operator+=(const Complex& c) {
        return *this = *this + c;
    }

    constexpr Complex operator*(const Complex& c) const {
        // (a + bi) * (c + di) = (ac − bd) + (ad + bc)i
        return {
            real * c.real - i * c.i,
            real * i + c.real * c.i
        };
    }

    constexpr Complex& operator*=(const Complex& c) {
        return *this = *this * c;
    }

};

int Mand(const Complex& c);
