#include "Game.h"

bool init() {
    ZEngine *engine = ZEngine::GetInstance();
    engine->SetupDisplay(640, 480, 32, false);
//  engine->SetupDisplay(640, 480, 32, true);
    engine->SetupSound(22050, true);
    engine->SetDesiredFramerate(60);
    return engine->CreateDisplay("TINT is not Tetris");
}

void play() {
    ZEngine *engine = ZEngine::GetInstance();
    Game game;

    do {
        engine->CheckEvents(); // Always check events

        if (engine->IsActive()) {
            engine->Clear();
            game.play();
            engine->Update(); // Without this nothing would update
        } else {
            engine->Delay(10); // Good to avoid 100% cpu usage
        }
    } while (!engine->QuitRequested());
}

int main(int argc, char *argv[]) {
    if (init()) {
        play();
    }

    ZEngine::ReleaseInstance();
    return 0;
}
