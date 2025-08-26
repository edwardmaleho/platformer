#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdbool.h>
#include "map.h"

#define PLAYER_SIZE 32
#define TILE_SIZE 32

#define INIT_X 200
#define INIT_Y 380

#define JUMP_VELOCITY 18
#define MOVE_VELOCITY 5

#define PLAYER_LEFT 0
#define PLAYER_RIGHT 1
#define PLAYER_UP 2
#define PLAYER_STOP_LEFT 3
#define PLAYER_STOP_RIGHT 4

#define GRAVITY 1

#define MAP_WIDTH 500
#define MAP_HEIGHT 30

typedef struct {
    int x; int y;
    int vx; int vy;
    bool on_ground;
} Player;

void player_init(Player *player);

void player_action(Player *player, int action);

void player_check_collisions(Player *player);

void player_update(Player *player);

#endif // PLAYER_H