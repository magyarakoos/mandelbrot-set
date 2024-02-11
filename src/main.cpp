#include <cmath>
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>
#include <iostream>

#include "mandelbrot.h"
#include "settings.h"

double
    real_min = REAL_MIN,
    real_max = REAL_MAX,
    img_min = IMG_MIN,
    img_max = IMG_MAX
;

float tint = TINT;

void Draw() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            Complex c {
                real_min + (x / static_cast<double>(WIDTH)) * (real_max - real_min),
                img_min  + (y / static_cast<double>(HEIGHT)) * (img_max - img_min)
            };

            int it = Mand(c);

            // map the iteration number to a color
            float hue = fmod(fmod(static_cast<float>(it) / ITER, 1.0f) + tint, 1.0f);

            Color color = ColorFromHSV(hue * 360, 1.0f, 1.0f);

            DrawPixel(x, y, color);
        }
    }
}

void Update() {
    if (IsKeyDown(KEY_RIGHT)) {
        tint += TINT_STEP;
        if (tint > 1.0f) {
            tint = 0.0f;
        }

        Draw();
    }

    else if (IsKeyDown(KEY_LEFT)) {
        tint -= TINT_STEP;
        if (tint < 0.0f) {
            tint = 1.0f;
        }

        Draw();
    }

    else if (IsKeyDown(KEY_UP)) {
        //auto [posX, posY] = GetMousePosition();

        real_min += ZOOM_STEP;
        real_max -= ZOOM_STEP;
        img_min += ZOOM_STEP;
        img_max -= ZOOM_STEP;
    }
}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE);

    for (int i = 0; i < 2; i++) {
        BeginDrawing();
        Draw();
        EndDrawing();
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        Update();
        EndDrawing();
    }
}
