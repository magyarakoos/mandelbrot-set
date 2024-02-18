#include <cmath>
#include <raylib.h>
#include <assert.h>
#include <complex>
#include <iomanip>
#include <array>
#include <string>

using complex = std::complex<double>;

constexpr int
    FPS = 60,
    MAX_ITER = 100,
    WIDTH = 800,
    HEIGHT = 800
;

double
    real_min = -2,
    real_max = 2,
    img_min = -2,
    img_max = 2
;

constexpr float 
    TINT_STEP = 0.02f
;

float 
    tint = 0.64f,
    zoom_step = 0.06f
;

std::array<int, (size_t)WIDTH * (size_t)HEIGHT> cache;

int Mand(const complex& c) {
    int it = 0;
    complex z = 0;

    while (it < MAX_ITER && z.real() < 2 && z.imag() < 2) {
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

std::string to_string(float f, int decimals) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimals) << f;
    return oss.str();
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

    std::string s = 
        to_string(tint,     2) + "  " + 
        to_string(real_min, 2) + "  " +
        to_string(real_max, 2) + "  " +
        to_string(img_min,  2) + "  " +
        to_string(img_max,  2)
    ;

    DrawText(s.c_str(), 8, 5, 30, WHITE);
}

bool GetInput() {

    bool update = 0;

    if (IsKeyDown(KEY_RIGHT)) {

        tint += TINT_STEP;
        if (tint > 1) {
            tint = 0;
        }
    }

    if (IsKeyDown(KEY_LEFT)) {

        tint -= TINT_STEP;
        if (tint < 0) {
            tint = 1;
        }
    }

    if (IsKeyDown(KEY_UP) != IsKeyDown(KEY_DOWN)) {

        float
            deltaX = static_cast<float>(GetMouseX()) / WIDTH,
            deltaY = static_cast<float>(GetMouseY()) / HEIGHT
        ;

        int flip = (IsKeyDown(KEY_UP) ? 1 : -1);

        real_min += flip * zoom_step * deltaX;
        img_min  += flip * zoom_step * deltaY;
        real_max -= flip * zoom_step * (1 - deltaX);
        img_max  -= flip * zoom_step * (1 - deltaY);

        zoom_step *= 0.99f;

        update = 1;
    }

    return update;
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
