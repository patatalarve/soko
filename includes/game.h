#ifndef GAME_H_
# define GAME_H_

# include <curses.h>
# include "map.h"

int gameloop(WINDOW *win, map_s *map);

#endif