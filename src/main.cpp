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
    BeginDrawing();
    
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

    EndDrawing();
}

void Tick() {
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

    bool up = IsKeyDown(KEY_UP), down = IsKeyDown(KEY_DOWN),

    else if () {

        auto [posX, posY] = GetMousePosition();

        float deltaX = posX / WIDTH, 
              deltaY = posY / HEIGHT;



        Draw();
    }

    else if () {

        

        Draw();
    }
}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE);

    for (int i = 0; i < 2; i++) {
        Draw();
    }

    while (!WindowShouldClose()) {
        Tick();
    }
}
