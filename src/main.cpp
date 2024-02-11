#include <cmath>
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>
#include <iostream>

#include "mandelbrot.h"
#include "settings.h"

long double
    real_min = REAL_MIN,
    real_max = REAL_MAX,
    img_min = IMG_MIN,
    img_max = IMG_MAX
;

float tint = TINT;

void Update() {
    if (IsKeyPressed(KEY_UP)) {
        tint += 0.01;
        if (tint > 1.0f) {
            tint = 1.0f;
        }
    }

    else if (IsMouseButtonPressed(KEY_DOWN)) {
        tint -= 0.01;
        if (tint < 0.0f) {
            tint = 0.0f;
        }
    }
}

void Draw() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            Complex c {
                real_min + (x / static_cast<long double>(WIDTH)) * (real_max - real_min),
                img_min  + (y / static_cast<long double>(HEIGHT)) * (img_max - img_min)
            };

            int it = Mand(c);

            // map the iteration number to a color
            float hue = fmod(fmod(static_cast<float>(it) / ITER, 1.0f) + tint, 1.0f);

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
