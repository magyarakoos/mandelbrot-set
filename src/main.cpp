#include <cmath>
#include <raylib.h>
#include <assert.h>
#include <complex>
#include <array>
#include <string>

using complex = std::complex<double>;

constexpr int
    FPS = 60,
    MAX_ITER = 200,
    WIDTH = 800,
    HEIGHT = 800
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
                real_min + (real_max - real_min) * x / (WIDTH - 1),
                img_min + (img_max - img_min) * y / (HEIGHT - 1)
            };

            cache[y * WIDTH + x] = Mand(c);
        }
    }
}

void Tick(bool update) {
    if (update) {
        Calculate();
    }

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            float hue = fmod(
                fmod(
                    static_cast<float>(cache[y * WIDTH + x]) / 
                    MAX_ITER, 1.0f
                ) + tint, 
                1.0f
            );

            Color color = ColorFromHSV(hue * 360, 1.0f, 1.0f);

            DrawPixel(x, y, color);
        }
    }

    DrawText("tint: " + std::to_string(tint) + " ", )
}

bool GetInput() {

    if (IsKeyPressed(KEY_RIGHT)) {

        tint += TINT_STEP;
        if (tint > 1) {
            tint = 0;
        }

        return 0;
    }

    if (IsKeyPressed(KEY_LEFT)) {

        tint -= TINT_STEP;
        if (tint < 0) {
            tint = 1;
        }

        return 0;
    }
}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");

    Tick(1);

    while (!WindowShouldClose()) {
        BeginDrawing();

        bool update = GetInput();

        Tick(update);

        EndDrawing();
    }
}
