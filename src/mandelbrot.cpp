#include <stdlib.h>

#include "mandelbrot.h"
#include "settings.h"

int Mand(const Complex& c) {
    int it = 0;
    Complex z {0, 0};

    while (it < ITER && abs(z.real) <= 2 && abs(z.i) <= 2) {
        // f(z) = z^2 + c
        z *= z;
        z += c;
    }

    
}