#include <curses.h>

#include "game.h"
#include "map.h"

int main() {

    map_s *map = create_map("./level/map.dat");
    if (!map)
        return 84;

    WINDOW *win = initscr();
    noecho();
    cbreak();
    keypad(win, TRUE);

    int ret = gameloop(win, map);

    endwin();

    return ret;
}