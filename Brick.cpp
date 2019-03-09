#include "Brick.h"
#include "Masks.h"

#include <stdlib.h>
#include <time.h>

// Create a random brick
Brick::Brick(int rel_x, int rel_y, int row, int col) : row_(row), col_(col), state_(0), rel_x_(rel_x), rel_y_(rel_y) {
    ZEngine *engine = ZEngine::GetInstance();

    // Random brick type
    srand(int(time(0)));
    type_ = Brick_type(rand() % 7);

    // The mask depending on the type
    this->set_mask();

    // Create the brick images
    this->create_images();
}

void Brick::set_mask() {
    if (type_ == I) {
        mask_ = I_brick;
    } else if (type_ == J) {
        mask_ = J_brick;
    } else if (type_ == L) {
        mask_ = L_brick;
    } else if (type_ == S) {
        mask_ = S_brick;
    } else if (type_ == Z) {
        mask_ = Z_brick;
    } else if (type_ == T) {
        mask_ = T_brick;
    } else if (type_ == O) {
        mask_ = O_brick;
    }
}

void Brick::create_images() {
    ZEngine *engine = ZEngine::GetInstance();

    int wh = MAX_STATES * BLOCK_SIZE; // Width/height
    int bpp  = engine->DisplayDepth(); // Color depth

    SDL_Surface *block = SDL_LoadBMP(BLOCK_BMP_FILE); // The 'building block'

    // Create 4 SDL surfaces for the 4 positions
    SDL_Surface *temp[MAX_STATES];
    for (int i = 0; i < MAX_STATES; i++) {
        temp[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, wh, wh, bpp, 0, 0, 0, 0); // Temporary surface where we draw the brick
        SDL_FillRect(temp[i], NULL, SDL_MapRGB(temp[i]->format, 0, 255, 0)); // Fill with green, to be used as color key later
        SDL_SetColorKey(temp[i], SDL_SRCCOLORKEY, SDL_MapRGB(temp[i]->format, 0, 255, 0));
    }

    //create the images using the block and the mask
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (mask_[i][j][k]) {
                    SDL_Rect to;
                    to.x = k * BLOCK_SIZE;
                    to.y = j * BLOCK_SIZE;
                    SDL_BlitSurface(block, NULL, temp[i], &to);
                }
            }
        }
        brick_[i].Attach(temp[i]);
//      brick_[i].SetColorKey(0, 255, 0); // Doesn't work, contact ZEngine author
    }
}

void Brick::rotate() {
    state_++;
    if (state_ > MAX_STATES - 1) {
        state_ = 0;
    }
}

void Brick::draw() {
    int to_x = col_ * BLOCK_SIZE + rel_x_;
    int to_y = row_ * BLOCK_SIZE + rel_y_;
    brick_[state_].Draw(to_x, to_y);
}

bool Brick::collide(short (*arena)[ARENA_WIDTH], Direction where) {
    int state = state_;
    int row = row_;
    int col = col_;

    if (where == left ) { col--; }
    if (where == right) { col++; }
    if (where == down ) { row++; }
    if (where == rot ) { state++; }
    if (state > MAX_STATES   - 1) { state = 0; }

    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            if (i + row < 0 || j + col < 0 || i + row > ARENA_HEIGHT - 1 || j + col > ARENA_WIDTH - 1 ) {
                // Dont check for values out of array bounds
                continue;
            }
            if (mask_[state][i][j]) {
                if (arena[i + row][j + col]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Brick::copy_mask(short (*arena)[ARENA_WIDTH]) {
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            if (mask_[state_][i][j]) {
                arena[i + row_][j + col_] = mask_[state_][i][j];
            }
        }
    }
}
