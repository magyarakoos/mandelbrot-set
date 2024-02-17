#include <cmath>
#include <float.h>
#include <raylib.h>
#include <assert.h>
#include <array>

// #include <boost/multiprecision/cpp_dec_float.hpp>
// using BigFloat = boost::multiprecision::cpp_dec_float_50;

int
    FPS = 60,
    ITER = 200
;

double
    WIDTH = 800,
    HEIGHT = 800,
    REAL_MIN = -2,
    REAL_MAX = 2,
    IMG_MIN = -2,
    IMG_MAX = 2,
    ZOOM_STEP = 0.05
;

float
    // pink: 0.76f
    // light blue: 0.5f
    // green: 0.32f
    // yellow: 0.14f
    // orange:0.04f
    // red: 0.0f

    TINT = 0.64f,
    TINT_STEP = 0.02f
;

float 
    tint = TINT
;

// yes, I am terrified of the C raw array
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

        Draw();
    }

    if (left) {
        tint -= TINT_STEP;
        if (tint < 0.0f) {
            tint = 1.0f;
        }

        Draw();
    }

    if (up != down) {
        double 
            deltaX = GetMouseX() / WIDTH,
            deltaY = GetMouseY() / HEIGHT;

        if (up) {

            real_min += (ZOOM_STEP * deltaX) * zoom_level;
            real_max -= ZOOM_STEP * (1 - deltaX) * zoom_level;
            img_min += ZOOM_STEP * deltaY * zoom_level;
            img_max -= ZOOM_STEP * (1 - deltaY) * zoom_level;
        }

        if (down) {

            real_min -= ZOOM_STEP * deltaX * zoom_level;
            real_max += ZOOM_STEP * (1 - deltaX) * zoom_level;
            img_min -= ZOOM_STEP * deltaY * zoom_level;
            img_max += ZOOM_STEP * (1 - deltaY) * zoom_level;
        }

        Draw(1);
    }
}

int main() {
    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE);
    
    // before the first input is pressed, make sure to render the whole screen
    for (int i = 0; i < 10 && !WindowShouldClose(); i++) {
        BeginDrawing();
        Draw(1);
        EndDrawing();
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        Update();
        EndDrawing();
    }
}
