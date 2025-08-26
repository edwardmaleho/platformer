#include "renderer.h"

int screen_x = 0, screen_y = 0;

void init_render(SDL_Renderer **renderer, SDL_Window **window) {
    SDL_Init(SDL_INIT_VIDEO);
    *window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, 0);
    *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void draw_map(SDL_Renderer *renderer) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (game_map[y][x] == GROUND) {
                SDL_Rect r = {x*TILE_SIZE+screen_x, y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }
}

void draw_player(SDL_Renderer *renderer, Player *player) {
    SDL_Rect p = {player->x+screen_x, player->y, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &p);
}

void draw_enemy(SDL_Renderer *renderer, Enemy *enemy) {
    if (enemy->is_dead) return;
    SDL_Rect e = {enemy->x+screen_x, enemy->y, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &e);
}

void render_window(SDL_Renderer *renderer, Player *player) {
    screen_x = 200-player->x;
    if (screen_x > 0) 
        screen_x = 0;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_map(renderer);

    for (int i = 0; i < enemy_count; i++) {
        draw_enemy(renderer, &enemies[i]);
    }

    draw_player(renderer, player);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}

void destroy_render(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}