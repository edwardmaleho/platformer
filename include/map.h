#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdbool.h>
#include "enemy.h"

#define MAP_WIDTH 500
#define MAP_HEIGHT 30

#define TILE_SIZE 32

#define MAX_ENEMIES 20

#define GROUND 1
#define PLAYER 2
#define ENEMY  3

extern int game_map[MAP_HEIGHT][MAP_WIDTH];

extern Enemy enemies[MAX_ENEMIES];
extern size_t enemy_count;

void parse_map(char* map_name);

void set_player_position(int *x, int *y);

bool is_solid(int x, int y);

bool is_enemy(int x, int y, int *e);

#endif // MAP_H