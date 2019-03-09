#ifndef CONSTANTS_H
#define CONSTANTS_H

// Block
char static const *BLOCK_BMP_FILE = "gfx/block.bmp";
int const BLOCK_SIZE = 16; // Block is 16x16 pixels
int const MAX_STATES = 4; // Maximum number of position

// Arena
int const ARENA_WIDTH = 12; // 12 columns
int const ARENA_HEIGHT = 21; // 21 rows

// Enumerated type definitions
enum Direction { left, right, down, rot };
enum Brick_type { I, J, L, S, Z, T, O };

// Gameplay
int const SPEED_ACCELERATE = 100; // Subtract to speed every new level
int const DEFAULT_SPEED  = 1000; // Level 1 speed, move once every second

#endif // CONSTANTS_H
