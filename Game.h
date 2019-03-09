#ifndef GAME_H
#define GAME_H

#include "Brick.h"
#include "Constants.h"

#include "ZEngine.h"
using namespace ZE;

class Game {
public:
    Game();
    ~Game();

    void play();

private:
    // Private methods
    void draw_arena();
    void draw_next_brick();
    void clear_lines();
    void update_mask(); // Updates the mask
    void update_arena(); // Updates arena_
    void handle_keyboard();
    void instant_drop();
    void new_game();

    // Private data
    Brick *current_brick_; // The current falling brick;
    Brick *next_brick_; // The next brick to fall
    int level_; // Determines the speed of descent
    int score_; // Determines the level
    int speed_;
    int last_update_; // Time when the last descent occured
    short (*mask_)[ARENA_WIDTH];
    SDL_Rect rect_;
    ZImage arena_;
    int pushing_left_;
    int pushing_right_;
    int rotating_;
    bool game_over_;
};

#endif // GAME_H
