#ifndef BRICK_H
#define BRICK_H

#include "Constants.h"
#include "ZEngine.h"

using namespace ZE;

class Brick {
public:
    // Force the client to initialize all necessary data
    Brick(int rel_x, int rel_y, int row, int col);  // Creates a random brick type
    ~Brick() {}

    // Movement and rotation
    void move_left() { col_--; }
    void move_right() { col_++; }
    void move_down() { row_++; } // Fall
    void rotate();
    void draw();
    bool collide(short (*arena)[ARENA_WIDTH], Direction where);
    void copy_mask(short (*arena)[ARENA_WIDTH]);

private:
    // Private methods
    void set_mask(); // Call after type_ is initialized
    void create_images();

    ZImage brick_[MAX_STATES];
    Brick_type type_;

    short const (*mask_)[4][4]; // Holds the mask
    int const rel_x_; // X-coordinate of the arena
    int const rel_y_; // Y-coordinate of the arena
    int row_; // Current row
    int col_; // Current column
    int state_; // Current rotation position
};

#endif // BRICK_H
