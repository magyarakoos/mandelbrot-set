#include <cmath>
#include <float.h>
#include <raylib.h>
#include <assert.h>
#include <array>

#include "mandelbrot.h"
#include "settings.h"

double
    real_min = REAL_MIN,
    real_max = REAL_MAX,
    img_min = IMG_MIN,
    img_max = IMG_MAX
;

float tint = TINT;

std::array<std::array<int, (size_t)WIDTH>, (size_t)HEIGHT> cache;

void Draw(bool recalc = false) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            int it;

            if (recalc) {
                Complex c {
                    real_min + (x / WIDTH) * (real_max - real_min),
                    img_min  + (y / HEIGHT) * (img_max - img_min)
                };

                it = Mand(c);
            } else {
                it = cache[y][x];
            }

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
         up = IsKeyPressed(KEY_UP),
         down = IsKeyPressed(KEY_DOWN);

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
    }

    if (right || left) {
        Draw();
    }

    else if (up || down) {
        Draw(1);
    }
}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        Update();
        EndDrawing();
    }
}
