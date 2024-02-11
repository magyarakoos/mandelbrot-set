#include <raylib.h>
#include <string>
#include <time.h>

int main() {

    srand((unsigned)time(nullptr));

    assert(!GetWindowHandle());

    SetTargetFPS(FPS);
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    
    Game game;

    while (!game.TriggerClose()) {
        game.Tick();
    }

    return 0;
}