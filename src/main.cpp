#include <cmath>
#include <raylib.h>
#include <assert.h>
#include <complex>
#include <array>

using complex = std::complex<double>;

constexpr int
    FPS = 60,
    MAX_ITER = 200,
    WIDTH = 800,
    HEIGHT = 800,
;

double
    real_min = -2,
    real_max = 2,
    img_min = -2,
    img_max = 2
;

float
    TINT_STEP = 0.02f,
    tint = 0.64f
;

std::array<int, (size_t)WIDTH * (size_t)HEIGHT> cache;

void Draw(bool recalc = false) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            // map the iteration number to a color
            float hue = fmod(fmod(static_cast<float>(it) / ITER, 1.0f) + tint, 1.0f);
            Color color = ColorFromHSV(hue * 360, 1.0f, 1.0f);

            DrawPixel(x, y, color);
        }
    }

    EndDrawing();
}

int Mand(const complex& c) {
    int it = 0;
    complex z = 0;

    while (it < MAX_ITER && abs(z) < 2) {
        z = z * z + c;
        it++;
    }

    return it;
}

void Calculate() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            complex c {
                
            };

            cache[y][x] = Mand()
        }
    }
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
