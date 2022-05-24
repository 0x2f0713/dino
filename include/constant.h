#ifndef CONSTANT_H
#define CONSTANT_H

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define WINDOW_TITLE "Dino"

#define CENTER_HORIZONTAL(x) SCREEN_WIDTH  / 2 - x / 2
#define CENTER_VERTICAL(x) SCREEN_HEIGHT / 2 - x / 2


#define V_JUMP -12
#define ACCELERATION 2
#define RANDOM_ENEMY_INTERVAL rand() % 10 + (1) * 100;

#define TRASH_PIXEL 20

#define DINO_STATUS_RUNNING 0
#define DINO_STATUS_JUMPING 1
#define DINO_STATUS_DIE     2


#endif