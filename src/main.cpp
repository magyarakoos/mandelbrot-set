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
                REAL_MIN + (x / WIDTH) * (REAL_MAX - REAL_MIN),
                IMG_MIN  + (y / HEIGHT) * (IMG_MAX - IMG_MIN)
            };

            int it = Mand(c);
            int color = 255 - (it * 255 / ITER);

            std::cerr << it << ' ' << color << '\n';

            DrawPixel(x + 150, y + 2, {
                (unsigned char)color, 
                (unsigned char)color, 
                (unsigned char)color, 
                255
            });
        }
    }
}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(1000, 1000, TITLE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        Update();
        Draw();
        EndDrawing();
    }
}