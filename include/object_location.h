#include "SDL2/SDL.h"
#include "include/constant.h"

#ifndef OBJECT_LOCATION_H
#define OBJECT_LOCATION_H
extern SDL_Rect objectSrcLocation[28] = {
    {0, 0, 73, 65},     // REPLAY
    {76, 6, 90, 90},    // DINO_NORMAL
    {166, 2, 92, 27},   // CLOUD
    {954, 29, 381, 21}, // GAMEOVER
    {260, 15, 92, 67},  // BIRD_1
    {352, 2, 92, 60},   // BIRD_2
    {446, 2, 34, 70},   // TREE_MEDIUM_1
    {480, 2, 34, 70},   // TREE_MEDIUM_2
    {514, 2, 34, 70},   // TREE_MEDIUM_3
    {548, 2, 34, 70},   // TREE_MEDIUM_4
    {582, 2, 34, 70},   // TREE_MEDIUM_5
    {616, 2, 34, 70},   // TREE_MEDIUM_6
    // {650, 2, 34, 70},
    {652, 2, 50, 100},   // TREE_BIG_1
    {702, 2, 50, 100},   // TREE_BIG_2
    {752, 2, 50, 100},   // TREE_BIG_3
    {802, 2, 50, 100},   // TREE_BIG_4
    {850, 2, 102, 100},  // TREE_BIG_5
    {1338, 2, 88, 94},   // DINO_1
    {1426, 2, 88, 94},   // DINO_2
    {1514, 2, 88, 94},   // DINO_3
    {1602, 2, 88, 94},   // DINO_4
    {1782, 2, 88, 94},   // DINO_5
    {1866, 36, 118, 60}, // DINO_6
    {1984, 36, 118, 60}, // DINO_7
    {2, 104, 2400, 24}   // GROUND
};
extern SDL_Rect objectDestLocation[28] = {
    {0, 0, 73, 65},             // REPLAY
    {76, 6, 90, 90},            // DINO_NORMAL
    {166, 2, 92, 27},           // CLOUD
    {954, 29, 381, 21},         // GAMEOVER
    {SCREEN_WIDTH, 15, 92, 67}, // BIRD_1
    {SCREEN_WIDTH, 2, 92, 60},  // BIRD_2
    {SCREEN_WIDTH, 2, 34, 70},  // TREE_MEDIUM_1
    {SCREEN_WIDTH, 2, 34, 70},  // TREE_MEDIUM_2
    {SCREEN_WIDTH, 2, 34, 70},  // TREE_MEDIUM_3
    {SCREEN_WIDTH, 2, 34, 70},  // TREE_MEDIUM_4
    {SCREEN_WIDTH, 2, 34, 70},  // TREE_MEDIUM_5
    {SCREEN_WIDTH, 2, 34, 70},  // TREE_MEDIUM_6
    // {650, 2, 34, 70},
    {SCREEN_WIDTH, 2, 50, 100},  // TREE_BIG_1
    {SCREEN_WIDTH, 2, 50, 100},  // TREE_BIG_2
    {SCREEN_WIDTH, 2, 50, 100},  // TREE_BIG_3
    {SCREEN_WIDTH, 2, 50, 100},  // TREE_BIG_4
    {SCREEN_WIDTH, 2, 102, 100}, // TREE_BIG_5
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},            // DINO_1
    {1426, 2, 88, 94},           // DINO_2
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},
    {160, SCREEN_HEIGHT / 3 * 2 - 80, 88, 94},
    // {1514, 2, 88, 94},      // DINO_3
    // {1602, 2, 88, 94},      // DINO_4
    {1782, 2, 88, 94},                       // DINO_5
    {1866, 36, 118, 60},                     // DINO_6
    {1984, 36, 118, 60},                     // DINO_7
    {0, SCREEN_HEIGHT / 3 * 2 - 9, 2400, 24} // GROUND
};
#endif