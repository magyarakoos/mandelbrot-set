#include <cmath>
#include <float.h>
#include <raylib.h>
#include <assert.h>
#include <array>

constexpr int
    FPS = 60,
    ITER = 200,
    WIDTH = 800,
    HEIGHT = 800
;

double
    real_min = -2,
    real_max = 2,
    IMG_MIN = -2,
    IMG_MAX = 2,
    ZOOM_STEP = 0.05
;

float
    TINT = 0.64f,
    TINT_STEP = 0.02f
;

std::array<int, (size_t)WIDTH * (size_t)HEIGHT> cache;

void Draw(bool recalc = false) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            int it;

            if (recalc) {
                // normalize the coordinates from 0 to 1
                // scale it to the range min..max
                Complex c {
                    real_min + (x / WIDTH) * (real_max - real_min),
                    img_min  + (y / HEIGHT) * (img_max - img_min)
                };

                // save it for later
                cache[y * WIDTH + x] = (it = Mand(c));
            } else {
                // being fast is about doing less
                it = cache[y * WIDTH + x];
            }

            // map the iteration number to a color
            float hue = fmod(fmod(static_cast<float>(it) / ITER, 1.0f) + tint, 1.0f);
            Color color = ColorFromHSV(hue * 360, 1.0f, 1.0f);

            DrawPixel(x, y, color);
        }
    }

    EndDrawing();
}

int Mand() {

}

void Calculate() {

}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");

    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }
}
