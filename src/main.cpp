#include <raylib.h>
#include <assert.h>
#include <iostream>

#include "mandelbrot.h"
#include "settings.h"

void Update() {

}

void Draw() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            Complex c {
                REAL_MIN + (x / static_cast<long double>(WIDTH)) * (REAL_MAX - REAL_MIN),
                IMG_MIN  + (y / static_cast<long double>(HEIGHT)) * (IMG_MAX - IMG_MIN)
            };

            int it = Mand(c);
            int color = 255 - (it * 255 / ITER);

            DrawPixel(x, y, {
                static_cast<unsigned char>(color), 
                static_cast<unsigned char>(color), 
                static_cast<unsigned char>(color), 
                255
            });
        }
    }
}


int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        Update();
        Draw();
        EndDrawing();
    }
}