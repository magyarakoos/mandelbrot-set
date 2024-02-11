#include <raylib.h>
#include <string>
#include <time.h>
#include <assert.h>

#include "settings.h"

int main() {

    srand((unsigned)time(nullptr));

    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE);
    
    Game game;

    while (!game.TriggerClose()) {
        game.Tick();
    }

    return 0;
}