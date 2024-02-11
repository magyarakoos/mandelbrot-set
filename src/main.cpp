#include <raylib.h>
#include <string>
#include <time.h>
#include <assert.h>

#include "settings.h"

void Update() {

}

void Draw() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            
        }
    }
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