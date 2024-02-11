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
    
    std::cerr << "DRAW\n";

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

            // std::cerr << it << ' ';
            // std::cerr << real_min << ' ' << real_max << ' ' << img_min << ' ' << img_max << '\n';

            DrawPixel(x, y, color);
        }
    }

    EndDrawing();
}

void Tick() {
    bool update = 0;

    if (IsKeyDown(KEY_RIGHT)) {
        update = 1;
        std::cerr << "RIGHT ";
        tint += TINT_STEP;
        if (tint > 1.0f) {
            tint = 0.0f;
        }
    }

    else if (IsKeyDown(KEY_LEFT)) {
        update = 1;
        std::cerr << "LEFT ";
        tint -= TINT_STEP;
        if (tint < 0.0f) {
            tint = 1.0f;
        }
    }

    else if (IsKeyDown(KEY_UP)) {
        update = 1;
        auto [posX, posY] = GetMousePosition();

        float deltaX = posX / WIDTH, 
              deltaY = posY / HEIGHT;

        std::cerr << "UP ";
        real_min += ZOOM_STEP * deltaX;
        img_min += ZOOM_STEP * deltaY; 

        real_max -= ZOOM_STEP * (WIDTH - deltaX);
        img_max -= ZOOM_STEP * (HEIGHT - deltaY);
    }

    else if (IsKeyDown(KEY_DOWN)) {
        update = 1;
        auto [posX, posY] = GetMousePosition();

        float deltaX = posX / WIDTH, 
              deltaY = posY / HEIGHT;

        std::cerr << "DOWN ";
        real_min -= ZOOM_STEP * deltaX;
        img_min -= ZOOM_STEP * deltaY; 

        real_max += ZOOM_STEP * (WIDTH - deltaX);
        img_max += ZOOM_STEP * (HEIGHT - deltaY);
    }

    if (update) {
        Draw();
        std::cerr << "DRAWCALL ";
        std::cerr << real_min << ' ' << real_max << ' ' << img_min << ' ' << img_max << '\n';
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
        Draw();
        //std::cerr << real_min << ' ' << real_max << ' ' << img_min << ' ' << img_max << ' ' << tint << '\n';
        //Tick();
    }
}
