#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"

extern int screen_x, screen_y;

void init_render(SDL_Renderer **renderer, SDL_Window **window);

void draw_map(SDL_Renderer *renderer);

void draw_player(SDL_Renderer *renderer, Player *player);

void render_window(SDL_Renderer *renderer, Player *player);

void destroy_render(SDL_Renderer *renderer, SDL_Window *window);

#endif // RENDERER_H
