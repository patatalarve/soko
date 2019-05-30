#include <curses.h>
#include "map.h"
#include "level.h"

static int won(map_s *map) {
    map = map;
    return 0;
}

static void move_curs(int ch, map_s *map) {
    int x = map->player.x;
    int y = map->player.y;
    if (ch == KEY_LEFT) {
        x -= 1;
    } else if (ch == KEY_RIGHT) {
        x += 1;
    } else if (ch == KEY_DOWN) {
        y += 1;
    } else if (ch == KEY_UP) {
        y -= 1;
    }
    if (map->map[y][x] == '1')
        return ;
    for (int i = 0; map->box[i].x > -1; i++) {
        if (map->box[i].x == x && map->box[i].y == y) {
            if ((map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '0') && 
                (map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '4') &&
                (map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '3'))
                return ;
            else {
                map->box[i].x = map->box[i].x +(x - map->player.x);
                map->box[i].y = map->box[i].y +(y - map->player.y);
                break ;
            }
        }
    }
    map->player.x = x;
    map->player.y = y;
}

static void print_map(map_s *map) {
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            if (map->map[i][j] == '0' ||
                map->map[i][j] == '1' ||
                map->map[i][j] == '4') { // regarder ce qu est une putain de ternaire <3
                char block = (map->map[i][j] == '0' ? GROUND : map->map[i][j] == '1' ? WALL : OBJECTIVE);
                mvprintw(i, j, "%c", block);
            }
        }
    }
    for (int i = 0; map->box[i].x >= 0; i++) {
        char found = 0;
        for (int j = 0; map->obj[j].x >= 0; j++) {
            if ((map->box[i].x == map->obj[j].x) && (map->box[i].y == map->obj[j].y)) {
                found = 1;
                break ;
            }

        }
        mvprintw(map->box[i].y, map->box[i].x, "%c", (found == 0 ? BOX : DONE));
    }
    mvprintw(map->player.y, map->player.x, "%c", PLAYER);
}

int gameloop(WINDOW *win, map_s *map) {
    print_map(map);
    while (!won(map)) {
        move_curs(getch(), map);
        wclear(win);
        print_map(map);
    }
    return (0);
}