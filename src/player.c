#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "player.h"

void player_init(Player *player) {
    if (!player)  {
        printf("Invalid player\n");
        return;
    }
    player->x = INIT_X;
    player->y = INIT_Y;
    player->vx = 0;
    player->vy = 0;
}

void player_action(Player *player, int action) {
    switch (action)
    {
        case PLAYER_LEFT:
            player->vx = -MOVE_VELOCITY;
            break;
        case PLAYER_RIGHT:
            player->vx = MOVE_VELOCITY;
            break;
        case PLAYER_UP:
            if (player->on_ground == true) {
                player->vy = -JUMP_VELOCITY;
                player->on_ground = false;
            }
            break;
        case PLAYER_STOP_LEFT:
            if (player->vx < 0)
                player->vx = 0;
            break;
        case PLAYER_STOP_RIGHT:
            if (player->vx > 0)
                player->vx = 0;
            break;
    }
}

void player_check_collisions(Player *player) {
    // the player can be in 4 blocks at once, therefore check all 4 tiles according to the map
    int tx1 = (player->x)/TILE_SIZE;
    int tx2 = (player->x + TILE_SIZE - 1)/TILE_SIZE;

    int ty1 = player->y/TILE_SIZE;
    int ty2 = (player->y + TILE_SIZE - 1)/TILE_SIZE;

    // collision with enemy
    int e;
    if (player->vx < 0) {
        if (is_enemy(player->x, player->y, &e) || is_enemy(player->x, player->y+PLAYER_SIZE - 1, &e)) {
            player_init(player);
        }
    }
    if (player->vx > 0) {
        if (is_enemy(player->x+PLAYER_SIZE, player->y, &e) || is_enemy(player->x+PLAYER_SIZE, player->y+PLAYER_SIZE - 1, &e)) {
            player_init(player);
        }
    }
    if (player->vy > 0) {
        if (is_enemy(player->x, player->y+PLAYER_SIZE, &e) || is_enemy(player->x+PLAYER_SIZE, player->y+PLAYER_SIZE, &e)) {
            enemy_destroy(&enemies[e]);
        } 
    }

    // check if tile below player
    if (player->vy > 0) {
        if (is_solid(player->x, player->y+PLAYER_SIZE) || is_solid(player->x+PLAYER_SIZE, player->y+PLAYER_SIZE)) {
            player->y = ty1*TILE_SIZE;
            player->vy = 0;
            player->on_ground = 1;
        } 
    }

    // check if tile above player
    if (player->vy < 0) {
        if (is_solid(player->x, player->y) || is_solid(player->x+PLAYER_SIZE, player->y)) {
            player->vy = 0;
            player->y = ty2*TILE_SIZE+1;
         }
 
    }

    // check if tile left and right of player
    if (player->vx < 0) {
        if (is_solid(player->x, player->y) || is_solid(player->x, player->y+PLAYER_SIZE - 1)) {
            player->x = (tx1+1)*TILE_SIZE + 1;
            player->vx = 0;
        }
    }
    if (player->vx > 0) {
        if (is_solid(player->x+PLAYER_SIZE, player->y) || is_solid(player->x+PLAYER_SIZE, player->y+PLAYER_SIZE - 1)) {
            player->x = (tx2-1)*TILE_SIZE - 1;
            player->vx = 0;
        }
    }
   
}

void player_update(Player *player) {
    player->x += player->vx;
    player->y += player->vy;
    player->vy += GRAVITY;
    if (player->y > MAP_HEIGHT*TILE_SIZE) {
        player_init(player);
    } 
}