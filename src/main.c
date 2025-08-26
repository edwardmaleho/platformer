#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "player.h"
#include "map.h"
#include "renderer.h"
#include <string.h>

#define TILE_SIZE 32

#define MAP_WIDTH 500
#define MAP_HEIGHT 30

#define GROUND 1

int running = 1;

void key_event(Player *player) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;
            
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) 
                    player_action(player, PLAYER_LEFT);
                if (e.key.keysym.sym == SDLK_RIGHT) 
                    player_action(player, PLAYER_RIGHT);
                if (e.key.keysym.sym == SDLK_UP) {
                    player_action(player, PLAYER_UP);
                }
            }
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    player_action(player, PLAYER_STOP_LEFT);
                }
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    player_action(player, PLAYER_STOP_RIGHT);
                }
            }
        }
}

int main(int argc, char **argv) {
    // initialize renderer
    char map[256] = "maps/";
    if (argc == 2) {
        strcat(map, argv[1]);
    } else {
        strcpy(map, "maps/map_1");
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    parse_map(map);

    // set up player
    Player player;
    player_init(&player);
    set_player_position(&player.x, &player.y);

    for (int i = 0; i < enemy_count; i++) {
        enemy_init(&enemies[i]);
    }

    // run game
    while (running) {
        key_event(&player);

        player_update(&player);
        
        for (int i = 0; i < enemy_count; i++) {
            enemy_update(&enemies[i]);
            enemy_check_collisions(&enemies[i]);
        }

        player_check_collisions(&player);

        render_window(renderer, &player);

     }

    destroy_render(renderer, window);

    return 0;
}