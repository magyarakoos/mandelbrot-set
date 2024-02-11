#include <raylib.h>
#include <string>
#include <time.h>
#include <assert.h>

#include "settings.h"

void Update() {

}

void Draw() {

}

int main() {

    srand((unsigned)time(nullptr));

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