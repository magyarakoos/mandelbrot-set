#include <raylib.h>
#include <assert.h>

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

            unsigned char 
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