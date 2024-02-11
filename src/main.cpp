#include <cmath>
#include <float.h>
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
                real_min + (x / WIDTH) * (real_max - real_min),
                img_min  + (y / HEIGHT) * (img_max - img_min)
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
    bool right = IsKeyDown(KEY_RIGHT),
         left = IsKeyDown(KEY_LEFT),
         up = IsKeyDown(KEY_UP),
         down = IsKeyDown(KEY_DOWN);

    if (right) {
        tint += TINT_STEP;
        if (tint > 1.0f) {
            tint = 0.0f;
        }
    }

    if (left) {
        tint -= TINT_STEP;
        if (tint < 0.0f) {
            tint = 1.0f;
        }
    }

    if (up != down) {
        double 
            deltaX = GetMouseX() / WIDTH,
            deltaY = GetMouseY() / HEIGHT;

        if (up) {
            real_min += ZOOM_STEP * deltaX;
            real_max -= ZOOM_STEP * (1 - deltaX);
            img_min += ZOOM_STEP * deltaY;
            img_max -= ZOOM_STEP * (1 - deltaY);
        }

        if (down) {
            real_min -= ZOOM_STEP * deltaX;
            real_max += ZOOM_STEP * (1 - deltaX);
            img_min -= ZOOM_STEP * deltaY;
            img_max += ZOOM_STEP * (1 - deltaY);
        }

        real_min = std::max(real_min, REAL_MIN);
        real_max = std::min(real_max, REAL_MAX);
        img_min  = std::max(img_min, IMG_MIN);
        img_max  = std::min(img_max, IMG_MAX);
    }

    if (right || left || up || down) {
        Draw();
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
