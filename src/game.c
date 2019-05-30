#include <curses.h>
#include <time.h>
#include <stdlib.h>

#include "map.h"
#include "level.h"

static int won(map_s *map) {
    for (int i = 0; map->box[i].x > -1; i++) {
        char done = 0;
        for (int j = 0; map->obj[j].x > -1; j++) {
            if (map->box[i].x == map->obj[j].x && map->box[i].y == map->obj[j].y)
                done = 1;
        }
        if (done == 0) {
            return 0;
        }
    }
    return 1;
}

static int noBlock(map_s *map, int x, int y) {
    for (int i = 0; map->box[i].x > -1; i++) {
        if (map->box[i].x == y && map->box[i].y == x)
            return 1;
    }
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
            if (((map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '0') && 
                (map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '4') &&
                (map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '2') &&
                (map->map[y * 2 - map->player.y][x * 2 - map->player.x] != '3')) ||
                noBlock(map, y * 2 - map->player.y, x * 2 - map->player.x))
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

static int check_deadlock(map_s *map, int y, int x) {
    int dir_x = 0;
    int dir_y = 0;
    int tmp_x = x;
    int tmp_y = y;

    //  ternaire qui empeche le segfault
    if (map->map[y > 0 ? y - 1 : y][x] == '1') {
        dir_x = -1;
    } else if (map->map[map->map[y + 1] ? y + 1 : y][x] == '1') {
        dir_x = 1;
    } else if (map->map[y][x > 0 ? x - 1 : x] == '1') {
        dir_y = -1;
    } else if (map->map[y][map->map[y][x + 1] ? x + 1 : x] == '1') {
        dir_y = 1;
    }
    while (map->map[tmp_y][tmp_x] != '1' && tmp_x > 0 && tmp_y > 0 && map->map[tmp_y][tmp_x]) {
        tmp_x += dir_x;
        tmp_y += dir_y;
        if (map->map[dir_x < 0 ? tmp_y - 1 : dir_x > 0 ? tmp_y + 1 : tmp_y]
                    [dir_y < 0 ? tmp_x - 1 : dir_y > 0 ? tmp_x + 1 : tmp_x])
            return 1;

    }
    return 0;
}

static void print_map(map_s *map) {
    for (int i = 0; map->map[i]; i++) {
        for (int j = 0; map->map[i][j]; j++) {
            attron(COLOR_PAIR(check_deadlock(map, i, j)));
            if (map->map[i][j] == '0' ||
                map->map[i][j] == '1' ||
                map->map[i][j] == '4') { // regarder ce qu est une putain de ternaire <3
                char block = (map->map[i][j] == '0' ? GROUND : map->map[i][j] == '1' ? WALL : OBJECTIVE);
                mvprintw(i, j, "%c", block);
            } else if (map->map[i][j] == '3')
                mvprintw(i, j, "%c", OBJECTIVE);
            attron(COLOR_PAIR(1));
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
        mvprintw(map->box[i].y, map->box[i].x, "%c", (found == 0 ? BOX : DONE)); // do the deadlock search
    }
    mvprintw(map->player.y, map->player.x, "%c", PLAYER); //  do the deadlock search
}

static int random_move() {
    getch();
    int r = rand() % 4;

    switch (r) {
        case 0:
            return KEY_LEFT;
        case 1:
            return KEY_RIGHT;
        case 2:
            return KEY_UP;
        default:
            return KEY_DOWN;
    }
}

int gameloop(WINDOW *win, map_s *map) {
    print_map(map);
    srand(time(NULL));
    random_move();
    while (!won(map)) {
        move_curs(getch(), map); // replace with 'random move'
        wclear(win);
        print_map(map);
    }
    return (0);
}