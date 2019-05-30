#include <curses.h>

#include "game.h"
#include "map.h"

int main(int ac, char **av) {

    if (ac != 2) {
        return 84;
    }

    map_s *map = create_map(av[1]);
    if (!map)
        return 84;

    WINDOW *win = initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(win, TRUE);
    start_color();

    init_pair(0, COLOR_BLACK, COLOR_RED);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    int ret = gameloop(win, map);

    endwin();

    return ret;
}