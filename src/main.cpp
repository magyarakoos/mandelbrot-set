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
//            unsigned char color = 255 - (it * 255 / ITER);

            float hue = fmod(static_cast<float>(it) / ITER, 1.0f);
            Color color = ColorFromHSV(hue * 360, 1.0f, 1.0f);

            DrawPixel(x, y, color);
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