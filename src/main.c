#include <curses.h>

#include "game.h"
#include "map.h"

int main() {

    map_s *map = create_map("./level/easy_6.dat");
    if (!map)
        return 84;

    WINDOW *win = initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(win, TRUE);

    int ret = gameloop(win, map);

    endwin();

    return ret;
}