#include "Game.h"
#include "Masks.h"

Game::Game() : level_(1), score_(0), speed_(DEFAULT_SPEED), last_update_(0), current_brick_(0), next_brick_(0),
    pushing_left_(0), pushing_right_(0), rotating_(0), game_over_(false) {
    ZEngine *engine = ZEngine::GetInstance();

    // The arena coordinates
    int arena_width_px = ARENA_WIDTH * BLOCK_SIZE;
    int arena_height_px = ARENA_HEIGHT * BLOCK_SIZE;

    // Draw in the center of the game screen
    rect_.x = (engine->DisplayWidth() / 2) - (arena_width_px / 2);
    rect_.y = (engine->DisplayHeight() / 2) - (arena_height_px / 2);
    rect_.w = arena_width_px;
    rect_.h = arena_height_px;

    // The arena mask, for collision detection and clearing lines
    mask_ = arena;

    // The bricks in the arena
    int bpp = engine->DisplayDepth(); // Color depth

    // Temporary surface where we draw the brick
    SDL_Surface *temp = SDL_CreateRGBSurface(SDL_HWSURFACE, arena_width_px, arena_height_px, bpp, 0, 0, 0, 0);
    // Fill with green; to be used as color key later
    SDL_FillRect(temp, NULL, SDL_MapRGB(temp->format, 128, 128, 128));
    // SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 0, 255, 0));
    arena_.Attach(temp);
    this->update_arena();
}

Game::~Game() {
    delete current_brick_;
    delete next_brick_;
}

void Game::draw_arena() {
    // Draw the bricks
    arena_.Draw(rect_.x, rect_.y);
}

void Game::update_arena() {
    SDL_Surface *block = SDL_LoadBMP(BLOCK_BMP_FILE);
    SDL_Surface *temp = arena_.Surface();
    SDL_FillRect(temp, NULL, SDL_MapRGB(temp->format, 128, 128, 128));
        
    // Update when a brick lands and when clearing lines
    for (int i = 0 ; i < ARENA_HEIGHT; i++) {
        for (int j = 0; j < ARENA_WIDTH; j++) {
            if (mask_[i][j]) {
                // Modify to allow multi-colored blocks
                SDL_Rect to;
                to.x = j * BLOCK_SIZE;
                to.y = i * BLOCK_SIZE;
                SDL_BlitSurface(block, NULL, temp, &to);
            }
        }
    }
    arena_.Reload();
}

void Game::update_mask() {
    if (current_brick_ == 0) { return; }
    current_brick_->copy_mask(mask_);
}

void Game::handle_keyboard() {
    ZEngine *engine = ZEngine::GetInstance();

    if (engine->KeyIsPressed(SDLK_UP) && (!rotating_ || rotating_ == 10)) {
        if (!current_brick_->collide(mask_, rot)) { current_brick_->rotate(); }
        if (!rotating_) { rotating_ = 1; }
    } else if (engine->KeyIsPressed(SDLK_UP)) {
        rotating_++;
    } else if (!engine->KeyIsPressed(SDLK_UP)) {
        rotating_ = 0;
    }

    // Push to the left
    if (engine->KeyIsPressed(SDLK_LEFT) && (!pushing_left_ || pushing_left_ == 10)) {
        if (!current_brick_->collide(mask_, left)) { current_brick_->move_left(); }
        if (!pushing_left_) { pushing_left_ = 1; }
    } else if (engine->KeyIsPressed(SDLK_LEFT)) {
        pushing_left_++;
    } else if (!engine->KeyIsPressed(SDLK_LEFT)) {
        pushing_left_ = 0;
    }

    // Push to the right
    if (engine->KeyIsPressed(SDLK_RIGHT) && (!pushing_right_ || pushing_right_ == 10)) {
        if (!current_brick_->collide(mask_, right)) { current_brick_->move_right(); }
        if (!pushing_right_) { pushing_right_ = 1; }
    } else if (engine->KeyIsPressed(SDLK_RIGHT))
        pushing_right_++;
    else if (!engine->KeyIsPressed(SDLK_RIGHT))
        pushing_right_ = 0;

    // Push towards the ground
    if (engine->KeyIsPressed(SDLK_DOWN)) {
        if (!current_brick_->collide(mask_, down)) { current_brick_->move_down(); }
    }

    // Drop
    if (engine->KeyPress(SDLK_SPACE) && engine->KeyIsPressed(SDLK_SPACE)) {
        this->instant_drop();
    }

    // if ( engine->KeyIsPressed(SDLK_s) ) engine->ToggleFullscreen();
}

