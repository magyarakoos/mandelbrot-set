#pragma once

// #include <boost/multiprecision/cpp_dec_float.hpp>
// using BigFloat = boost::multiprecision::cpp_dec_float_50;

struct Complex {
    double real;
    double i;

    Complex operator+(const Complex& c) const {
        return {
            real + c.real,
            i + c.i
        };
    }

    Complex& operator+=(const Complex& c) {
        return *this = *this + c;
    }

    Complex operator*(const Complex& c) const {
        // (a + bi) * (c + di) = (ac − bd) + (ad + bc)i
        return {
            real * c.real - i * c.i,
            real * i + c.real * c.i
        };
    }

    Complex& operator*=(const Complex& c) {
        return *this = *this * c;
    }

};

int Mand(const Complex& c);
