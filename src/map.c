#include "map.h"

int game_map[MAP_HEIGHT][MAP_WIDTH];

int player_x = 0, player_y = 0;

Enemy enemies[MAX_ENEMIES];
size_t enemy_count = 0;

void parse_map(char* map_name) {
	FILE *fp = fopen(map_name, "r");
	if (!fp) {
		perror("File opening failed");
		return;
	}
	char line[101];
	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			game_map[y][x] = 0;
		}
	}
    int x = 0;
	while (fgets(line, sizeof(line), fp)) {
		for (int y = 0; line[y] != '\0'; y++) {
			if (line[y] == 'x') {
				game_map[y][x] = GROUND;	
			}
			if (line[y] == 'p') {
				player_x = x*TILE_SIZE;
				player_y = y*TILE_SIZE;
			}
			if (line[y] == 'e') {
				enemies[enemy_count].x = x*TILE_SIZE;
				enemies[enemy_count].y = y*TILE_SIZE;
				enemy_count++;
			}
		}
		x++;
	}
	fclose(fp);
	return;
}

void set_player_position(int *x, int *y) {
	if (player_x == 0 && player_y == 0) return;
	*x = player_x;
	*y = player_y;
}

bool is_solid(int x, int y) {
    int px = x/TILE_SIZE;
    int py = y/TILE_SIZE;
    if (game_map[py][px] == GROUND) {
        return true;
    } else {
        return false;
    }
}

bool is_enemy(int x, int y, int *e) {
	for (int i = 0; i < enemy_count; i++) {
		int ex = enemies[i].x;
		int ey = enemies[i].y;
		if (x > ex && x < ex+ENEMY_SIZE && y > ey && y < ey+ENEMY_SIZE) {
			e = i;
			return true;
		}
	}
	return false;
}