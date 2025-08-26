#include "enemy.h"
#include "map.h"


void enemy_init(Enemy *enemy) {
    enemy->vx = ENEMY_SPEED;
    enemy->vy = 0;
    enemy->is_dead = false;
}

void enemy_action(Enemy *enemy, int action) {

}

void enemy_check_collisions(Enemy *enemy) {
    if (enemy->is_dead) return;

    // the enemy can be in 4 blocks at once, therefore check all 4 tiles according to the map
    int tx1 = (enemy->x)/TILE_SIZE;
    int tx2 = (enemy->x + TILE_SIZE - 1)/TILE_SIZE;

    int ty1 = enemy->y/TILE_SIZE;
    int ty2 = (enemy->y + TILE_SIZE - 1)/TILE_SIZE;

    // check if tile below enemy
    if (enemy->vy > 0) {
        if (is_solid(enemy->x, enemy->y+ENEMY_SIZE) || is_solid(enemy->x+ENEMY_SIZE, enemy->y+ENEMY_SIZE)) {
            enemy->y = ty1*TILE_SIZE;
            enemy->vy = 0;
        } 
    }
    
    // check if tile above enemy
    if (enemy->vy < 0) {
        if (is_solid(enemy->x, enemy->y) || is_solid(enemy->x+ENEMY_SIZE, enemy->y)) {
            enemy->vy = 0;
            enemy->y = ty2*TILE_SIZE+1;
            }
    
    }

    // check if tile left and right of enemy
    if (enemy->vx < 0) {
        if (is_solid(enemy->x, enemy->y) || is_solid(enemy->x, enemy->y+ENEMY_SIZE - 1)) {
            enemy->x = (tx1+1)*TILE_SIZE + 1;
            enemy->vx = ENEMY_SPEED;
        }
    }
    if (enemy->vx > 0) {
        if (is_solid(enemy->x+ENEMY_SIZE, enemy->y) || is_solid(enemy->x+ENEMY_SIZE, enemy->y+ENEMY_SIZE - 1)) {
            enemy->x = (tx2-1)*TILE_SIZE - 1;
            enemy->vx = -ENEMY_SPEED;
        }
    }
}

void enemy_update(Enemy *enemy) {
    if (enemy->is_dead) return;
    enemy->x += enemy->vx;
    enemy->y += enemy->vy;
    enemy->vy += GRAVITY;
    if (enemy->y > MAP_HEIGHT*TILE_SIZE) {
        enemy_destroy(enemy);
    } 
}

void enemy_destroy(Enemy *enemy) {
    enemy->is_dead = true;
    enemy->x = 0;
    enemy->y = 0;
}