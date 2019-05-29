#include <curses.h>
#include "map.h"

static int won(map_s *map) {
    map = map;
    return 0;
}

static void move_curs(int ch) {
    if (ch == KEY_LEFT) {
        // x -= 1;
    } else if (ch == KEY_RIGHT) {
        // x += 1;
    } else if (ch == KEY_DOWN) {
        // y += 1;
    } else if (ch == KEY_UP) {
        // y -= 1;
    }
}

static void print_map(map_s *map) {
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            mvprintw(i, j, "%c", map->map[i][j]);
        }
    }
}

int gameloop(WINDOW *win, map_s *map) {
    print_map(map);
    while (!won(map)) {
        move_curs(getch());
        print_map(map);
    }

    win = win;
    return (0);
}