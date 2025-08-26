#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>

#define ENEMY_SIZE 32
#define TILE_SIZE 32

#define ENEMY_SPEED 3

#define GRAVITY 1

typedef struct {
    int x; int y;
    int vx; int vy;
    bool is_dead;
} Enemy;

void enemy_init(Enemy *enemy);

void enemy_action(Enemy *enemy, int action);

void check_collisions(Enemy *enemy);

void enemy_update(Enemy *enemy);

void enemy_destroy(Enemy *enemy);

#endif // ENEMY_H