void Game::instant_drop() {
    while(!current_brick_->collide(mask_, down)) { current_brick_->move_down(); }
}

void Game::clear_lines() {
    // Marks the rows
    int count = 0;
    int clear_line[ARENA_HEIGHT - 1];
    int buffer_field[ARENA_HEIGHT][ARENA_WIDTH];
    
    for (int i = 0; i < ARENA_HEIGHT - 1; i++) {
        // Reset variables
        count = 0;
        clear_line[i] = 0;

        // Count the number of blocks in the row
        for (int j = 0; j < ARENA_WIDTH; j++) {
            if (mask_[i][j]) { count++; }
        }

        // If there's 12 blocks, the row's full.
        if (count == ARENA_WIDTH) {
            // Mark the row for clearing and count the cleared rows
            clear_line[i] = 1;
        }
    }

    // The filled rows are marked, so now let's delete them

    // Clear the bufferfield
    for (int i = 0; i < ARENA_HEIGHT; i++) {
        for (int j = 0; j < ARENA_WIDTH; j++) {
            buffer_field[i][j] = 0;
        }
    }

    // Initialize the row counters for both fields
    for (int i = count = ARENA_HEIGHT - 2; i >= 0; i--) {
        // Move one line from the playfield to the bufferfield
        for (int j = 0; j < ARENA_WIDTH; j++) {
            buffer_field[count][j] = mask_[i][j];
        }

        // If the line isn't meant to be cleared ...
        if ( !clear_line[i] ) {
            // ... don't overwrite it
            count--;
        }
    }

    // Move the bufferfield back to the playfield
    for (int i = 0; i < ARENA_HEIGHT - 1; i++) {
        for (int j = 1; j < ARENA_WIDTH - 1; j++) {
            mask_[i][j] = buffer_field[i][j];
        }
    }
}

void Game::new_game() {
    // Initialize some data
    level_ = 1;
    score_ = 0;
    speed_ = DEFAULT_SPEED;
    last_update_ = 0;
    pushing_left_ = 0;
    pushing_right_ = 0;
    rotating_ = 0;
    game_over_ = false;

    // Initialize the arena mask
    for (int i = 0; i < ARENA_HEIGHT; i++) {
        for (int j = 0; j < ARENA_WIDTH; j++) {
            if (j == 0) { mask_[i][j] = 8; } // Left wall
            else if (j == ARENA_WIDTH - 1) { mask_[i][j] = 8; } // Right wall
            else if (i == ARENA_HEIGHT - 1) { mask_[i][j] = 8; } // Floor
            else { mask_[i][j] = 0; }
        }
    }

    // Remove the bricks from memory
    delete current_brick_;
    delete next_brick_;

    current_brick_ = 0;
    next_brick_    = 0;

    // Update the arena image
    this->update_arena();
}

void Game::play() {
    ZEngine *engine = ZEngine::GetInstance();

    if (engine->KeyIsPressed(SDLK_ESCAPE)) { engine->RequestQuit(); } // Quit game
    if (engine->KeyIsPressed(SDLK_n)) { this->new_game(); } // New game
    if (game_over_) { return; }

    // Check score, switch level if necessary, change speed

    // Next and current bricks
    if (current_brick_ == NULL) { // The very first brick
        current_brick_ = new Brick(rect_.x, rect_.y, -1, ARENA_WIDTH / 2 - 2);
        next_brick_ = new Brick(rect_.x, rect_.y, -1, ARENA_WIDTH / 2 - 2);
    } else if ((SDL_GetTicks() > last_update_ + speed_ ) && (current_brick_->collide(mask_, down))) { // The current brick has landed
        this->update_mask();
        delete current_brick_;
        current_brick_ = next_brick_;

        // Game over
        if (current_brick_->collide(mask_, Direction(-1))) {
            game_over_ = true;
            return;
        }

        next_brick_ = new Brick(rect_.x, rect_.y, -1, ARENA_WIDTH / 2 - 2);
        this->clear_lines();
        this->update_arena();
    }

    // Falling brick
    if (SDL_GetTicks() > last_update_ + speed_) {
        last_update_ = SDL_GetTicks();
        if (!current_brick_->collide(mask_, down)) { current_brick_->move_down(); }
    }

    if (current_brick_ != NULL) {
        this->handle_keyboard();
        this->draw_arena();
        current_brick_->draw();
    }
}
