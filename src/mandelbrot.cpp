#include "mandelbrot.h"
#include "settings.h"

int Mand(const Complex& c) {
    int it = 0;
    Complex z {0, 0};

    while (it < ITER && abs(z.real) )
}